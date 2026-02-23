//
// Created by Brendon on 1/29/2026.
//

#include "library.h"

#include <cassert>
#include <iostream>
#include <windows.h>

#include "engine/Debug.h"
#include <libhat/scanner.hpp>

#include "games/DeadIsland/Game/Camera/CameraManagerDI.h"
#include "games/DeadIsland/Game/Game/LocalClientDI.h"
using namespace hat::literals; // for _sig / _sigv UDLs

void OnLoad() {
    std::cout << "Hello, World!" << std::endl;
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


    //set CamManager->m_ActiveType to ECameraTypeDI::TPPCAMERA
    constexpr auto pattern = "48 89 6C 24 ? 48 89 74 24 ? 41 56 48 83 EC ? 48 8B 41 ? 4D 8B F0"_sig;

    static void* cached_addr = nullptr;
    if (!cached_addr) {
        std::optional<hat::process::module> ntdll = hat::process::get_module("gamedll_x64_rwdi.dll");
        assert(ntdll.has_value());
        hat::scan_result result = hat::find_pattern(pattern, ".text", *ntdll);

        const std::byte* match = nullptr;
        try {
            match = result.get();
        } catch (...) {
            match = nullptr;
        }

        if (!match) {
            dbgprintf("ChangeCamera pattern not found\n");
            return;
        }
        cached_addr = (void*)match;
        dbgprintf("Found ChangeCamera at %p\n", cached_addr);
        MessageBoxA(nullptr, "Zamn", nullptr, 0);
    }

    using ChangeCameraFn = void(*)(CameraManagerDI* /*thisptr*/, ECameraTypeDI::TYPE /*type*/, PlayerDI* /*obj*/);


    const ChangeCameraFn ChangeCamera = reinterpret_cast<ChangeCameraFn>(cached_addr);
    if (!ChangeCamera) {
        dbgprintf("ChangeCamera: null function pointer\n");
        return;
    }

    auto desiredType = ECameraTypeDI::BOATCAMERA;

    if (CamManager->m_ActiveType != desiredType && CamManager->m_ActiveType != ECameraTypeDI::NONE)
        ChangeCamera(CamManager, desiredType, pIGame->m_Session->m_LocalClient->m_PlayerObject);
}