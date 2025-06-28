#include <pch.h>
#include "MenuOptionsGameHook.h"
#include "UIOptionSliderHook.h"
#include "../PluginInfo.h"
#include "../Core/Util/Mem.h"
#include "../Core/Sdk/Game/UIOptionSlider.h"

void MenuOptionsGameHook::OnInit(__int64* MenuOptionsGame_this) {
    dbgprintf("[%s] OnInit hook triggered. this = %p\n", kPluginName, MenuOptionsGame_this);

    if (oOnInit) {
        oOnInit(MenuOptionsGame_this);
    }

    // Access UIOptionSlider at offset 0x540
    auto* slider = *reinterpret_cast<UIOptionSlider**>(reinterpret_cast<uintptr_t>(MenuOptionsGame_this) + 0x540);

    if (!slider) {
        dbgprintf("[%s] UIOptionSlider at offset 0x540 is null!\n", kPluginName);
        return;
    }

    slider->maxValue = g_maxFov;
    UIOptionSliderHook::AdjustSlider(slider, 1);
}

void MenuOptionsGameHook::install() {
    HMODULE gamedll = GetModuleHandleA("gamedll_x64_rwdi.dll");
    if (!gamedll) {
        MessageBoxA(nullptr, "Failed to find gamedll_x64_rwdi.dll", "Error", MB_ICONERROR);
        return;
    }

    auto target = Utils::findSig(gamedll, "");
    if (!target) {
        MessageBoxA(nullptr, "Signature for MenuOptionsGame::OnInit not found", "Error", MB_ICONERROR);
        return;
    }

    detour = std::make_unique<PLH::x64Detour>(target, reinterpret_cast<uint64_t>(&MenuOptionsGameHook::OnInit), reinterpret_cast<uint64_t*>(&oOnInit));

    if (!detour->hook()) {
        MessageBoxA(nullptr, "Failed to hook MenuOptionsGame::OnInit", "Error", MB_ICONERROR);
    }
}
