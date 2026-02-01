//
// Created by Brendon on 1/12/2026.
//
#pragma once
#include <windows.h>
#include "engine/Export.h"
#include "engine/Game/IGame.h"

extern "C" ENGINE_API bool Main(void);
extern "C" ENGINE_API int ShowSplashscreen(HINSTANCE hInst, LPCSTR Splash, LPSTR Title, HANDLE Icon);
extern "C" ENGINE_API void HideSplashscreen();
extern "C" ENGINE_API bool InitializeGameScript(LPCSTR GameDll, ULONGLONG param_2);
//InitializeGameScriptFn
extern "C" ENGINE_API void UninitializeGameScript();
extern "C" ENGINE_API IGame *CreateGame(LPCSTR param_1, HINSTANCE hinstance, bool param_3, LPCSTR param_4);
extern "C" ENGINE_API void DestroyGame(__int64 param_1, __int64 param_2, __int64 param_3, __int64 param_4);
//Initialize
//GetEngineVersion
//GetEngineDllVersion
//SetPlatform