#pragma once
#include "HookManager.h"
#include "../Core/Sdk/Game/UIOptionSlider.h"

class UIOptionSliderHook: public Hook {
public:
    using AdjustSliderFn = void(*)(UIOptionSlider* slider, std::int8_t);
    static void AdjustSlider(UIOptionSlider* slider, std::int8_t);

    void install() override;

private:
    inline static std::unique_ptr<PLH::Detour> detour;
    inline static AdjustSliderFn oAdjustSlider = nullptr;
};