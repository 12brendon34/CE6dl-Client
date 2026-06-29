#include "D3D11Hook.h"
#include <d3d11.h>
#include <dxgi.h>
#include <iostream>
#include <mutex>
#include <safetyhook.hpp>
#include "engine/Debug.h"
#include "engine/ModAPI.h"
#include "imgui.h"
#include "imgui_impl_dx11.h"
#include "imgui_impl_win32.h"


extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

namespace D3D11Hook {
    typedef HRESULT(__stdcall *PresentFn)(IDXGISwapChain *, UINT, UINT);
    typedef HRESULT(__stdcall *ResizeBuffersFn)(IDXGISwapChain *, UINT, UINT, UINT, DXGI_FORMAT, UINT);

    static safetyhook::InlineHook g_PresentHook;
    static safetyhook::InlineHook g_ResizeBuffersHook;
    static HWND g_Window = nullptr;
    static ID3D11Device *g_pDevice = nullptr;
    static ID3D11DeviceContext *g_pContext = nullptr;
    static ID3D11RenderTargetView *g_mainRenderTargetView = nullptr;
    static WNDPROC g_OriginalWndProcHandler = nullptr;
    static bool g_ImGuiInitialized = false;
    static std::recursive_mutex g_ImGuiMutex;
    static safetyhook::InlineHook g_SetCursorPosHook;
    static safetyhook::InlineHook g_ClipCursorHook;

    BOOL WINAPI Hooked_SetCursorPos(int X, int Y) {
        if (ModAPI::IsMenuOpen()) {
            POINT pt;
            GetCursorPos(&pt);
            return g_SetCursorPosHook.call<BOOL>(pt.x, pt.y);
        }
        return g_SetCursorPosHook.call<BOOL>(X, Y);
    }

    BOOL WINAPI Hooked_ClipCursor(const RECT *lpRect) {
        if (ModAPI::IsMenuOpen())
            return TRUE;
        return g_ClipCursorHook.call<BOOL>(lpRect);
    }

