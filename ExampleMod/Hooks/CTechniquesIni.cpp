// CMaterialMgrHook.cpp
#include <pch.h>
#include "CTechniquesIni.h"
#include "../Core/Util/Mem.h"

void** r_MatMgr = nullptr;

__int64 CTechniquesIni::Create(void** param_1, __int64 param_2, __int64 param_3, __int64 param_4) {
    void** dat_180a402b0 = param_1 - 1;

    // Log value
    dbgprintf("r_MatMgr; %p\n", dat_180a402b0);
    r_MatMgr = dat_180a402b0;

    return oCreate(param_1, param_2, param_3, param_4);
}

void CTechniquesIni::install() {
    HMODULE engine = GetModuleHandleA("engine_x64_rwdi.dll");
    if (!engine) {
        MessageBoxA(nullptr, "Failed to find engine_x64_rwdi.dll", "Error", MB_ICONERROR);
        return;
    }

    auto target = Utils::findSig(engine, "40 55 53 57 41 56 48 8D AC 24");
    detour = std::make_unique<PLH::x64Detour>(target, reinterpret_cast<uint64_t>(&CTechniquesIni::Create), reinterpret_cast<uint64_t*>(&oCreate));
     

    if (!detour->hook()) {
        MessageBoxA(nullptr, "Failed to hook PackLoader::Load", "Error", MB_ICONERROR);
    }
}
