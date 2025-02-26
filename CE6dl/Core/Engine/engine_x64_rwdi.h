#pragma once
#include "pch.h"
#include "IGame.h"

#ifdef _WIN32
#define DLL_EXPORT __declspec(dllimport) // For importing the function
#else
#define DLL_EXPORT
#endif

#pragma once
/*
struct IGSObject {
    //undefined field0_0x0;
    //undefined field1_0x1;
    //undefined field2_0x2;
    //undefined field3_0x3;
    int m_PointerGuardedCounter;
    struct CGSObject* m_CGSO;
};

struct CRTTIVoidMethod {
    void* m_Method;
};

template <typename T>
struct CRTTIVoidFunctor; //idk generic stuff

template <>
struct CRTTIVoidFunctor<IGSObject> {
    struct IGSObject* object;
    struct CRTTIVoidMethod* method;
};
*/

namespace Mount {
    class IMountHelper {
        //figure out what's the constructor and destructor so 'Mount::IMountHelper' has virtual functions but non - virtual destructor
        virtual void Func_00(); // FUN_180257140
        virtual void Func_01(); // LAB_180257230
        virtual void Func_02(); // FUN_180258CB0
        virtual void Func_03(); // FUN_180258D20
        virtual void Func_04(); // LAB_1807D6F10
        virtual void Func_05(); // FUN_1802587E0
        virtual void Func_06(); // FUN_180258AE0
        virtual void Func_07(); // LAB_180258B00
        virtual void Func_08(); // FUN_1802570D0
        virtual void Func_09(); // FUN_180259520
        virtual void Func_10(); // LAB_180259A50
        virtual void Func_11(); // LAB_180259AD0
        virtual void Func_12(); // Stripped
        virtual void Func_13(); // LAB_18025A550
        virtual void Func_14(); // DAT_1808EAAD0
    };

    IMountHelper* __cdecl CreateMountHelper(const char* param1, const char* param2, const char* param3);
    void __cdecl DestroyMountHelper(IMountHelper* helper);
}

struct AssetManager {
    //RDPMainHeader::Platform
    virtual ULONG SetGame(LPCSTR DW, LPCSTR WD, int Platform, bool, char const*);

    //Unsure
    virtual void FUN_1803e5590(); //SetMountDirs
    virtual void FUN_1803e55a0(); //GetMountDirs
    virtual void Stripped();
    virtual void FUN_1803e5a00(); //GetCurrentPlatform
    virtual void FUN_1803e55d0(); //SetForceRpackCreationMode

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

    /*
     * addr  AssetManagerImpl::Shutdown
     * addr AssetManagerImpl::FixAfterReloadTexture
     * addr AssetManagerImpl::GetDataPackName
     */
    virtual void FUN_1803e5160();
    virtual void FUN_1803e5680();
    virtual void FUN_1803e3a00();
    virtual void GetMaxValue(); //IDK why this here
    virtual void FUN_1803eb1d0();
    virtual void FUN_1803eb200();
    virtual void FUN_1803e37d0();

    virtual void LoadAsset(char const* Path, UINT param_2, char const* param_3);

    virtual ~AssetManager() = default;
};

struct AssetManager* __cdecl GetAssetManager(void);


//I still dk a better way
//using T_MountDLC = void(*)(IGame* pGame, const char** className, __int64* CRTTIVariant);

//same sig hopefully
extern "C" DLL_EXPORT bool Main(void);
extern "C" DLL_EXPORT int ShowSplashscreen(HINSTANCE hInst, LPCSTR Splash, LPSTR Title, HANDLE Icon);
extern "C" DLL_EXPORT void HideSplashscreen();

extern "C" DLL_EXPORT bool InitializeGameScript(LPCSTR GameDll, ULONGLONG param_2);
extern "C" DLL_EXPORT IGame* CreateGame(LPCSTR param_1, HINSTANCE hinstance, bool param_3, LPCSTR param_4);
extern "C" DLL_EXPORT void DestroyGame(__int64 param_1, __int64 param_2, __int64 param_3, __int64 param_4);
extern "C" DLL_EXPORT void UninitializeGameScript();