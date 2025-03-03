#pragma once
#include "pch.h"
#include "../TTL.h"

class CResourceLoadingRuntime {
private:
    typedef void(__fastcall* CResourceLoadingRuntimeConstructor)(void*);

public:
    // Fixed return type to pointer
    static CResourceLoadingRuntime* Create()
    {
        CResourceLoadingRuntime* pCVar1 = (CResourceLoadingRuntime*)malloc(0x248);

        if (pCVar1 != nullptr) {
            HMODULE hModule = LoadLibraryA("engine_x64_rwdi.dll");
            if (!hModule) {
                free(pCVar1);
                return nullptr;
            }

            uintptr_t funcAddress = (uintptr_t)hModule + 0x407A70; // Assuming fixed offset
            CResourceLoadingRuntimeConstructor ctor = (CResourceLoadingRuntimeConstructor)funcAddress;

            ctor(pCVar1);

            return pCVar1;
        }
        return nullptr;
    }

    //bool CancelResource(struct CResourceLoadingRuntime::StreamOp*, bool);
    __declspec(dllimport) static class CResourceLoadingRuntime* __ptr64 Get(void);
    //int GetSkipMipLevelsBasedOnTexQuality(enum ETextureQuality::TYPE) const;
    __declspec(dllimport) void OnDemandEvictAll(void);
    __declspec(dllimport) void OnDemandEvictAllFromPack(class CResourceDataPack*);
    //bool OnDemandIsLoaded(struct CResourceLoadingRuntime::SOnDemandResource*, bool&);
    //struct CResourceLoadingRuntime::SOnDemandResource* __ptr64 OnDemandSchedule(class CResourceDataPack*, char const*, enum EResType::ENUM, int, enum CResourceLoadingRuntime::WaitFlags);
    //void OnDemandUnload(struct CResourceLoadingRuntime::SOnDemandResource*);
    //void OnDemandWaitForResource(struct CResourceLoadingRuntime::SOnDemandResource*, bool&);
    //bool StreamResource(struct CResourceLoadingRuntime::StreamOp*, class CResourceDataPack*, struct RDPResourceEntryHeader const*, void*, void(__cdecl*);



    //vtable
    virtual ~CResourceLoadingRuntime();
    virtual void Stripped1();
    virtual int LAB_1803ffd60() {
        return 0x7fffffff;
    }
    virtual void LAB_180404970(int param_2);

    //stripped
    virtual void Stripped2();
    virtual void Stripped3();
    virtual void Stripped4();
    virtual void Stripped5();
    virtual void Stripped6();
    virtual void Stripped7();
    virtual void Stripped8();
    virtual void Stripped9();
    virtual void Stripped10();
    virtual void Stripped11();

    virtual bool Stripped12();
    virtual void Stripped13();
    virtual void Stripped14();
    virtual void Stripped15();
    virtual void RegisterTinyObjectsResource(ULONGLONG param_2,uint *param_3);
    virtual void FUN_180402d60();

    //stripped
    virtual void Stripped16();

    virtual void RegisterMeshResourceEx(ULONGLONG param_2, uint* param_3);
    virtual void RegisterAnimationResource(LONGLONG param_2, uint* param_3);
    virtual void RegisterAnimationScrResource(LONGLONG param_2, uint* param_3, __int64 param_4);
    virtual void UnregisterAnimationResource(LONGLONG param_2, uint* param_3);
    virtual void LAB_1804035c0();

    //stripped
    virtual void Stripped17();

    virtual void UnregisterTexturesResource(LONGLONG param_2, uint* param_3, __int64 param_4);
    virtual void RegisterFxResource(LONGLONG* param_2, uint* param_3);

    //stripped
    virtual void Stripped18();
    virtual void Stripped19();
    virtual void Stripped20();
    virtual void Stripped21();
};
