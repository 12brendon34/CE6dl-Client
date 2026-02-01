//
// Created by Brendon on 1/14/2026.
//
#include "CustomSplash.h"
#include "resource.h"
#include <gdiplus.h>

#pragma comment(lib, "gdiplus")

HBITMAP LoadImageFromResource(HMODULE hMod, LPCSTR resid, LPCSTR restype) {
    Gdiplus::GdiplusStartupInput gdiplusStartupInput;
    ULONG_PTR gdiplusToken = 0;
    if (Gdiplus::Ok != Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, nullptr))
        return nullptr;

    HRSRC hrsrc = FindResource(hMod, resid, restype);
    if (!hrsrc)
        return nullptr;

    const DWORD dwResourceSize = SizeofResource(hMod, hrsrc);
    if (dwResourceSize == 0)
        return nullptr;

    const HGLOBAL hGlobalResource = LoadResource(hMod, hrsrc);
    if (!hGlobalResource)
        return nullptr;

    void *imagebytes = LockResource(hGlobalResource);
    if (!imagebytes)
        return nullptr;

    const HGLOBAL hGlobal = ::GlobalAlloc(GHND, dwResourceSize);
    if (!hGlobal)
        return nullptr;

    void *pBuffer = ::GlobalLock(hGlobal);
    if (!pBuffer)
        return nullptr;
    memcpy(pBuffer, imagebytes, dwResourceSize);
    ::GlobalUnlock(hGlobal);

    IStream *pStream = nullptr;
    const HRESULT hr = CreateStreamOnHGlobal(hGlobal, TRUE, &pStream);
    if (FAILED(hr) || !pStream)
        return nullptr;

    const auto pBmp = new Gdiplus::Bitmap(pStream);
    if (pBmp->GetLastStatus() != Gdiplus::Ok)
        return nullptr;

    HBITMAP hBitmap = nullptr;
    if (pBmp->GetHBITMAP(Gdiplus::Color(0, 0, 0), &hBitmap) != Gdiplus::Ok)
        return nullptr;

    return hBitmap;
}

void ShowCustomSplashscreen(HINSTANCE hInstance, LPCSTR bitmap_res, UINT app_title_res, HICON icon) {
    CHAR app_title[128] = {};
    LoadString(hInstance, app_title_res, app_title, sizeof(app_title));

    l_Bitmap = LoadImageFromResource(hInstance, bitmap_res, "PNG");
    //l_Bitmap = static_cast<HBITMAP>(LoadImage(hInstance, bitmap_res, IMAGE_BITMAP, 0, 0, 0));
    if (!l_Bitmap)
        return;

    l_Splash = CreateDialogParam(hInstance, MAKEINTRESOURCE(IDD_SPLASH), nullptr, nullptr, 0);
    if (!l_Splash)
        return;

    SendDlgItemMessage(l_Splash, 1002, STM_SETIMAGE, IMAGE_BITMAP, reinterpret_cast<LPARAM>(l_Bitmap));

    if (app_title[0])
        SetWindowText(l_Splash, app_title);

    SetClassLongPtr(l_Splash, GCLP_HICON, reinterpret_cast<LONG_PTR>(icon));

    BITMAP bmp = {};
    if (GetObject(l_Bitmap, sizeof(bmp), &bmp) == 0)
        return;

    if (const HWND hCtrl = GetDlgItem(l_Splash, 1002))
        SetWindowPos(hCtrl, nullptr, 0, 0, bmp.bmWidth, bmp.bmHeight, SWP_NOZORDER | SWP_NOMOVE | SWP_NOCOPYBITS | SWP_NOOWNERZORDER);

    const int x = (GetSystemMetrics(SM_CXSCREEN) - bmp.bmWidth) / 2;
    const int y = (GetSystemMetrics(SM_CYSCREEN) - bmp.bmHeight) / 2;
    SetWindowPos(l_Splash, nullptr, x, y, bmp.bmWidth, bmp.bmHeight, SWP_NOZORDER | SWP_NOCOPYBITS | SWP_NOOWNERZORDER);
    UpdateWindow(l_Splash);
}

void HideCustomSplashscreen() {
    if (l_Splash != nullptr) {
        DestroyWindow(l_Splash);
        l_Splash = nullptr;
    }
    if (l_Bitmap != nullptr) {
        DeleteObject(l_Bitmap);
        l_Bitmap = nullptr;
    }
}
