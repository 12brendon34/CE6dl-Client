#include <pch.h>
#include "UIOptionSliderHook.h"
#include "../PluginInfo.h"
#include "../Core/Util/Mem.h"

void UIOptionSliderHook::AdjustSlider(UIOptionSlider* slider, std::int8_t param_2) {
    dbgprintf("[%s] AdjustSlider called. this = %p, param = %d, Max = %d, Min = %d\n", kPluginName, slider, param_2, slider->maxValue, slider->minValue);

    if (oAdjustSlider)
        oAdjustSlider(slider, param_2);
}

void UIOptionSliderHook::install() {
    HMODULE gamedll = GetModuleHandleA("gamedll_x64_rwdi.dll");
    if (!gamedll) {
        MessageBoxA(nullptr, "Failed to find gamedll_x64_rwdi.dll", "Error", MB_ICONERROR);
        return;
    }

    // TODO: Provide actual signature in findSig call
    auto target = Utils::findSig(gamedll, "40 55 57 48 8D 6C 24 ? 48 81 EC ? ? ? ? 8B 81");
    if (!target) {
        MessageBoxA(nullptr, "Signature for UIOptionSlider::AdjustSlider not found", "Error", MB_ICONERROR);
        return;
    }

    detour = std::make_unique<PLH::x64Detour>(target, reinterpret_cast<uint64_t>(&UIOptionSliderHook::AdjustSlider), reinterpret_cast<uint64_t*>(&oAdjustSlider));
    if (!detour->hook()) {
        MessageBoxA(nullptr, "Failed to hook UIOptionSlider::AdjustSlider", "Error", MB_ICONERROR);
    }
}
