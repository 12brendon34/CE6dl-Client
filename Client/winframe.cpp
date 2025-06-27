// Precompiled Header
#include <pch.h>

// SDK / External
#include "Core/Sdk/Steam/steam_api.h"
#include "Core/Sdk/Filesystem/Filesystem.h"
#include "Core/Sdk/Engine/engine.h"
#include "Core/Sdk/Engine/ILevel.h"
#include "Core/Sdk/Engine/IGame.h"

// Game Resources
#include "Resources/Resource.h"

// Utils
#include "Core/Util/Alert.h"
#include "Core/Util/Directory.h"
#include "Core/Util/UString.h"
#include "Core/Util/Console.h"

// Loader and Hooks
#include "Loader.h"
//#include "Hooks.h"

#include <filesystem>
#include "Hooks/HookManager.h"
#include "Hooks/PackLoader.h"
#include "Hooks/CTechniquesIni.h"

typedef uint32 AppId_t;
const AppId_t k_uAppId = 239140;

constexpr const char* kGameDir = "DW"; // Dead World
//constexpr const char* KLocale = "En";
constexpr const char* kSubPath = "DyingLight";
constexpr const char* kCacheSubPath = "out/cache";
std::string working_directory;

// Initialize Steam API, restart if not run through steam, error if failure
bool SteamInit() {
	if (SteamAPI_RestartAppIfNecessary(k_uAppId))
		return EXIT_FAILURE;

	if (!SteamAPI_Init()) {
		dbgprintf("SteamAPI_Init() failed\n");
		Utils::Alert("Fatal Error", "Steam must be running to play Dying Light (SteamAPI_Init() failed).");
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

// Main game rendering and message loop
void GameLoop(IGame* pIGame) {
	MSG msg;
	while (true) {
		while (PeekMessageA(&msg, nullptr, 0, 0, PM_REMOVE) == NULL) {
			pIGame->OnPaint();
		}
		if (msg.message == WM_QUIT)
			break;
		TranslateMessage(&msg);
		DispatchMessageA(&msg);
	}
}

// Set up file system paths for game data and then init fs
bool FilesystemInit(bool fallback = false) {
	dbgprintf("FilesystemInit: Starting initialization (fallback = %s)\n", fallback ? "true" : "false");

	if (fs::is_full_path(kSubPath)) {
		dbgprintf("FilesystemInit: '%s' is a full path, using it directly.\n", kSubPath);
		return fs::init(kSubPath, FFSAddSourceFlags::SUBDIRS, kCacheSubPath, false, true, nullptr);
	}

	PWSTR documentsPath = nullptr;
	HRESULT hr = SHGetKnownFolderPath(FOLDERID_Documents, 0, nullptr, &documentsPath);

	if (SUCCEEDED(hr) && documentsPath) {
		std::filesystem::path fullPath = std::filesystem::path(documentsPath) / kSubPath;
		CoTaskMemFree(documentsPath);

		std::string fullPathStr = fullPath.string();
		dbgprintf("FilesystemInit: Got Documents folder, resolved path: %s\n", fullPathStr.c_str());

		if (!fallback)
			return fs::init(fullPathStr.c_str(), FFSAddSourceFlags::SUBDIRS, kCacheSubPath, false, true, nullptr);
	}
	else {
		dbgprintf("FilesystemInit: Failed to get Documents folder (HRESULT: 0x%08X)\n", hr);
		if (documentsPath) CoTaskMemFree(documentsPath);
	}

	std::filesystem::path fallbackPath = std::filesystem::path(working_directory) / kGameDir / "out";
	dbgprintf("FilesystemInit: Falling back to: %s\n", fallbackPath.string().c_str());
	return fs::init(fallbackPath.string().c_str(), (FFSAddSourceFlags::ENUM)5, kCacheSubPath, false, true, nullptr);
}

// Console log callback
void __cdecl LogCallback(enum Log::ELevel::TYPE level, const char* category, const char* message) {
	printf("%s", message);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
	// Initialize Steam and game base systems
	if (SteamInit() || !Main())
		return EXIT_FAILURE;

#ifdef _DEBUG
	Utils::InitConsole();
	LogSetPrintCallback(LogCallback);

	while (!::IsDebuggerPresent())
		::Sleep(100);
#endif

	working_directory = Utils::GetWorkingDirectory().string();

	// Get user's Steam language and convert it
	const std::string steam_language = SteamApps()->GetCurrentGameLanguage();
	const std::string KLocale = Utils::ConvertSteamLangToWebLang(steam_language);

	// Load splash screen, icon, etc.
	auto hSplash = MAKEINTRESOURCE(IDB_SplashA);
	auto hText = MAKEINTRESOURCE(IDS_Title);
	auto hIcon = MAKEINTRESOURCE(IDI_ICON);

	// Load icon images
	auto smallIcon = (HICON)LoadImage(hInstance, hIcon, IMAGE_ICON, GetSystemMetrics(SM_CXSMICON), GetSystemMetrics(SM_CYSMICON), 0);
	auto largeIcon = (HICON)LoadImage(hInstance, hIcon, IMAGE_ICON, GetSystemMetrics(SM_CXICON), GetSystemMetrics(SM_CYICON), 0);

	// Show splash screen
	ShowSplashscreen(hInstance, hSplash, hText, smallIcon);

	//Init filesystem, index mods, enable hooks
	FilesystemInit();
	Loader::IndexMods();
	Loader::LoadNativeMods();


	HookManager::get().add(std::make_unique<PackLoader>());
	HookManager::get().add(std::make_unique<CTechniquesIni>());
	//auto Hooks = new HookManager();
	//Hooks->setup();
	//Hooks->enable();
	//Hooks::Init();
	//Hooks::Enable();

	//get assetmanager and call setgame (required for rpack stuff/dlc)
	auto s_AssetManagerImpl = GetAssetManager();
	s_AssetManagerImpl->SetGame(kGameDir, working_directory.c_str(), 0, NULL, nullptr);

	// Define file paths
	std::string basePath = working_directory + kGameDir;
	std::string dataPath = basePath + "\\Data";
	std::string localePath = dataPath + KLocale;
	std::string localePak = localePath + ".pak";
	std::string speechPath = basePath + "\\Speech" + KLocale;
	std::string speechPak = speechPath + ".pak";

	// Add Game/DW folder
	fs::add_source(basePath.c_str(), (FFSAddSourceFlags::ENUM)258);

	// Add data0.pak to data3.pak
	for (int i = 0; i < 4; ++i) {
		std::string dataPakPath = std::format("{}\\Data{}.pak", basePath, i);
		fs::add_source(dataPakPath.c_str(), FFSAddSourceFlags::SUBDIRS);
	}

	// Add other important game resources
	fs::add_source(dataPath.c_str(), (FFSAddSourceFlags::ENUM)7);
	fs::add_source(localePath.c_str(), (FFSAddSourceFlags::ENUM)265);
	fs::add_source(localePak.c_str(), (FFSAddSourceFlags::ENUM)9);
	fs::add_source(speechPath.c_str(), (FFSAddSourceFlags::ENUM)265);
	fs::add_source(speechPak.c_str(), (FFSAddSourceFlags::ENUM)9);

	//load custom paks
	Loader::LoadModPaks();

	if (!IGame::InitializeOnlineServices(nullptr)) {
		dbgprintf("IGame::InitializeOnlineServices Failed!\n");
		ExitProcess(1);
	}

	// init game script
	std::string gameDllPath = working_directory + "gamedll";
	InitializeGameScript(gameDllPath.c_str(), false);

	//create game and set wd
	IGame* pIGame = CreateGame("GameDI", hInstance, true, kGameDir);
	pIGame->SetRootDirectory(working_directory.c_str());

	//create game mounthelper (loads dlcs)
	auto mountHelper = Mount::CreateMountHelper(working_directory.c_str(), kGameDir, nullptr);
	CRTTIVariant variant(mountHelper);
	pIGame->SetProperty(ttl::string_base<char>("MountHelper"), variant);

	//hide splash and call preinit in asi mods
	HideSplashscreen();
	Loader::PreInitialize();

	//Init Game
	if (pIGame->Initialize(lpCmdLine, nShowCmd, smallIcon, largeIcon, 0, 0, nullptr) != 0) {
		dbgprintf("IGame::Initialize() failed\n");
		Utils::Alert("Fatal Error", "Game failed to initialize.");
		return EXIT_FAILURE;
	}

	//get material manager
	//Hooks::MaterialMgrInit();
	auto s_ResourceLoadingRuntime = CResourceLoadingRuntime::Get();

	//need to do this better somehow
	auto EngineDll = GetModuleHandleA("engine_x64_rwdi.dll");

	//CreateMaterialManager is inlined into CMaterialMgr::Initialize
	//should be roughly
	/*
	CMaterialMgr *this;
  
	this = (CMaterialMgr *)malloc(0xb8);
	CMaterialMgr::CMaterialMgr(this);
	r_MatMgr = this;
	CMaterialMgr::Initialize(this,param_1);
	g_pMatMgr = r_MatMgr;
	return;
	*/


	//instead of using DAT_180a402b0 directly, I can hook CTechniquesIni::Create, capture the first (argument-1) and that should give me r_MatMgr
	/*
	  DAT_180a402b0 = plVar7;
	  FUN_18076fd20(uVar5,param_2,param_3,param_4);
	  CTechniquesIni::Create((void **)(plVar7 + 1),param_2,param_3,param_4);
	*/

    //auto r_MatMgr = *reinterpret_cast<void**>(reinterpret_cast<uintptr_t>(EngineDll) + 0xa402b0);
    auto g_pMatMgr = reinterpret_cast<CMaterialMgr*>(r_MatMgr);


	//load matpaks, rpacks, call post init for asi mods
	Loader::LoadMaterialPacks(g_pMatMgr);
	Loader::LoadResourcePaks(s_ResourceLoadingRuntime);
	Loader::LoadTinyResourcePaks(pIGame);
	Loader::PostInitialize(pIGame);

	//set custom title because I can
	pIGame->SetGameName(ttl::string_base<char>("Dying Light (CE6DL)"));

	//gameloop
	GameLoop(pIGame);

	//shutdown game
	if (pIGame)
		DestroyGame(NULL, NULL, NULL, NULL);
	
	//Hooks->shutdown();
	IGame::ShutdownOnlineServices();
	Mount::DestroyMountHelper(mountHelper);
	UninitializeGameScript();
	fs::shutdown();

	return EXIT_SUCCESS;
}

// callback hook for debug text emitted from the Steam API
extern "C" void __cdecl SteamAPIDebugTextHook(int, const char* pchDebugText)
{
	// if you add -debug_steamapi to the command-line, a lot of extra informational messages will also be sent
	::OutputDebugString(pchDebugText);
}

extern "C" {
	// Enable NVIDIA Optimus discrete GPU: https://developer.download.nvidia.com/devzone/devcenter/gamegraphics/files/OptimusRenderingPolicies.pdf
	__declspec(dllexport) extern const DWORD NvOptimusEnablement = 0x00000001;

	// Enable AMD PowerXpress high-performance GPU: https://developer.amd.com/community/blog/2015/10/02/amd-enduro-system-for-developers/
	__declspec(dllexport) extern const int AmdPowerXpressRequestHighPerformance = 1;
}