#pragma once
#include "igame.h"

#define DLL_EXPORT __declspec(dllimport)

namespace Mount {
    class IMountHelper {

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

    virtual void RegRpack(void* CResourceDataPack, char const** string_base);
    virtual void UnregRpack(void* CResourceDataPack, char const** string_base);
    virtual void CopyPackData(void* CResourceDataPack);
    virtual void PastePackData(void* CResourceDataPack);
    virtual void LoadPackData(char const* param_1, long* param_3, long long* param_4);
    virtual void ChangePackMemory(void* CResourceDataPack, long* param_3, long* param_4);
    virtual void CalcResPackInfo();
    virtual void LoadAssetAutoBuild(char const* param_1, unsigned int param_2, char const*);
    virtual void ReleasePack(void* CResourceDataPack);

    virtual void FUN_1803e5160();
    virtual void FUN_1803e5680();
    virtual void FUN_1803e3a00();
    virtual void GetMaxValue();
    virtual void FUN_1803eb1d0();
    virtual void FUN_1803eb200();
    virtual void FUN_1803e37d0();

    virtual void LoadAsset(char const* Path, UINT param_2, char const* param_3);

    virtual ~AssetManager() = default;
};

class CMaterialsPack {

};

class CMaterialMgr {
public:
    virtual CMaterialsPack* LoadPack(LPCSTR Path, int ELoadPackOptions);

    /*
    0147b9c0 a0 14 ec        addr       CMaterialMgr::FreePack
    0147b9c8 f0 06 ec        addr       CMaterialMgr::LoadMaterial
    0147b9d0 80 d8 eb        addr       CMaterialMgr::AddMaterialReference
    0147b9d8 80 15 ec        addr       CMaterialMgr::ReleaseMaterial
    0147b9e0 a0 d7 eb        addr       CMaterialMgr::DeleteWhenReleased
    0147b9e8 60 dc eb        addr       CMaterialMgr::FindMaterial
    0147b9f0 30 d7 eb        addr       CMaterialMgr::IsDefaultMaterial
    0147b9f8 a0 d8 eb        addr       CMaterialMgr::GetDefaultMaterial
    0147ba00 90 18 ec        addr       CMaterialMgr::DumpMaterials
    0147ba08 b0 d7 eb        addr       CMaterialMgr::DumpMaterialsNames
    0147ba10 30 3a ec        addr       CMaterialMgr::GetTechniqueName
    0147ba18 00 eb eb        addr       CMaterialMgr::OnLevelExit
    0147ba20 30 2d ec        addr       CMaterialMgr::ReloadLocalMaterials
    0147ba28 20 3a ec        addr       CMaterialMgr::GetTechniqueID
    0147ba30 40 d7 eb        addr       CMaterialMgr::SetUniqueDefMatMode
    0147ba38 f0 d7 eb        addr       CMaterialMgr::GetMaterials
    0147ba40 d0 d8 eb        addr       CMaterialMgr::AcquireLoadedMaterialVersions
    0147ba48 c0 03 ec        addr       CMaterialMgr::CloneMaterial
    0147ba50 50 d7 eb        addr       CMaterialMgr::CloneMaterialByName
    0147ba58 a0 dd eb        addr       CMaterialMgr::ObtainTextuerQuality
    0147ba60 a0 fc eb        addr       CMaterialMgr::VerifyTexturesArePresent
    */

    virtual ~CMaterialMgr() = default;
};

struct AssetManager* __cdecl GetAssetManager(void);

extern "C" DLL_EXPORT bool Main(void);
extern "C" DLL_EXPORT int ShowSplashscreen(HINSTANCE hInst, LPCSTR Splash, LPSTR Title, HANDLE Icon);
extern "C" DLL_EXPORT void HideSplashscreen();
extern "C" DLL_EXPORT bool InitializeGameScript(LPCSTR GameDll, ULONGLONG param_2);
extern "C" DLL_EXPORT IGame* CreateGame(LPCSTR param_1, HINSTANCE hinstance, bool param_3, LPCSTR param_4);
extern "C" DLL_EXPORT void DestroyGame(__int64 param_1, __int64 param_2, __int64 param_3, __int64 param_4);
extern "C" DLL_EXPORT void UninitializeGameScript();