//
// Created by Brendon on 2/5/2026.
//

#pragma once
class CameraFPPDI;

// taken from Dead Island, might be wrong
class ECameraTypeDI {
    public:
    enum TYPE {
        NONE = 0,
        TPPCAMERA = 1,
        FPPCAMERA = 2,
        CARCAMERA = 3,
        BOATCAMERA = 4,
        MAPCAMERA = 5
    };
};

class CameraManagerDI {
    public:
    char _pad[0x50]; //m_Cameras (cameracontainerdi), m_Session
    CameraFPPDI* m_ActiveCamera;
    ECameraTypeDI::TYPE m_ActiveType;
};