    void CreateRenderTarget(IDXGISwapChain *pSwapChain) {
        if (!pSwapChain || !g_pDevice)
            return;
        ID3D11Texture2D *pBackBuffer = nullptr;
        const HRESULT hr = pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void **) &pBackBuffer);
        if (FAILED(hr) || !pBackBuffer) {
            dbgprintf("GetBuffer failed (hr=0x%X)\n", static_cast<unsigned>(hr));
            return;
        }
        const HRESULT hrRtv = g_pDevice->CreateRenderTargetView(pBackBuffer, NULL, &g_mainRenderTargetView);
        pBackBuffer->Release();
        if (FAILED(hrRtv) || !g_mainRenderTargetView) {
            dbgprintf("CreateRenderTargetView failed (hr=0x%X)\n", static_cast<unsigned>(hrRtv));
        }
    }

    void CleanupRenderTarget() {
        if (g_mainRenderTargetView) {
            g_mainRenderTargetView->Release();
            g_mainRenderTargetView = nullptr;
        }
    }

    LRESULT CALLBACK WndProcHook(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
        if (msg == WM_KEYDOWN || msg == WM_SYSKEYDOWN) {
            if (wParam == ModAPI::GetMenuKey() && ((lParam & 0x40000000) == 0)) {
                ModAPI::ToggleMenu();
            }
        }

        {
            std::lock_guard<std::recursive_mutex> lock(g_ImGuiMutex);
            if (g_ImGuiInitialized && ImGui::GetCurrentContext()) {
                ImGuiIO &io = ImGui::GetIO();
                if (ModAPI::IsMenuOpen()) {
                    ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam);
                    io.MouseDrawCursor = true;
                    // mouse interaciton disabled for now because i couldnt figure it out
                    // if (msg >= WM_MOUSEFIRST && msg <= WM_MOUSELAST) return DefWindowProc(hWnd, msg, wParam, lParam);
                    if (msg >= WM_KEYFIRST && msg <= WM_KEYLAST && wParam != ModAPI::GetMenuKey())
                        return DefWindowProc(hWnd, msg, wParam, lParam);
                    // disabled for now
                    // if (msg == WM_INPUT) return DefWindowProc(hWnd, msg, wParam, lParam); // block raw input
                } else {
                    io.MouseDrawCursor = false;
                }
            }
        }
        if (g_OriginalWndProcHandler)
            return CallWindowProc(g_OriginalWndProcHandler, hWnd, msg, wParam, lParam);
        return DefWindowProc(hWnd, msg, wParam, lParam);
    }

    HRESULT __stdcall Present(IDXGISwapChain *pSwapChain, UINT SyncInterval, UINT Flags) {
        try {
            if (!g_ImGuiInitialized) {
                dbgprintf("Initializing ImGui...\n");
                if (SUCCEEDED(pSwapChain->GetDevice(__uuidof(ID3D11Device), (void **) &g_pDevice))) {
                    g_pDevice->GetImmediateContext(&g_pContext);
                    DXGI_SWAP_CHAIN_DESC sd;
                    pSwapChain->GetDesc(&sd);
                    g_Window = sd.OutputWindow;
                    dbgprintf("OutputWindow: %p\n", g_Window);

                    CreateRenderTarget(pSwapChain);

                    ImGui::CreateContext();
                    ImGuiIO &io = ImGui::GetIO();
                    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

                    if (!ImGui_ImplWin32_Init(g_Window) || !ImGui_ImplDX11_Init(g_pDevice, g_pContext)) {
                        dbgprintf("ImGui backend init failed\n");
                        CleanupRenderTarget();
                        ImGui::DestroyContext();
                        if (g_pContext) {
                            g_pContext->Release();
                            g_pContext = nullptr;
                        }
                        if (g_pDevice) {
                            g_pDevice->Release();
                            g_pDevice = nullptr;
                        }
                        g_Window = nullptr;
                        return g_PresentHook.call<HRESULT>(pSwapChain, SyncInterval, Flags);
                    }

                    SetLastError(0);
                    g_OriginalWndProcHandler = (WNDPROC) SetWindowLongPtr(g_Window, GWLP_WNDPROC, (LONG_PTR) WndProcHook);
                    const DWORD wndProcErr = GetLastError();
                    if (!g_OriginalWndProcHandler && wndProcErr != 0) {
                        dbgprintf("Failed to set window long ptr! Error: %lu\n", wndProcErr);
                    } else {
                        dbgprintf("WndProc hooked successfully.\n");
                    }

                    g_ImGuiInitialized = true;
                    ModAPI::SetImGuiContext(ImGui::GetCurrentContext());
                    dbgprintf("ImGui Initialized.\n");
                } else {
                    dbgprintf("GetDevice failed in Present!\n");
                }
            }

            {
                std::lock_guard<std::recursive_mutex> lock(g_ImGuiMutex);
                if (g_ImGuiInitialized) {
                    ImGui_ImplDX11_NewFrame();
                    ImGui_ImplWin32_NewFrame();
                    ImGui::NewFrame();

                    ModAPI::CallOnImGuiCallbacks();

                    ImGui::Render();

                    ID3D11RenderTargetView *prevRenderTargetView = nullptr;
                    ID3D11DepthStencilView *prevDepthStencilView = nullptr;
                    g_pContext->OMGetRenderTargets(1, &prevRenderTargetView, &prevDepthStencilView);

                    g_pContext->OMSetRenderTargets(1, &g_mainRenderTargetView, NULL);
                    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

                    g_pContext->OMSetRenderTargets(1, &prevRenderTargetView, prevDepthStencilView);
                    if (prevRenderTargetView)
                        prevRenderTargetView->Release();
                    if (prevDepthStencilView)
                        prevDepthStencilView->Release();
                }
            }
        } catch (...) {
            dbgprintf("Exception inside Present hook!\n");
        }

        return g_PresentHook.call<HRESULT>(pSwapChain, SyncInterval, Flags);
    }

    HRESULT __stdcall ResizeBuffers(IDXGISwapChain *pSwapChain, UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags) {
        CleanupRenderTarget();
        HRESULT hr = g_ResizeBuffersHook.call<HRESULT>(pSwapChain, BufferCount, Width, Height, NewFormat, SwapChainFlags);
        if (g_pDevice) {
            CreateRenderTarget(pSwapChain);
        }
        return hr;
    }

    bool Initialize() {
        WNDCLASSEXA wc = {sizeof(WNDCLASSEXA), CS_CLASSDC, DefWindowProcA, 0L, 0L, GetModuleHandle(NULL), NULL, NULL, NULL, NULL, "DX11Dummy", NULL};
        if (!RegisterClassExA(&wc)) {
            dbgprintf("RegisterClassExA failed (err=%lu)\n", GetLastError());
            return false;
        }
        HWND hwnd = CreateWindowA(wc.lpszClassName, "Dummy", WS_OVERLAPPEDWINDOW, 100, 100, 10, 10, NULL, NULL, wc.hInstance, NULL);
        if (!hwnd) {
            dbgprintf("CreateWindowA failed (err=%lu)\n", GetLastError());
            UnregisterClassA(wc.lpszClassName, wc.hInstance);
            return false;
        }

        DXGI_SWAP_CHAIN_DESC sd = {};
        sd.BufferCount = 1;
        sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        sd.OutputWindow = hwnd;
        sd.SampleDesc.Count = 1;
        sd.Windowed = TRUE;
        sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

        ID3D11Device *pDevice = nullptr;
        IDXGISwapChain *pSwapChain = nullptr;
        D3D_FEATURE_LEVEL featureLevel;

        HRESULT hr = D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, 0, NULL, 0, D3D11_SDK_VERSION, &sd, &pSwapChain, &pDevice, &featureLevel, NULL);

        if (FAILED(hr)) {
            DestroyWindow(hwnd);
            UnregisterClassA(wc.lpszClassName, wc.hInstance);
            return false;
        }

        void **pVTable = *reinterpret_cast<void ***>(pSwapChain);
        void *presentAddress = pVTable[8];
        void *resizeBuffersAddress = pVTable[13];

        g_PresentHook = safetyhook::create_inline(presentAddress, reinterpret_cast<void *>(Present));
        g_ResizeBuffersHook = safetyhook::create_inline(resizeBuffersAddress, reinterpret_cast<void *>(ResizeBuffers));
        // mouse hooks disabled
        // g_SetCursorPosHook = safetyhook::create_inline(reinterpret_cast<void*>(&SetCursorPos), reinterpret_cast<void*>(Hooked_SetCursorPos));
        // g_ClipCursorHook = safetyhook::create_inline(reinterpret_cast<void*>(&ClipCursor), reinterpret_cast<void*>(Hooked_ClipCursor));

        pSwapChain->Release();
        pDevice->Release();
        DestroyWindow(hwnd);
        UnregisterClassA(wc.lpszClassName, wc.hInstance);

        dbgprintf("D3D11 hooks installed\n");
        return true;
    }

    void Shutdown() {
        std::lock_guard<std::recursive_mutex> lock(g_ImGuiMutex);

        if (g_ImGuiInitialized) {
            if (g_Window && g_OriginalWndProcHandler)
                SetWindowLongPtr(g_Window, GWLP_WNDPROC, (LONG_PTR) g_OriginalWndProcHandler);

            CleanupRenderTarget();

            ImGui_ImplDX11_Shutdown();
            ImGui_ImplWin32_Shutdown();
            ImGui::DestroyContext();

            ModAPI::SetImGuiContext(nullptr);

            if (g_pContext) {
                g_pContext->Release();
                g_pContext = nullptr;
            }
            if (g_pDevice) {
                g_pDevice->Release();
                g_pDevice = nullptr;
            }

            g_Window = nullptr;
            g_OriginalWndProcHandler = nullptr;
            g_ImGuiInitialized = false;
        }

        g_PresentHook.reset();
        g_ResizeBuffersHook.reset();
        // mouse hooks disabled
        // g_SetCursorPosHook.reset();
        // g_ClipCursorHook.reset();
    }
} // namespace D3D11Hook
