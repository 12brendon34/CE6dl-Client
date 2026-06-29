//
// Created by Brendon on 1/12/2026.
//
#include <filesystem>
#include <iostream>
#include <shlobj.h>
#include <windows.h>

#include "../Hook/HookManager.h"
#include "engine/Debug.h"
#include "engine/Game/IGame.h"
#include "engine/ModAPI.h"
#include "engine/ModLoader.h"
#include "engine/engine/ChromeEngine.h"
#include "engine/engine/CustomSplash.h"
#include "engine/engine/resourcemanagement/AssetManager.h"
#include "engine/engine/resourcemanagement/MountHelper.h"
#include "engine/filesystem/Filesystem.h"
#include "resource.h"

#ifdef STEAM_PLATFORM
#include "steam/steam_api.h"
typedef uint32_t AppId_t;
constexpr AppId_t kuAppId = 239140;
#endif

#define BUF_SIZE MAX_PATH
constexpr bool bUseMyDocuments = true;
constexpr auto kGameDir = "DW"; // Dead World
constexpr auto kSubPath = "DyingLight";
constexpr auto kCacheSubPath = "out/cache";

LONG WINAPI DLCECrashHandler(EXCEPTION_POINTERS *pExceptionPointers) {
    dbgprintf("\n--- DLCE CRASH DETECTED ---\n");
    if (pExceptionPointers && pExceptionPointers->ExceptionRecord) {
        dbgprintf("Exception Code: 0x%X\n", pExceptionPointers->ExceptionRecord->ExceptionCode);
        dbgprintf("Exception Address: 0x%p\n", pExceptionPointers->ExceptionRecord->ExceptionAddress);
    }

    // fuck getchar
    MessageBoxA(nullptr, "check dlce_debug.log for details", "DLCE crashed", MB_OK | MB_ICONERROR | MB_SYSTEMMODAL);

    return EXCEPTION_EXECUTE_HANDLER;
}

// I just felt like putting these below WinMain
bool CheckMultipleInstances(const char *command_line);
bool CheckFreeDiskSpaceAndDisplayWarning(const char *drivePath);

