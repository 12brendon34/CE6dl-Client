#pragma once
#include "HookManager.h"

enum class EIsGlobalPack : int { No = 0, Yes = 1 };
enum class EIsContentPack : int { No = 0, Yes = 1 };
enum class EUseCachePartition : int { No = 0, Yes = 1 };
enum class EIsCrossLevelPack : int { No = 0, Yes = 1 };
enum class EPackKind : int {}; // Define it if needed

class CResourceLoadingRuntime;
class CResourceDataPack;

class PackLoader : public Hook {
public:
    using LoadFn = bool(*)(CResourceLoadingRuntime*, const char*, CResourceDataPack**,
        EIsGlobalPack, EIsContentPack, EUseCachePartition,
        EIsCrossLevelPack, EPackKind);

    static bool Load(CResourceLoadingRuntime* runtime, const char* path, CResourceDataPack** outPack,
        EIsGlobalPack isGlobal, EIsContentPack isContent, EUseCachePartition useCache,
        EIsCrossLevelPack isCrossLevel, EPackKind kind);

    void install() override;

private:
    inline static std::unique_ptr<PLH::Detour> detour;
    inline static LoadFn oLoad = nullptr;
    inline static bool onceler = true; //Because I'm Biggering
};