#include <pch.h>
#include "Link.h"

namespace Engine
{
    t_Main Main = nullptr;
    T_ShowSplashscreen ShowSplashscreen = nullptr;
    T_HideSplashscreen HideSplashscreen = nullptr;
    T_InitializeOnlineServices InitializeOnlineServices = nullptr;
    T_InitializeGameScript InitializeGameScript = nullptr;
    T_CreateGame CreateGame = nullptr;
    T_SetRootDirectory SetRootDirectory = nullptr;
    T_Initialize Initialize = nullptr;
    T_OnPaint OnPaint = nullptr;
    T_GetAssetManager GetAssetManager = nullptr;
    T_AssetManager AssetManager = nullptr;
    T_DestroyGame DestroyGame = nullptr;
    T_ShutdownOnlineServices ShutdownOnlineServices = nullptr;
    T_UninitializeGameScript UninitializeGameScript = nullptr;
}

namespace Filesystem
{
    T_WriteFullDump WriteFullDump = nullptr;
    T_IsFullPath IsFullPath = nullptr;
    T_Init Init = nullptr;
    T_Add_Source Add_Source = nullptr;
    T_CrashClose CrashClose = nullptr;
    T_Shutdown Shutdown = nullptr;
}

bool LoadGameLibarys() {
    const HMODULE engine = Utils::LoadLibrarySimple("engine_x64_rwdi.dll");
    const HMODULE filesystem = Utils::LoadLibrarySimple("filesystem_x64_rwdi.dll");

    if (!engine || !filesystem) {// || !gamedll) {
        dbgprintf("One or more DLLs failed to load. Exiting.");
        return false;
    }

    //engine_x64_rwdi.dll
    Engine::Main = (Engine::t_Main)GetProcAddress(engine, "Main");
    Engine::ShowSplashscreen = (Engine::T_ShowSplashscreen)GetProcAddress(engine, "ShowSplashscreen");
    Engine::HideSplashscreen = (Engine::T_HideSplashscreen)GetProcAddress(engine, "HideSplashscreen");
    Engine::InitializeOnlineServices = (Engine::T_InitializeOnlineServices)GetProcAddress(engine, "?InitializeOnlineServices@IGame@@SA_NPEAX@Z");
    Engine::InitializeGameScript = (Engine::T_InitializeGameScript)GetProcAddress(engine, "InitializeGameScript");
    Engine::CreateGame = (Engine::T_CreateGame)GetProcAddress(engine, "CreateGame");
    Engine::SetRootDirectory = (Engine::T_SetRootDirectory)GetProcAddress(engine, "?SetRootDirectory@IGame@@QEAA_NPEBD@Z");
    Engine::Initialize = (Engine::T_Initialize)GetProcAddress(engine, "?Initialize@IGame@@QEAAHPEADHPEAUHICON__@@1KKPEAVIProgressIndicator@@@Z");
    Engine::OnPaint = (Engine::T_OnPaint)GetProcAddress(engine, "?OnPaint@IGame@@QEAAXXZ");
    Engine::GetAssetManager = (Engine::T_GetAssetManager)GetProcAddress(engine, "?GetAssetManager@@YAPEAUAssetManager@@XZ");
    Engine::DestroyGame = (Engine::T_DestroyGame)GetProcAddress(engine, "DestroyGame");
    Engine::ShutdownOnlineServices = (Engine::T_ShutdownOnlineServices)GetProcAddress(engine, "?ShutdownOnlineServices@IGame@@SAXXZ");
    Engine::UninitializeGameScript = (Engine::T_UninitializeGameScript)GetProcAddress(engine, "UninitializeGameScript");

    //filesystem_x64_rwdi.dll
    Filesystem::WriteFullDump = (Filesystem::T_WriteFullDump)GetProcAddress(filesystem, "?WriteFullDump@@YAXKPEAU_EXCEPTION_POINTERS@@PEBD_NPEAD@Z");
    Filesystem::IsFullPath = (Filesystem::T_IsFullPath)GetProcAddress(filesystem, "?is_full_path@fs@@YA_NPEBD@Z");//Filesystem::IsFullPath looks better than fs::is_full_path
    Filesystem::Init = (Filesystem::T_Init)GetProcAddress(filesystem, "?init@fs@@YA_NPEBDW4ENUM@FFSAddSourceFlags@@0_N2PEAPEBD@Z");
    Filesystem::Add_Source = (Filesystem::T_Add_Source)GetProcAddress(filesystem, "?add_source@fs@@YA_NPEBDW4ENUM@FFSAddSourceFlags@@@Z");
    Filesystem::CrashClose = (Filesystem::T_CrashClose)GetProcAddress(filesystem, "?CrashClose@@YAXXZ");
    Filesystem::Shutdown = (Filesystem::T_Shutdown)GetProcAddress(filesystem, "?shutdown@fs@@YAXXZ");

    return true;
}
