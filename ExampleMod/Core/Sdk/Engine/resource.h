#pragma once

//#include <cstdint>
//#include "pch.h"
#include "../TTL.h"

// Forward declarations
struct RDPResourceEntryHeader;
struct RDPLogicalResourceEntryHeader;

class ETextureQuality {
public:
    enum TYPE {
        DONT_CARE = 1,
        VERY_LOW = 2,
        LOW = 3,
        HIGH = 4
    };
};

class EResType {
public:
    enum ENUM {
        restype_Invalid = 0,
        restype_Mesh = 16,
        ressubtype_MeshFixups = 17,
        restype_Skin = 18,
        ressubtype_SkinFixups = 19,
        restype_Texture = 32,
        ressubtype_TextureBitmapData = 33,
        ressubtype_TextureMipBitmapData = 34,
        restype_Material = 48,
        ressubtype_Shader = 49,
        ressubtype_MaterialFixups = 50,
        ressubtype_MaterialTextures = 51,
        restype_Animation = 64,
        ressubtype_AnimationStream = 65,
        ressubtype_AnimationScr = 66,
        ressubtype_AnimationScrFixups = 67,
        restype_anm2_metadata = 68,
        restype_anm2_payload = 69,
        restype_anm2_fallback = 70,
        restype_Fx = 80,
        restype_Lightmap = 96,
        restype_Flash = 97,
        restype_Sound = 101,
        ressubtype_Music = 102,
        ressubtype_Speech = 103,
        ressubtype_SFX_stream = 104,
        ressubtype_SFX_local = 105,
        restype_DensityMap = 112,
        restype_HeightMap = 128,
        restype_Mimics = 144,
        restype_PathMap = 160,
        restype_Phonemes = 176,
        restype_StaticGeometry = 192,
        ressubtype_StaticGeomSetup = 193,
        ressubtype_StaticGeomFixups = 194,
        ressubtype_StaticGeomSetupFixups = 195,
        restype_TextData = 208,
        restype_BinaryData = 224,
        restype_VertexData = 240,
        restype_IndexData = 241,
        restype_VertexDynamicData = 242,
        restype_TinyObjects = 248,
        ressubtype_TinyObjectsFixUps = 249,
        ressubtype_TinyObjectsDensityMap = 250,
        restype_BuilderInformation = 255
    };
};

enum Status {
    Ready = 0,
    Queued = 1,
    Loading = 2,
    Complete = 3,
    Cancelled = 4
};

class __declspec(dllimport) CResourceDataPack {
public:
    CResourceDataPack();
    void AddRpackReference();
    void ClosePackFiles();
    void DeleteThis();
    const char* GetPackName() const;
    unsigned int ReleaseRpackReference();
};

class __declspec(dllimport) CResourceLoadingRuntime {
public:
    struct StreamOp {
        Status m_Status;
        uint32_t m_RefCount;
    };

    struct SOnDemandResource {
        struct SubResource {
            RDPResourceEntryHeader* m_Entry;
            StreamOp* m_StreamOp;
            void* m_Memory;
            uint32_t m_ReleaseAfterRegister : 1;
        };

        ttl::vectorm<40, SubResource> m_SubResources;
        CResourceDataPack* m_Container;
        RDPLogicalResourceEntryHeader* m_Entry;
        long m_LeftToLoad;
        Status m_Status;
        void* m_RegisterData;
        int m_Priority;
        bool m_Failed;
        ttl::string_base<char> m_ResourceName;
    };

    enum class StreamStatus {
        Loading = 0,
        Succeeded = 1,
        Failed = 2
    };

    enum class WaitFlags : uint32_t {
        None = 0,
        WaitForEvent = 1
    };

    bool CancelResource(StreamOp* op, bool forceCancel);
    static CResourceLoadingRuntime* Get();
    int GetSkipMipLevelsBasedOnTexQuality(ETextureQuality::TYPE quality) const;
    void OnDemandEvictAll();
    void OnDemandEvictAllFromPack(CResourceDataPack* pack);
    bool OnDemandIsLoaded(SOnDemandResource* res, bool& outLoaded);
    SOnDemandResource* OnDemandSchedule(CResourceDataPack* pack, const char* resourceName, EResType::ENUM type, int priority, WaitFlags flags);
    void OnDemandUnload(SOnDemandResource* res);
    void OnDemandWaitForResource(SOnDemandResource* res, bool& outStatus);

    bool StreamResource(
        StreamOp* op,
        CResourceDataPack* pack,
        const RDPResourceEntryHeader* resourceHeader,
        void* outputBuffer,
        void (*callback)(void* context, StreamStatus status, unsigned int resultCode),
        void* callbackContext,
        int param1,
        int param2,
        int param3
    );
};
