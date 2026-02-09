//
// Created by Brendon on 1/12/2026.
//
#pragma once
#include <windows.h>

#include "Editor/IEngineImpl.h"
#include "engine/Export.h"
#include "engine/Game/IGame.h"
#include "engine/filesystem/LogSettings.h"

extern "C" ENGINE_API bool Main(void);
extern "C" ENGINE_API int ShowSplashscreen(HINSTANCE hInst, LPCSTR Splash, LPSTR Title, HANDLE Icon);
extern "C" ENGINE_API void HideSplashscreen();
extern "C" ENGINE_API bool InitializeGameScript(LPCSTR GameDll, ULONGLONG param_2);
//InitializeGameScriptFn
extern "C" ENGINE_API void UninitializeGameScript();
extern "C" ENGINE_API IGame *CreateGame(LPCSTR param_1, HINSTANCE hinstance, bool param_3, LPCSTR param_4);
extern "C" ENGINE_API void DestroyGame(__int64 param_1, __int64 param_2, __int64 param_3, __int64 param_4);

typedef void(__cdecl* LogCallback_t)(Log::ELevel::TYPE, const char*, const char*);
extern "C" ENGINE_API IEngineImpl* Initialize(
    HINSTANCE        hInstance,
    HWND             hwndMainWindow,
    HWND             hwndMsgTarget,
    void*            pEngineHelper,
    const char*      gameName, //game class but I don't feel like renaming it, (GameDI and such)
    const char*      gameDllName,
    const char*      videoSettingsPath,  // "Out/Settings/EditorVideo.scr"
    const char*      audioSettingsPath,  // "Out/Settings/EditorAudio.scr"
    LogCallback_t    logCallback,
    void*            pUserContext //loading progress class but I don't feel like renaming
);
//GetEngineVersion
//GetEngineDllVersion
//SetPlatform