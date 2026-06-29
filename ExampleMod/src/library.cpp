//
// Created by Brendon on 1/29/2026.
//

#include "library.h"

#include <cassert>
#include <iostream>
#include <windows.h>

#include "engine/Debug.h"
#include <libhat/scanner.hpp>
#include <imgui.h>

#include "games/DeadIsland/Game/Camera/CameraManagerDI.h"
#include "games/DeadIsland/Game/Game/LocalClientDI.h"
using namespace hat::literals; // for _sig / _sigv UDLs

bool OnLoad() {
    std::cout << "Hello, World!" << std::endl;
    return true;
}

//haven't bothered implementing yet
void OnUnload() {
    std::cout << "Goodbye, World!" << std::endl;
}

//not implemented
class ObjectDI{};

void OnPaint(IGame *pIGame) {
    if (!pIGame->m_Session)
        return;

    const auto CamManager = pIGame->m_Session->m_CameraManager;
    if (!CamManager)
        return;

    /*
    static int lastCameraType = -1;
    int currentType = CamManager->m_ActiveType;

    if (currentType != lastCameraType)
    {
        const char *CameraTypeNames[] = {"NONE", "TPPCAMERA", "FPPCAMERA", "CARCAMERA", "BOATCAMERA", "MAPCAMERA"};
        dbgprintf("%s\n", CameraTypeNames[currentType]);
        dbgprintf("pIGame: %p\n", pIGame);
        dbgprintf("m_Session: %p\n", pIGame->m_Session);
        dbgprintf("m_CameraManager: %p\n", pIGame->m_Session->m_CameraManager);

        lastCameraType = currentType;
    }
    */

    //IBaseCamera* camera = CamManager->m_ActiveCamera;
    //if (camera)
    //    camera->SetOrthoView(ECameraMode::BACK);


    // draw custom ui or do per-frame logic here
}

#include <atomic>
std::atomic<bool> g_show_ui = false;

void OnImGui(void* ctx) {
    ImGui::SetCurrentContext((ImGuiContext*)ctx);

    bool bShow = g_show_ui.load();
    if (bShow) {
        ImGui::Begin("Dying Light Custom Edition", &bShow);
        ImGui::Text("Hello from ExampleMod!");
        ImGui::Text("Press INSERT to toggle this menu.");
        if (ImGui::Button("Close")) {
            bShow = false;
        }
        ImGui::End();
        g_show_ui.store(bShow);
    }
}

void OnKey(int key, bool isDown) {
    if (key == VK_INSERT && isDown) {
        g_show_ui = !g_show_ui;
    }
    // log key event
    char keyName[128] = {0};
    UINT scanCode = MapVirtualKeyA(key, MAPVK_VK_TO_VSC);
    
    // For extended keys, GetKeyNameText requires the extended bit (bit 24)
    LONG lParam = (scanCode << 16);
    switch (key) {
        case VK_LEFT: case VK_UP: case VK_RIGHT: case VK_DOWN:
        case VK_RCONTROL: case VK_RMENU:
        case VK_LWIN: case VK_RWIN: case VK_APPS:
        case VK_PRIOR: case VK_NEXT: case VK_END: case VK_HOME:
        case VK_INSERT: case VK_DELETE: case VK_DIVIDE: case VK_NUMLOCK:
            lParam |= (1 << 24);
            break;
    }

    GetKeyNameTextA(lParam, keyName, sizeof(keyName));
    
    dbgprintf("name: %s key: %d down: %d\n", keyName, key, isDown);
}