#ifdef STEAM_PLATFORM
bool SteamInit() {
    if (SteamAPI_RestartAppIfNecessary(kuAppId))
        return EXIT_FAILURE;

    if (!SteamAPI_Init()) {
        dbgprintf("SteamAPI_Init() failed\n");
        // Utils::Alert("Fatal Error", "Steam must be running to play Dying Light (SteamAPI_Init() failed).");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
#endif

void GameLoop(IGame *pIGame) {
    MSG msg;
    while (true) {
        while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE) == NULL) {
            pIGame->OnPaint();

            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        if (msg.message == WM_QUIT)
            break;

        if (msg.message == WM_KEYDOWN || msg.message == WM_SYSKEYDOWN) {
            if ((msg.lParam & 0x40000000) == 0) {
                ModAPI::CallOnKeyCallbacks(static_cast<int>(msg.wParam), true);
            }
        } else if (msg.message == WM_KEYUP || msg.message == WM_SYSKEYUP) {
            ModAPI::CallOnKeyCallbacks(static_cast<int>(msg.wParam), false);
        }

        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
    char szCurrDir[BUF_SIZE] = {};
    char szPath[BUF_SIZE] = {};

#ifdef STEAM_PLATFORM
    if (SteamInit())
        return EXIT_FAILURE;
#endif

    SetUnhandledExceptionFilter(DLCECrashHandler);

    // clears the debug log on startup
    FILE *fClear;
    if (fopen_s(&fClear, "dlce_debug.log", "w") == 0)
        fclose(fClear);

#ifdef STEAM_PLATFORM
    dbgprintf("Platform: Steam\n");
#else
    dbgprintf("Platform: GOG\n");
#endif

#ifdef _DEBUG
    FILE *fp;
    if (!AttachConsole(ATTACH_PARENT_PROCESS)) {
        AllocConsole();
    }
    freopen_s(&fp, "CONOUT$", "w", stdout);
    freopen_s(&fp, "CONOUT$", "w", stderr);
#endif



    if (!Main())
        return EXIT_FAILURE;

    if (!CheckMultipleInstances(lpCmdLine))
        return EXIT_FAILURE;

    if (strstr(lpCmdLine, "--wd")) {
        // read from current working directory (instead of the exe's dir)
        GetCurrentDirectory(BUF_SIZE, szCurrDir);
        strcat_s(szCurrDir, BUF_SIZE, "\\");
    } else {
        char szExeDir[BUF_SIZE] = {};
        char drive[_MAX_DRIVE] = {};
        char dir[_MAX_DIR] = {};

        GetModuleFileName(nullptr, szExeDir, BUF_SIZE);
        _splitpath_s(szExeDir, drive, _MAX_DRIVE, dir, _MAX_DIR, nullptr, 0, nullptr, 0);
        strcpy_s(szExeDir, BUF_SIZE, drive);
        strcat_s(szExeDir, BUF_SIZE, dir);
        strcpy_s(szCurrDir, BUF_SIZE, szExeDir);
    }

    // Choose documents or current directory to write out to
    FFSAddSourceFlags::ENUM write_path_flags = FFSAddSourceFlags::SUBDIRS;
    if (bUseMyDocuments && SHGetFolderPath(nullptr, CSIDL_PERSONAL, nullptr, 0, szPath) >= 0) {
        strcat_s(szPath, BUF_SIZE, "\\");
        strcat_s(szPath, BUF_SIZE, kSubPath);
    } else {
        strcpy_s(szPath, BUF_SIZE, szCurrDir);
        strcat_s(szPath, BUF_SIZE, kGameDir);
        strcat_s(szPath, BUF_SIZE, "\\out");
        write_path_flags |= FFSAddSourceFlags::STRIP_LAST_DIR;
    }

    if (!CheckFreeDiskSpaceAndDisplayWarning(szPath))
        return EXIT_FAILURE;

    // Hooks/Plugins
    HookManager::initHooks();
    const auto ModLoader = new Loader();
    ModLoader->IndexMods();

    // Splashscreen
    const auto hSplash = MAKEINTRESOURCE(IDB_SPLASH);
    // auto hText = MAKEINTRESOURCE(IDS_TITLE);
    const auto hIcon = MAKEINTRESOURCE(IDI_ICON);

    const auto smallIcon = static_cast<HICON>(LoadImage(hInstance, hIcon, IMAGE_ICON, GetSystemMetrics(SM_CXSMICON), GetSystemMetrics(SM_CYSMICON), 0));
    const auto largeIcon = static_cast<HICON>(LoadImage(hInstance, hIcon, IMAGE_ICON, GetSystemMetrics(SM_CXICON), GetSystemMetrics(SM_CYICON), 0));

    ShowCustomSplashscreen(hInstance, hSplash, IDS_TITLE, smallIcon);

    const auto bInitSuccess = fs::init(szPath, write_path_flags, kCacheSubPath, false, true, nullptr);
    if (!bInitSuccess)
        return EXIT_FAILURE;

    // load mod dll's
    ModLoader->LoadPhase(ModLoadPhase::DllPhase);

    const auto s_AssetManagerImpl = GetAssetManager();
    s_AssetManagerImpl->SetGame(kGameDir, szCurrDir, 0, NULL, nullptr);

    // Get DW path
    char sBaseDir[BUF_SIZE] = {};
    strcpy_s(sBaseDir, BUF_SIZE, szCurrDir);
    strcat_s(sBaseDir, BUF_SIZE, kGameDir);
    fs::add_source(sBaseDir, FFSAddSourceFlags::APPEND);

    // add each datapak
    for (int i = 0; i < 4; ++i) {
        char sPakPath[BUF_SIZE] = {};
        sprintf_s(sPakPath, "%s\\Data%d.pak", sBaseDir, i);
        fs::add_source(sPakPath, FFSAddSourceFlags::SUBDIRS);
    }

    // Add Game Data dir (DW\Data)
    char sDataDir[BUF_SIZE] = {};
    strcpy_s(sDataDir, BUF_SIZE, sBaseDir);
    strcat_s(sDataDir, BUF_SIZE, "\\Data");
    fs::add_source(sDataDir, FFSAddSourceFlags::SUBDIRS | FFSAddSourceFlags::APPEND | FFSAddSourceFlags::PRELOAD);

    if (!IGame::InitializeOnlineServices(nullptr)) {
        dbgprintf("IGame::InitializeOnlineServices Failed!\n");
        ExitProcess(1);
    }

    // Get locale or fallback locale
    auto LocaleID = IGame::GetDefaultLocaleID();
    char sLocalePath[BUF_SIZE] = {};
    strcpy_s(sLocalePath, BUF_SIZE, sDataDir);
    strcat_s(sLocalePath, BUF_SIZE, LocaleID.c_str());

    if (!fs::does_dir_exist(sLocalePath)) {
        LocaleID = IGame::GetFallbackLocaleID();
        strcpy_s(sLocalePath, BUF_SIZE, sDataDir);
        strcat_s(sLocalePath, BUF_SIZE, LocaleID.c_str());
    }

    // add DW/DataEn source
    fs::add_source(sLocalePath, FFSAddSourceFlags::SUBDIRS | FFSAddSourceFlags::BROWSABLE);

    // add DW/DataEn.pak
    strcat_s(sLocalePath, BUF_SIZE, ".pak");
    fs::add_source(sLocalePath, FFSAddSourceFlags::SUBDIRS | FFSAddSourceFlags::BROWSABLE);

    // same thing, but with speech paks
    auto SpeechID = IGame::GetDefaultSpeechID(LocaleID);
    char sSpeechPath[BUF_SIZE] = {};
    strcpy_s(sSpeechPath, BUF_SIZE, sBaseDir);
    strcat_s(sSpeechPath, BUF_SIZE, "\\Speech");
    strcat_s(sSpeechPath, BUF_SIZE, SpeechID.c_str());

    if (!fs::does_dir_exist(sSpeechPath)) {
        SpeechID = IGame::GetFallbackSpeechID();
        strcpy_s(sSpeechPath, BUF_SIZE, sBaseDir);
        strcat_s(sSpeechPath, BUF_SIZE, "\\Speech");
        strcat_s(sSpeechPath, BUF_SIZE, SpeechID.c_str());
    }

    // add DW/SpeechEn source
    fs::add_source(sSpeechPath, FFSAddSourceFlags::SUBDIRS | FFSAddSourceFlags::BROWSABLE);

    // add DW/SpeechEn.pak
    strcat_s(sSpeechPath, BUF_SIZE, ".pak");
    fs::add_source(sSpeechPath, FFSAddSourceFlags::SUBDIRS | FFSAddSourceFlags::BROWSABLE);

    char szGameScriptDLL[BUF_SIZE] = {};
    strcpy_s(szGameScriptDLL, BUF_SIZE, szCurrDir);
    strcat_s(szGameScriptDLL, BUF_SIZE, "gamedll");

    // load mod pak's
    ModLoader->LoadPhase(ModLoadPhase::PakPhase);
    InitializeGameScript(szGameScriptDLL, false);

    IGame *pIGame = CreateGame("GameDI", hInstance, true, kGameDir);
    
    pIGame->SetLocaleID(LocaleID.c_str());
    pIGame->SetSpeechID(SpeechID.c_str(), false);
    pIGame->SetRootDirectory(szCurrDir);

    const auto mountHelper = Mount::CreateMountHelper(szCurrDir, kGameDir, nullptr);
    const CRTTIVariant variant(mountHelper);
    pIGame->SetProperty(ttl::string_base(const_cast<char *>("MountHelper")), variant);

    HideCustomSplashscreen();
    if (pIGame->Initialize(lpCmdLine, nShowCmd, smallIcon, largeIcon, 0, 0, nullptr) != 0) {
        dbgprintf("IGame::Initialize() failed\n");
        // Utils::Alert("Fatal Error", "Game failed to initialize.");
        return EXIT_FAILURE;
    }

    // Get Window Title, append DLCE
    char sWindowTitle[BUF_SIZE] = {};
    GetWindowText(pIGame->GethWnd(), sWindowTitle, BUF_SIZE);
    strcat_s(sWindowTitle, BUF_SIZE, " [DLCE]");

    pIGame->SetGameName(ttl::string_base(sWindowTitle));
    GameLoop(pIGame);

    // Shutdown

    ModLoader->UnLoadPhase(ModLoadPhase::DllPhase);
    ModLoader->UnLoadPhase(ModLoadPhase::PakPhase);
    DestroyGame(NULL, NULL, NULL, NULL);
    IGame::ShutdownOnlineServices();
    Mount::DestroyMountHelper(mountHelper);
    UninitializeGameScript();
    fs::shutdown();

    return EXIT_SUCCESS;
}

bool CheckMultipleInstances(const char *command_line) {
    // -ami : allow multi instance
    if (strstr(command_line, "-ami"))
        return true;

    static HANDLE h = CreateMutex(nullptr, TRUE, "Global\\ChromeEngine");
    const DWORD err = GetLastError();

    if (h && err != ERROR_ALREADY_EXISTS)
        return true;

    if (!h && err != ERROR_ACCESS_DENIED)
        return true;

    MessageBox(nullptr, "Dying Light is already running", "Dying Light Error", MB_ICONERROR);
    return false;
}

bool CheckFreeDiskSpaceAndDisplayWarning(const char *drivePath) {
    CreateDirectory(drivePath, nullptr);

    ULARGE_INTEGER freeBytesAvailable = {};
    if (!GetDiskFreeSpaceEx(drivePath, &freeBytesAvailable, nullptr, nullptr)) {
        // unable to check disk space, assume that there is enough space instead of closing for possibly no reason
        return true;
    }

    const auto freeMB = freeBytesAvailable.QuadPart / (1024 * 1024);
    constexpr auto requiredMB = 200;

    if (freeMB >= requiredMB) {
        return true;
    }

    char msg[512];
    _snprintf_s(msg, sizeof(msg), _TRUNCATE, "You have insufficient disk space on drive %s\nPlease free up %d MB of disk space and run this game again.", drivePath, requiredMB);
    const int msgResult = MessageBox(nullptr, msg, "Free disk space warning", MB_ICONEXCLAMATION | MB_OKCANCEL);

    if (msgResult == IDOK)
        return true;

    if (msgResult == IDCANCEL)
        return false;

    return true;
}

// callback hook for debug text emitted from the Steam API
extern "C" void __cdecl SteamAPIDebugTextHook(int, const char *pchDebugText) {
    // if you add -debug_steamapi to the command-line, a lot of extra informational messages will also be sent
    ::OutputDebugString(pchDebugText);
}

extern "C" {
// Enable NVIDIA Optimus discrete GPU: https://developer.download.nvidia.com/devzone/devcenter/gamegraphics/files/OptimusRenderingPolicies.pdf
__declspec(dllexport) extern const DWORD NvOptimusEnablement = 0x00000001;

// Enable AMD PowerXpress high-performance GPU: https://developer.amd.com/community/blog/2015/10/02/amd-enduro-system-for-developers/
__declspec(dllexport) extern const int AmdPowerXpressRequestHighPerformance = 1;
}
