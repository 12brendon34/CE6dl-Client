#include <pch.h>
#include "PackLoader.h"
#include "../Loader.h"
#include "../Core/Util/Mem.h"

bool PackLoader::Load(CResourceLoadingRuntime* runtime, const char* path, CResourceDataPack** outPack,
    EIsGlobalPack isGlobal, EIsContentPack isContent, EUseCachePartition useCache,
    EIsCrossLevelPack isCrossLevel, EPackKind kind) {

    if (onceler) {
        onceler = false;
        Loader::LoadResourcePaks(runtime, true);
    }

    dbgprintf("[PackLoader::Load] Called with:\n");
    dbgprintf("  CResourceLoadingRuntime*: %p\n", runtime);
    dbgprintf("  Path: %s\n", path);
    dbgprintf("  isGlobal: %d\n", static_cast<int>(isGlobal));
    dbgprintf("  isContent: %d\n", static_cast<int>(isContent));
    dbgprintf("  useCache: %d\n", static_cast<int>(useCache));
    dbgprintf("  isCrossLevel: %d\n", static_cast<int>(isCrossLevel));
    dbgprintf("  kind: %d\n", static_cast<int>(kind));

    bool result = oLoad(runtime, path, outPack, isGlobal, isContent, useCache, isCrossLevel, kind);

    dbgprintf("  Result: %s\n", result ? "Success" : "Failure");
    return result;
}

void PackLoader::install() {
    HMODULE engine = GetModuleHandleA("engine_x64_rwdi.dll");
    if (!engine) {
        MessageBoxA(nullptr, "Failed to find engine_x64_rwdi.dll", "Error", MB_ICONERROR);
        return;
    }

    auto target = Utils::findSig(engine, "48 89 5C 24 ? 48 89 74 24 ? 48 89 7C 24 ? 55 41 54 41 56");
    //PLH::x64Detour detour(target, reinterpret_cast<uint64_t>(&PackLoader::Load), reinterpret_cast<uint64_t*>(&oLoad));
    detour = std::make_unique<PLH::x64Detour>(target, reinterpret_cast<uint64_t>(&PackLoader::Load), reinterpret_cast<uint64_t*>(&oLoad));


    if (!detour->hook()) {
        MessageBoxA(nullptr, "Failed to hook PackLoader::Load", "Error", MB_ICONERROR);
    }
}
