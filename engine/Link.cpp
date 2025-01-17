#include <pch.h>
#include "Link.h"

namespace Engine
{
    HMODULE Library;

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
    T_DestroyGame DestroyGame = nullptr;
    T_ShutdownOnlineServices ShutdownOnlineServices = nullptr;
    T_UninitializeGameScript UninitializeGameScript = nullptr;
    T_CreateMountHelper CreateMountHelper = nullptr;
    T_MountDLC MountDLC = nullptr;
}

namespace Filesystem
{
    HMODULE Library;

    T_WriteFullDump WriteFullDump = nullptr;
    T_IsFullPath IsFullPath = nullptr;
    T_Init Init = nullptr;
    T_Add_Source Add_Source = nullptr;
    T_CrashClose CrashClose = nullptr;
    T_Shutdown Shutdown = nullptr;
}

bool LoadGameLibrarys() {
    Engine::Library = Utils::LoadLibrarySimple("engine_x64_rwdi.dll");
    Filesystem::Library = Utils::LoadLibrarySimple("filesystem_x64_rwdi.dll");

    if (!Engine::Library || !Filesystem::Library) {// || !gamedll) {
        dbgprintf("One or more DLLs failed to load. Exiting.");
        return false;
    }

    //engine_x64_rwdi.dll
    Engine::Main = (Engine::t_Main)GetProcAddress(Engine::Library, "Main");
    Engine::ShowSplashscreen = (Engine::T_ShowSplashscreen)GetProcAddress(Engine::Library, "ShowSplashscreen");
    Engine::HideSplashscreen = (Engine::T_HideSplashscreen)GetProcAddress(Engine::Library, "HideSplashscreen");
    Engine::InitializeOnlineServices = (Engine::T_InitializeOnlineServices)GetProcAddress(Engine::Library, "?InitializeOnlineServices@IGame@@SA_NPEAX@Z");
    Engine::InitializeGameScript = (Engine::T_InitializeGameScript)GetProcAddress(Engine::Library, "InitializeGameScript");
    Engine::CreateGame = (Engine::T_CreateGame)GetProcAddress(Engine::Library, "CreateGame");
    Engine::SetRootDirectory = (Engine::T_SetRootDirectory)GetProcAddress(Engine::Library, "?SetRootDirectory@IGame@@QEAA_NPEBD@Z");
    Engine::Initialize = (Engine::T_Initialize)GetProcAddress(Engine::Library, "?Initialize@IGame@@QEAAHPEADHPEAUHICON__@@1KKPEAVIProgressIndicator@@@Z");
    Engine::OnPaint = (Engine::T_OnPaint)GetProcAddress(Engine::Library, "?OnPaint@IGame@@QEAAXXZ");
    Engine::GetAssetManager = (Engine::T_GetAssetManager)GetProcAddress(Engine::Library, "?GetAssetManager@@YAPEAUAssetManager@@XZ");
    Engine::DestroyGame = (Engine::T_DestroyGame)GetProcAddress(Engine::Library, "DestroyGame");
    Engine::ShutdownOnlineServices = (Engine::T_ShutdownOnlineServices)GetProcAddress(Engine::Library, "?ShutdownOnlineServices@IGame@@SAXXZ");
    Engine::UninitializeGameScript = (Engine::T_UninitializeGameScript)GetProcAddress(Engine::Library, "UninitializeGameScript");
    Engine::CreateMountHelper = (Engine::T_CreateMountHelper)GetProcAddress(Engine::Library, "?CreateMountHelper@Mount@@YAPEAVIMountHelper@1@PEBD00@Z");

    //filesystem_x64_rwdi.dll
    Filesystem::WriteFullDump = (Filesystem::T_WriteFullDump)GetProcAddress(Filesystem::Library, "?WriteFullDump@@YAXKPEAU_EXCEPTION_POINTERS@@PEBD_NPEAD@Z");
    Filesystem::IsFullPath = (Filesystem::T_IsFullPath)GetProcAddress(Filesystem::Library, "?is_full_path@fs@@YA_NPEBD@Z");//Filesystem::IsFullPath looks better than fs::is_full_path
    Filesystem::Init = (Filesystem::T_Init)GetProcAddress(Filesystem::Library, "?init@fs@@YA_NPEBDW4ENUM@FFSAddSourceFlags@@0_N2PEAPEBD@Z");
    Filesystem::Add_Source = (Filesystem::T_Add_Source)GetProcAddress(Filesystem::Library, "?add_source@fs@@YA_NPEBDW4ENUM@FFSAddSourceFlags@@@Z");
    Filesystem::CrashClose = (Filesystem::T_CrashClose)GetProcAddress(Filesystem::Library, "?CrashClose@@YAXXZ");
    Filesystem::Shutdown = (Filesystem::T_Shutdown)GetProcAddress(Filesystem::Library, "?shutdown@fs@@YAXXZ");

    return true;
}
