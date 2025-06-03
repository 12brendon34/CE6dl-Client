#include <pch.h>
#include "Hooks.h"
#include "Core/Util/Mem.h"

bool (*oLoad)(CResourceLoadingRuntime* runtime, const char* path, CResourceDataPack** outPack,
    EIsGlobalPack isGlobal, EIsContentPack isContent, EUseCachePartition useCache,
    EIsCrossLevelPack isCrossLevel, EPackKind kind) = nullptr;

void ERRCHECK(MH_STATUS result) {
#ifdef _DEBUG
    if (result != MH_OK) {
        printf("MinHook error! (%d) %s\n", result, MH_StatusToString(result));
        exit(-1);
    }
#endif
}

bool PackLoader::Load(CResourceLoadingRuntime* runtime, const char* path, CResourceDataPack** outPack,
    EIsGlobalPack isGlobal, EIsContentPack isContent, EUseCachePartition useCache,
    EIsCrossLevelPack isCrossLevel, EPackKind kind) {

    printf("[PackLoader::Load] Called with:\n");
    printf("  CResourceLoadingRuntime*: %p\n", runtime);
    printf("  Path: %s\n", path);
    printf("  isGlobal: %d\n", static_cast<int>(isGlobal));
    printf("  isContent: %d\n", static_cast<int>(isContent));
    printf("  useCache: %d\n", static_cast<int>(useCache));
    printf("  isCrossLevel: %d\n", static_cast<int>(isCrossLevel));
    printf("  kind: %d\n", static_cast<int>(kind));

    bool result = oLoad(runtime, path, outPack, isGlobal, isContent, useCache, isCrossLevel, kind);

    printf("  Result: %s\n", result ? "Success" : "Failure");
    //printf("  outPack: %p\n", (void*)*outPack);

    return result;
}


int GetCategoryLevel(int This, char* Catagory) {
    return INT_MAX;
}


int* (*oLogSettingsInstance)() = nullptr;
int* Log_Settings_Instance() {
    int* logint = oLogSettingsInstance();
    *logint = INT_MAX;

    return logint;
}
HMODULE EngineDll;
HMODULE FilesystemDll;

CMaterialMgr* s_MaterialMgr = nullptr;

void Hooks::MaterialMgrInit() {
    auto vtablePtr = *reinterpret_cast<void**>(reinterpret_cast<uintptr_t>(EngineDll) + 0xa402b0);
    s_MaterialMgr = reinterpret_cast<CMaterialMgr*>(vtablePtr);
}

void Hooks::Init() {
    EngineDll = GetModuleHandleA("engine_x64_rwdi.dll");
    FilesystemDll = GetModuleHandleA("filesystem_x64_rwdi.dll");

    auto* PackLoader_Load_Addr = reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(EngineDll) + 0x401870);
    void* GetCategoryLevel_Address = Utils::GetProcAddress(FilesystemDll, "?GetCategoryLevel@Settings@Log@@QEBA?AW4TYPE@ELevel@2@PEBD@Z");
    void* Log_Settings_Instance_Address = Utils::GetProcAddress(FilesystemDll, "?Instance@Settings@Log@@SAAEAV12@XZ");

    ERRCHECK(MH_Initialize());
    ERRCHECK(MH_CreateHook(PackLoader_Load_Addr, reinterpret_cast<void*>(&PackLoader::Load), reinterpret_cast<void**>(&oLoad)));
    ERRCHECK(MH_CreateHook(GetCategoryLevel_Address, reinterpret_cast<void*>(&GetCategoryLevel), nullptr));
    ERRCHECK(MH_CreateHook(Log_Settings_Instance_Address, reinterpret_cast<void*>(&Log_Settings_Instance), reinterpret_cast<void**>(&oLogSettingsInstance)));
}


void Hooks::Enable() {
    ERRCHECK(MH_EnableHook(MH_ALL_HOOKS));
}

void Hooks::Disable() {
    ERRCHECK(MH_DisableHook(MH_ALL_HOOKS));
}
