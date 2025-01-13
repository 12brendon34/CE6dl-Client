#pragma once
#include "../Utils/Utils.h"

bool LoadGameLibarys();

namespace Engine {
    using t_Main = int (*)(void);
    extern t_Main Main;

    using T_ShowSplashscreen = int (*)(HINSTANCE hInst, LPCSTR Splash, LPSTR Title, HANDLE Icon);
    extern T_ShowSplashscreen ShowSplashscreen;

    using T_HideSplashscreen = void (*)(void);
    extern T_HideSplashscreen HideSplashscreen;

    using T_InitializeOnlineServices = void* (*)(void);
    extern T_InitializeOnlineServices InitializeOnlineServices;

    using T_InitializeGameScript = void* (*)(LPCSTR GameDll, ULONGLONG param_2);
    extern T_InitializeGameScript InitializeGameScript;

    //param_3 and param_4 Unused?
    using T_CreateGame = void* (*)(LPCSTR param_1, HINSTANCE hinstance, bool param_3, LPCSTR param_4);
    extern T_CreateGame CreateGame;

    using T_SetRootDirectory = bool (*)(void* pGame, LPCSTR WorkingDirectory);
    extern T_SetRootDirectory SetRootDirectory;

    using T_Initialize = int (*)(void* pGame, char* lpCmdLine, int nCmdShow, HANDLE SmallIcon, HANDLE LargeIcon, ULONG param_5, ULONG param_6, void* IProgressIndicator);
    extern T_Initialize Initialize;

    using T_OnPaint = void* (*)(void*);
    extern T_OnPaint OnPaint;

    using T_GetAssetManager = void* __ptr64 (*)(void);
    extern T_GetAssetManager GetAssetManager;

    using T_AssetManager = int(*)(void* param_1, LPCSTR DW, LPCSTR WD, int platform, void* param_5, char* param_6);
    extern T_AssetManager AssetManager;

    //unused params
    using T_DestroyGame = void (*)(__int64 param_1, __int64 param_2, __int64 param_3, __int64 param_4);
    extern T_DestroyGame DestroyGame;

    using T_UninitializeGameScript = void (*) (void);
    extern T_UninitializeGameScript UninitializeGameScript;

    using T_ShutdownOnlineServices = void (*)(void);
    extern T_ShutdownOnlineServices ShutdownOnlineServices;
}

namespace Filesystem
{
    using T_WriteFullDump = void(*)(ULONG nExceptionCode, _EXCEPTION_POINTERS* pException, char* param_3, bool MiniDump, char* param_5);
    extern T_WriteFullDump WriteFullDump;

    using T_IsFullPath = bool(*)(LPCSTR Path);
    extern T_IsFullPath IsFullPath;

    //param_3 and higher appear unused, must be stripped
    using T_Init = bool(*)(LPCSTR Path, int FFSAddSourceFlags, LPCSTR Cache, bool param_4, bool param_5, char const** param_6);
    extern T_Init Init;

    using T_Add_Source = bool(*)(LPCSTR Path, int FFSAddSourceFlags);
    extern T_Add_Source Add_Source;

    using T_CrashClose = void (*)(void);
    extern T_CrashClose CrashClose;

    using T_Shutdown = void (*)(void);
    extern T_Shutdown Shutdown;
}