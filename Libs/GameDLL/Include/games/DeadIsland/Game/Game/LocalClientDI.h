//
// Created by Brendon on 1/18/2026.
//

#pragma once
#include "games/DeadIsland/Game/Player/PlayerDI.h"

class SessionCooperativeDI;

class LocalClientDI {
    public:
    char pad_0000[64]; //0x0000
    SessionCooperativeDI *N00000E4E; //0x0040
    char pad_0048[8]; //0x0048
    PlayerDI *m_PlayerDI; //0x0050
};
