// dllmain.cpp : Defines the entry point for the DLL application.
#include <pch.h>
#include "Core/Sdk/Engine/igame.h"
#include "MinHook/MinHook.h"

void ERRCHECK(MH_STATUS result) {
#ifdef _DEBUG
	if (result != MH_OK) {
        dbgprintf("MinHook error! (%d) %s\n", result, MH_StatusToString(result));
		exit(-1);
	}
#endif
}

static const char* pluginName = "EXAMPLE";

//Dll loaded after splash screen load
BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved) {
	if (ul_reason_for_call == DLL_PROCESS_ATTACH) {
        dbgprintf("[%s] DLL_PROCESS_ATTACH\n", pluginName);
	}
	return TRUE;
}

//set plugin name in loader
extern "C" __declspec(dllexport) const char* GetPluginName() {
    return pluginName;
}

//actual struct of it (partual, theres alot for some reason)
struct UIOptionSlider
{
    char pad_0000[0xAC];
    int m_iMaxValue;  // 0xAC
    int m_iMinValue;  // 0xB0
};

class UIOptionSliderHook {
public:
    static void __fastcall AdjustSlider_Hook(UIOptionSlider* thisptr, char param);
    static void(__fastcall* OriginalAdjustSlider)(void*, char);
};

class MenuOptionsGameHook {
public:
    static void __fastcall OnInit_Hook(void* thisptr);
    static void(__fastcall* OriginalOnInit)(void*);
};

void(__fastcall* UIOptionSliderHook::OriginalAdjustSlider)(void*, char) = nullptr;
void(__fastcall* MenuOptionsGameHook::OriginalOnInit)(void*) = nullptr;


void __fastcall MenuOptionsGameHook::OnInit_Hook(void* thisptr)
{
    dbgprintf("[%s] MenuOptionsGame::OnInit called. this = %p\n", pluginName, thisptr);

    if (OriginalOnInit)
        OriginalOnInit(thisptr);

    //UIOptionSlider* sliderObj = *(UIOptionSlider**)((uintptr_t)thisptr + 0xA8 * sizeof(void*));  // == 0x540
    UIOptionSlider* sliderObj = *(UIOptionSlider**)((uintptr_t)thisptr + 0x540);
    if (!sliderObj) {
        dbgprintf("[%s] UIOptionSlider pointer MenuOptionsVideo_Fov at 0xA8 is null!\n", pluginName);
        return;
    }

    sliderObj->m_iMaxValue = 40;
    UIOptionSliderHook::AdjustSlider_Hook(sliderObj, 1);
}

void __fastcall UIOptionSliderHook::AdjustSlider_Hook(UIOptionSlider* thisptr, char param)
{
    dbgprintf("[%s] AdjustSlider called. this = %p, param = %i, MaxVal = %i, MinVal = %i\n",pluginName,thisptr,param,thisptr->m_iMaxValue,thisptr->m_iMinValue);

    if (OriginalAdjustSlider)
        OriginalAdjustSlider(thisptr, param);
}


extern "C" __declspec(dllexport) void PreInitialize()
{
    dbgprintf("[%s] PreInitialize\n", pluginName);

    HMODULE hGame = GetModuleHandleA("gamedll_x64_rwdi.dll");
    if (!hGame)
    {
        dbgprintf("[%s] Failed to get game module handle\n", pluginName);
        return;
    }

    auto* pOnInit = reinterpret_cast<void*>((uintptr_t)hGame + 0x1251090);
    auto* pAdjustSlider = reinterpret_cast<void*>((uintptr_t)hGame + 0x117AE90);

    ERRCHECK(MH_Initialize());

    ERRCHECK(MH_CreateHook(pOnInit, &MenuOptionsGameHook::OnInit_Hook, reinterpret_cast<void**>(&MenuOptionsGameHook::OriginalOnInit)));
    ERRCHECK(MH_CreateHook(pAdjustSlider, &UIOptionSliderHook::AdjustSlider_Hook, reinterpret_cast<void**>(&UIOptionSliderHook::OriginalAdjustSlider)));

    ERRCHECK(MH_EnableHook(pOnInit));
    ERRCHECK(MH_EnableHook(pAdjustSlider));
}

//called after CGame::Initialize
extern "C" __declspec(dllexport) void PostInitialize(IGame* pIGame) {
    dbgprintf("[%s] PostInitialize\n", pluginName);
	dbgprintf("IGame Ptr: %p\n", pIGame);
}
