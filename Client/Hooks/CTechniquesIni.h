// CMaterialMgrHook.h
#pragma once
#include "HookManager.h"

extern void** r_MatMgr;

class CTechniquesIni : public Hook {
public:
    using CreateFn = __int64(*)(void** CTechniquesIni_this, __int64 param_2, __int64 param_3, __int64 param_4);
    static __int64 Create(void** param_1, __int64 param_2, __int64 param_3, __int64 param_4);

    void install() override;

private:
    inline static std::unique_ptr<PLH::Detour> detour;
    inline static CreateFn oCreate = nullptr;
};