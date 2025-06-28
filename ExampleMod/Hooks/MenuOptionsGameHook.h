#pragma once
#include "HookManager.h"

class MenuOptionsGameHook : public Hook {
public:
    using OnInitFn = void(*)(__int64* MenuOptionsGame_this);
    static void OnInit(__int64* MenuOptionsGame_this);

    void install() override;

private:
    inline static std::unique_ptr<PLH::Detour> detour;
    inline static OnInitFn oOnInit = nullptr;
};