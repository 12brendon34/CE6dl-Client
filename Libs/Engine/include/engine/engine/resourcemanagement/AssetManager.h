//
// Created by Brendon on 1/12/2026.
//
#pragma once

struct AssetManager {
    //RDPMainHeader::Platform
    virtual bool SetGame(LPCSTR DW, LPCSTR WD, int Platform, bool, char const *);

    //Unsure
    virtual void FUN_1803e5590(); //SetMountDirs
    virtual void FUN_1803e55a0(); //GetMountDirs
    virtual void Stripped();
    virtual void FUN_1803e5a00(); //GetCurrentPlatform
    virtual void FUN_1803e55d0(); //SetForceRpackCreationMode
    virtual void RegRpack(void *CResourceDataPack, char const **string_base);
    virtual void UnregRpack(void *CResourceDataPack, char const **string_base);
    virtual void CopyPackData(void *CResourceDataPack);
    virtual void PastePackData(void *CResourceDataPack);
    virtual void LoadPackData(char const *param_1, long *param_3, long long *param_4);
    virtual void ChangePackMemory(void *CResourceDataPack, long *param_3, long *param_4);
    virtual void CalcResPackInfo();
    virtual void LoadAssetAutoBuild(char const *param_1, unsigned int param_2, char const *);
    virtual void ReleasePack(void *CResourceDataPack);
    virtual void FUN_1803e5160();
    virtual void FUN_1803e5680();
    virtual void FUN_1803e3a00();
    virtual void GetMaxValue();
    virtual void FUN_1803eb1d0();
    virtual void FUN_1803eb200();
    virtual void FUN_1803e37d0();
    virtual void LoadAsset(char const *Path, UINT param_2, char const *param_3);
    virtual ~AssetManager() = default;
};

AssetManager * __cdecl GetAssetManager();