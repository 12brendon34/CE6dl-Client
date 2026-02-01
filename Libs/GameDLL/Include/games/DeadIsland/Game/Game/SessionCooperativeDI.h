//
// Created by Brendon on 1/18/2026.
//
#pragma once
#include "LevelDI.h"
#include "LocalClientDI.h"

class CameraManagerDI {};

class SessionCooperativeDI {
public:
    /*
    char pad_0000[72]; //0x0000
    class LogicalLevel *N00000800; //0x0048
    char pad_0050[32]; //0x0050
    class Sessions::LocalClient *m_Sessions_LocalClient; //0x0070
    char pad_0078[24]; //0x0078
    class N00001B44 *m_Sessions_StatusDL; //0x0090
    char pad_0098[24]; //0x0098
    class LevelDI *m_ActiveLevel; //0x00B0
    class LocalClientDI *m_LocalClient; //0x00B8
    */
    char pad_0176[0xB0];
    LevelDI *m_ActiveLevel; //start of SessionDI
    LocalClientDI *m_LocalClient; //0x00B8
    CameraManagerDI *m_CameraManager; //0x00C0
};
