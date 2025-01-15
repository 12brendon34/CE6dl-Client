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

    class AssetManager {
    public:
        //RDPMainHeader::Platform
        virtual ULONG SetGame(LPCSTR DW, LPCSTR WD, int Platform, bool, char const*);

        //Stripped
        virtual void SetMountDirs(LPCSTR);

        //sets param_1[1] and param_1[0]; to null when ran, prob stripped or smt
        uint64_t* GetMountDirs(uint64_t* param_1);

        //returns 6
        virtual int64_t GetCurrentPlatform();

        //Stripped, Returns 0 without doing anything
        virtual int64_t SetForceRpackCreationMode();

        //virtual void __thiscall RegRpack(CResourceDataPack*, ttl::string_base<char> const&)
        virtual void RegRpack(void* CResourceDataPack, char const** string_base);
        virtual void UnregRpack(void* CResourceDataPack, char const** string_base);

        virtual void CopyPackData(void* CResourceDataPack);
        virtual void PastePackData(void* CResourceDataPack);

        /* AssetManagerImpl::LoadPackData(char const*, ttl::vector<SRLRResource>&, ttl::vector<EResType::ENUM> const&) */
        virtual void LoadPackData(char const* param_1, long* param_3, long* param_4);
        /* AssetManagerImpl::ChangePackMemory(CResourceDataPack*, ttl::vector<SRLRResource>&, ttl::vector<EResType::ENUM> const&) */
        virtual void ChangePackMemory(void* CResourceDataPack, long* param_3, long* param_4); //calls CResourceDataPack::ChangePackMemoryAfterReload
        virtual void CalcResPackInfo(); //CResourceLoadingRuntime::CalcResPackInfo(CResourceLoadingRuntime::s_This);
        virtual void LoadAssetAutoBuild(char const* param_1, unsigned int param_2, char const*); //last arg unused
        virtual void ReleasePack(void* CResourceDataPack);
        virtual void Shutdown();
        virtual void FixAfterReloadTexture(void* CTexture, void* CTexture_2, void* CResourceDataPack);
        virtual void GetDataPackName(void* CResourceDataPack);

        virtual ~AssetManager() = default;
    };

    using T_GetAssetManager = AssetManager* __ptr64 (*)(void);
    extern T_GetAssetManager GetAssetManager;

    //unused params
    using T_DestroyGame = void (*)(__int64 param_1, __int64 param_2, __int64 param_3, __int64 param_4);
    extern T_DestroyGame DestroyGame;

    using T_UninitializeGameScript = void (*) (void);
    extern T_UninitializeGameScript UninitializeGameScript;

    using T_ShutdownOnlineServices = void (*)(void);
    extern T_ShutdownOnlineServices ShutdownOnlineServices;

    using T_CreateMountHelper = void* (*)(LPCSTR param_1, LPCSTR param_2, LPCSTR param_3);
    extern T_CreateMountHelper CreateMountHelper;

    using T_MountDLC = void(*)(void* pGame, const char** className, __int64* CRTTIVariant);
    extern T_MountDLC MountDLC;
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