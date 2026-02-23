//
// Created by Brendon on 1/18/2026.
//

#pragma once
#include "engine/Kernel/ttl/String.h"
#include "games/DeadIsland/Game/Player/PlayerDI.h"

class SessionDI;
class PlayerSaveContext {
    public:
};

class ClientDI //: public IGSObject
{
public:
    char pad_0000[64]; // 0x0000
    SessionDI *m_Session; // 0x0040
    bool m_IsLocal;
    // padding byte
    // padding byte
    // padding byte
    PlayerDI *m_PlayerObject; // SmartPtr<PlayerDI> m_PlayerObject; // 0x0050
    ttl::string_base<wchar_t> m_Name;
    char pad_0068[17]; // 0x0068
};
static_assert(sizeof(ClientDI) == 0x80);

class LocalClientDI : public ClientDI {
public:
    int m_TransactionIDCounter; //80
    bool m_AlreadySpawned; //84
    // padding byte
    // padding byte
    // padding byte
    //PlayerSaveContext::PlayerSaveContext(v3);
    alignas(8) PlayerSaveContext m_PlayerSaveContext;
    //then the unknown that I am passing (likely the entire PlayerSaveContext m_PlayerSaveContext)
};
static_assert(offsetof(LocalClientDI, m_PlayerSaveContext) == 0x88, "offset mismatch");