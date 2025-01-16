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


    //AssetManagerImpl has some other stuff not in this table, that's fine for my useage
    class AssetManager {
    public:
        //RDPMainHeader::Platform
        virtual ULONG SetGame(LPCSTR DW, LPCSTR WD, int Platform, bool, char const*);

        //I guess just don't use these
        virtual void FUN_1803e5590();
        virtual void FUN_1803e55a0();
        virtual void Stripped();
        virtual void FUN_1803e5a00();
        virtual void FUN_1803e55d0();

        //virtual void __thiscall RegRpack(CResourceDataPack*, ttl::string_base<char> const&)
        virtual void RegRpack(void* CResourceDataPack, char const** string_base);
        virtual void UnregRpack(void* CResourceDataPack, char const** string_base);

        virtual void CopyPackData(void* CResourceDataPack);
        virtual void PastePackData(void* CResourceDataPack);

        /* AssetManagerImpl::LoadPackData(char const*, ttl::vector<SRLRResource>&, ttl::vector<EResType::ENUM> const&) */
        virtual void LoadPackData(char const* param_1, long* param_3, long long* param_4);

        /* AssetManagerImpl::ChangePackMemory(CResourceDataPack*, ttl::vector<SRLRResource>&, ttl::vector<EResType::ENUM> const&) */
        virtual void ChangePackMemory(void* CResourceDataPack, long* param_3, long* param_4); //calls CResourceDataPack::ChangePackMemoryAfterReload
        virtual void CalcResPackInfo(); //CResourceLoadingRuntime::CalcResPackInfo(CResourceLoadingRuntime::s_This);
        virtual void LoadAssetAutoBuild(char const* param_1, unsigned int param_2, char const*); //last arg unused
        virtual void ReleasePack(void* CResourceDataPack);

        virtual void FUN_1803e5160();
        virtual void FUN_1803e5680();
        virtual void FUN_1803e3a00();
        virtual void GetMaxValue(); //IDK why this here
        virtual void FUN_1803eb1d0();
        virtual void FUN_1803eb200();
        virtual void FUN_1803e37d0();

        virtual void LoadAsset(char const* Path, UINT param_2, char const* param_3);
        /*
        //Stripped
        virtual void SetMountDirs(LPCSTR);

        //sets param_1[1] and param_1[0]; to null when ran, prob stripped or smt
        uint64_t* GetMountDirs(uint64_t* param_1);

        //returns 6
        virtual int64_t GetCurrentPlatform();

        //Stripped, Returns 0 without doing anything
        virtual int64_t SetForceRpackCreationMode();

        virtual void Shutdown();
        virtual void FixAfterReloadTexture(void* CTexture, void* CTexture_2, void* CResourceDataPack);
        virtual void GetDataPackName(void* CResourceDataPack);


        18086e2a0 60 51 3e        addr       FUN_1803e5160
        18086e2a8 80 56 3e        addr       FUN_1803e5680
        18086e2b0 00 3a 3e        addr       FUN_1803e3a00
        18086e2b8 f0 f5 01        addr       CRTTIFieldTyped<>::GetMaxValue
        18086e2c0 d0 b1 3e        addr       FUN_1803eb1d0
        18086e2c8 00 b2 3e        addr       FUN_1803eb200
        18086e2d0 d0 37 3e        addr       FUN_1803e37d0
        18086e2d8 10 57 3e        addr       AssetManagerImpl::LoadAsset
        18086e2e0 a0 67 3e        addr       FUN_1803e67a0
        18086e2e8 40 68 3e        addr       FUN_1803e6840
        18086e2f0 b0 68 3e        addr       LAB_1803e68b0
        18086e2f8 10 71 3e        addr       FUN_1803e7110
        18086e300 a0 72 3e        addr       LAB_1803e72a0
        18086e308 50 75 3e        addr       FUN_1803e7550
        18086e310 80 77 3e        addr       FUN_1803e7780
        18086e318 20 7b 3e        addr       LAB_1803e7b20
        18086e320 70 7f 3e        addr       FUN_1803e7f70
        18086e328 90 66 3e        addr       FUN_1803e6690
        18086e330 30 60 3e        addr       AssetManagerImpl::RebuildAssets
        18086e338 c0 bb 3e        addr       LAB_1803ebbc0
        */

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