#pragma once
#include <pch.h>
#include "../TTL.h"

typedef struct {
    uint8_t type;
    uint8_t type_index;
    uint8_t format;
    uint8_t stream;
} VertexElementData;

typedef union {
    VertexElementData details;
    uint32_t uint_format;
} VertexElementUnion;

typedef struct {
    VertexElementUnion element;
    uint32_t usage_vtxmp;
} CVertexElement;

class EMaterialLoadFlags{
public:
    typedef enum TYPE {
        SKINNING = 1,
        MORPHING = 2,
        MORPH_TARGETS = 4,
        INSTANCING_VS = 8,
        INSTANCING_SM30 = 16,
        LIGHTMAPS_VERTEX = 32,
        LIGHTMAPS_PIXEL = 64,
        WORLD_SPACE = 128,
        INSTANCING_VSPLUS = 256,
        SKINNING_ONE_BONE = 512,
        DISTANCE_FADE = 1024,
        HIDING = 2048,
        SOFTWARE_VP = 4096,
        INSTANCING_DIP = 8192,
        ANYTHING = 65535
    } TYPE;
};


class __declspec(dllimport) CMaterialsPack {
public:
    enum ELoadFlags {};

public:
    CMaterialsPack();
    ~CMaterialsPack();
    //bool FetchMaterialTexturesInformationFromReferences(MatID const&, ttl::vector<char const*>&) const;
    bool FetchMaterialTexturesInformationFromReferences(long const&, ttl::vector<char const*>&) const;
    bool FetchMaterialVertexInputs(CVertexElement*, unsigned int&, char const*, EMaterialLoadFlags::TYPE) const;
    bool Load(char const*, CMaterialsPack::ELoadFlags);
};

class CMaterialMgr {
public:
    virtual CMaterialsPack* LoadPack(LPCSTR Path, int ELoadPackOptions);
    virtual void FreePack(class CMaterialsPack* param_1, int param_2);
    virtual class IMaterial* LoadMaterial(uint64_t param_2, char* param_3, int param_4);
    virtual void AddMaterialReference(class IMaterial* param_2);
    virtual void ReleaseMaterial(uint64_t param_1);
    //stripped function
    virtual uint64_t DeleteWhenReleased();
    virtual long FindMaterial(char* param_1, uint64_t param_2);

    //unchecked, may not be accurate
    virtual bool IsDefaultMaterial(long param_1);
    virtual class IMaterial* GetDefaultMaterial();
    virtual void DumpMaterials(uint64_t param_1);
    virtual void DumpMaterialsNames();
    virtual void GetTechniqueName(byte param_1);
    virtual void OnLevelExit();
    virtual int ReloadLocalMaterials();
    virtual void GetTechniqueID(char* param_1);
    virtual void SetUniqueDefMatMode(class CMaterialMgr* param_2);
    virtual void GetMaterials(long* param_1);
    virtual uint AcquireLoadedMaterialVersions(uint64_t param_2_00, int* param_2, uint param_3);
    virtual uint64_t CloneMaterial(class IMaterial* param_1, char* param_2);
    virtual uint64_t CloneMaterialByName(uint64_t param_1, uint64_t param_2, uint64_t param_3);
    virtual uint64_t ObtainTextuerQuality(void* param_1, uint64_t param_2);
    virtual class CMaterialMgr* VerifyTexturesArePresent(long param_1, char param_2);
    //virtual void operator.delete[]();


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