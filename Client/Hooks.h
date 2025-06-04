#pragma once

#include <Windows.h>
#include "Core/Sdk/Engine/resource.h"
#include "MinHook/MinHook.h"
#include "Core/Sdk/Engine/engine.h"
#include "Core/Sdk/Engine/CMaterialMgr.h"


enum class EIsGlobalPack : int {
    No = 0,
    Yes = 1
};

enum class EIsContentPack : int {
    No = 0,
    Yes = 1
};

enum class EUseCachePartition : int {
    No = 0,
    Yes = 1
};

enum class EIsCrossLevelPack : int {
    No = 0,
    Yes = 1
};

// Placeholder until defined
enum class EPackKind : int {
};

class Hooks {
public:
    static void MaterialMgrInit();
    static void Init();
    static void Enable();
    static void Disable();
};

class PackLoader {
public:
    static bool Load(CResourceLoadingRuntime* runtime, const char* path, CResourceDataPack** outPack,
        EIsGlobalPack isGlobal, EIsContentPack isContent, EUseCachePartition useCache,
        EIsCrossLevelPack isCrossLevel, EPackKind kind);
};

// Original function pointer
extern bool (*oLoad)(CResourceLoadingRuntime* runtime, const char* path, CResourceDataPack** outPack,
    EIsGlobalPack isGlobal, EIsContentPack isContent, EUseCachePartition useCache,
    EIsCrossLevelPack isCrossLevel, EPackKind kind);

// Error checking function
void ERRCHECK(MH_STATUS result);

//ptr to CMaterialMgr, couldn't find a exported getter function
extern CMaterialMgr *s_MaterialMgr;
