#include <pch.h>
#include "Core/Sdk/Engine/igame.h"
#include "MinHook/MinHook.h"

//minhook log
static void CheckMH(MH_STATUS status) {
#ifdef _DEBUG
    if (status != MH_OK) {
        dbgprintf("MinHook Error (%d): %s\n", status, MH_StatusToString(status));
        exit(EXIT_FAILURE);
    }
#endif
}

// plugin name
static constexpr const char* kPluginName = "ExtraFov";

// Internal struct (partial)
struct UIOptionSlider {
    char padding[0xAC];
    int maxValue;  // Offset 0xAC
    int minValue;  // Offset 0xB0
};

// Function pointer declarations
static void(__fastcall* OriginalAdjustSlider)(void*, char) = nullptr;
static void(__fastcall* OriginalOnInit)(void*) = nullptr;

// Hooked slider function
static void __fastcall AdjustSlider_Hook(UIOptionSlider* self, char param) {
    dbgprintf("[%s] AdjustSlider called. this = %p, param = %d, Max = %d, Min = %d\n",
        kPluginName, self, param, self->maxValue, self->minValue);

    if (OriginalAdjustSlider)
        OriginalAdjustSlider(self, param);
}

// Hooked menu option init function
static void __fastcall OnInit_Hook(void* self) {
    dbgprintf("[%s] OnInit hook triggered. this = %p\n", kPluginName, self);

    if (OriginalOnInit)
        OriginalOnInit(self);

    auto* slider = *reinterpret_cast<UIOptionSlider**>((uintptr_t)self + 0x540);
    if (!slider) {
        dbgprintf("[%s] UIOptionSlider at 0x540 is null!\n", kPluginName);
        return;
    }

    slider->maxValue = 40;
    AdjustSlider_Hook(slider, 1);
}

// Plugin name exposed to loader
extern "C" __declspec(dllexport) const char* GetPluginName() {
    return kPluginName;
}

// Called before CGame::Initialize
extern "C" __declspec(dllexport) void PreInitialize(std::string ModPath) {
    dbgprintf("[%s] PreInitialize\n", kPluginName);

    HMODULE gameModule = GetModuleHandleA("gamedll_x64_rwdi.dll");
    if (!gameModule) {
        dbgprintf("[%s] Failed to get game module handle\n", kPluginName);
        return;
    }

    auto* onInitAddr = reinterpret_cast<void*>((uintptr_t)gameModule + 0x1251630); //god I need to setup aob//0x1251090);
    auto* adjustSliderAddr = reinterpret_cast<void*>((uintptr_t)gameModule + 0x117b430);//0x117AE90);

    CheckMH(MH_Initialize());

    CheckMH(MH_CreateHook(onInitAddr, &OnInit_Hook, reinterpret_cast<void**>(&OriginalOnInit)));
    CheckMH(MH_CreateHook(adjustSliderAddr, &AdjustSlider_Hook, reinterpret_cast<void**>(&OriginalAdjustSlider)));

    CheckMH(MH_EnableHook(onInitAddr));
    CheckMH(MH_EnableHook(adjustSliderAddr));
}

// Called after game engine initialization
extern "C" __declspec(dllexport) void PostInitialize(IGame* gameInstance) {
    dbgprintf("[%s] PostInitialize\n", kPluginName);
    dbgprintf("IGame Ptr: %p\n", gameInstance);
}

// DLL entry point
BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved) {
    if (ul_reason_for_call == DLL_PROCESS_ATTACH) {
        dbgprintf("[%s] DLL_PROCESS_ATTACH\n", kPluginName);
    }
    return TRUE;
}
