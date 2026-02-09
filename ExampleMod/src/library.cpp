//
// Created by Brendon on 1/29/2026.
//

#include "library.h"
#include <windows.h>
#include <iostream>

void OnLoad() {
    std::cout << "Hello, World!" << std::endl;
}

//haven't bothered implementing yet
void OnUnload() {
    std::cout << "Goodbye, World!" << std::endl;
}


void OnPaint(IGame *pIGame) {
    if (!pIGame->m_Session)
        return;

    const auto CamManager = pIGame->m_Session->m_CameraManager;
    if (!CamManager)
        return;

    static int lastCameraType = -1;
    int currentType = CamManager->m_ActiveType;

    if (currentType != lastCameraType)
    {
        const char *CameraTypeNames[] = {"NONE", "TPPCAMERA", "FPPCAMERA", "CARCAMERA", "BOATCAMERA", "MAPCAMERA"};
        printf("%s\n", CameraTypeNames[currentType]);
        lastCameraType = currentType;
    }

    IBaseCamera* camera = CamManager->m_ActiveCamera;
    if (camera)
        camera->SetOrthoView(ECameraMode::BACK);
}