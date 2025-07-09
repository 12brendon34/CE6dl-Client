// Precompiled Header
#include <pch.h>

// Platform & SDK
#ifdef STEAM_PLATFORM
#include "Core/Sdk/Steam/steam_api.h"
typedef uint32 AppId_t;
const AppId_t k_uAppId = 239140;
#endif

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
#include "Hooks/HookManager.h"
#include "Hooks/PackLoader.h"
#include "Hooks/CTechniquesIni.h"

#include <filesystem>

constexpr const char* kGameDir = "DW"; // Dead World
constexpr const char* kSubPath = "DyingLight";
constexpr const char* kCacheSubPath = "out/cache";

std::string working_directory;

#ifdef STEAM_PLATFORM
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
#endif

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

#ifdef _DEBUG
// Console log callback
void __cdecl LogCallback(enum Log::ELevel::TYPE, const char*, const char* message) {
	dbgprintf("%s", message);
}
#endif

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
#ifdef STEAM_PLATFORM
	if (SteamInit())
		return EXIT_FAILURE;
#endif

	if (!Main())
		return EXIT_FAILURE;

	working_directory = Utils::GetWorkingDirectory().string();

	std::string KLocale;

	ttl::string_base<char> defaultLocale = IGame::GetDefaultLocaleID();
	std::string KLocale_default = defaultLocale.c_str();

	ttl::string_base<char> fallbackLocale = IGame::GetFallbackLocaleID();
	std::string KLocale_fallback = fallbackLocale.c_str();

#ifdef STEAM_PLATFORM
	const std::string steam_language = SteamApps()->GetCurrentGameLanguage();
	KLocale = Utils::ConvertSteamLangToWebLang(steam_language);
#else
	KLocale = KLocale_default;
#endif

#ifdef _DEBUG
	Utils::InitConsole();
	LogSetPrintCallback(LogCallback);

	dbgprintf("KLocale: %s\nKLocale_default: %s\nKLocale_fallback: %s\n", KLocale.c_str(), KLocale_default.c_str(), KLocale_fallback.c_str());
	dbgprintf("Working Directory: %s\n", working_directory.c_str());
	dbgprintf("Platform Steam: %d\n", STEAM_PLATFORM);

	while (!::IsDebuggerPresent())
		::Sleep(100);
#endif

	// Splashscreen
	auto hSplash = MAKEINTRESOURCE(IDB_SplashA);
	auto hText = MAKEINTRESOURCE(IDS_Title);
	auto hIcon = MAKEINTRESOURCE(IDI_ICON);

	auto smallIcon = (HICON)LoadImage(hInstance, hIcon, IMAGE_ICON, GetSystemMetrics(SM_CXSMICON), GetSystemMetrics(SM_CYSMICON), 0);
	auto largeIcon = (HICON)LoadImage(hInstance, hIcon, IMAGE_ICON, GetSystemMetrics(SM_CXICON), GetSystemMetrics(SM_CYICON), 0);

	ShowSplashscreen(hInstance, hSplash, hText, smallIcon);

	// Initialization
	FilesystemInit();
	Loader::IndexMods();
	Loader::LoadNativeMods();

	auto& hookManager = HookManager::get();
	hookManager.add(std::make_unique<PackLoader>());
	hookManager.add(std::make_unique<CTechniquesIni>());

	auto s_AssetManagerImpl = GetAssetManager();
	s_AssetManagerImpl->SetGame(kGameDir, working_directory.c_str(), 0, NULL, nullptr);

	std::string basePath = working_directory + kGameDir;
	std::string dataPath = basePath + "\\Data";

	auto resourcesExist = [&](const std::string& locale) {
		std::string localePath = dataPath + locale;
		std::string localePak = localePath + ".pak";
		std::string speechPath = basePath + "\\Speech" + locale;
		std::string speechPak = speechPath + ".pak";

		//return std::filesystem::exists(localePath) || // this folder usually doesn't exist.
		return std::filesystem::exists(localePak) ||
			std::filesystem::exists(speechPath) ||
			std::filesystem::exists(speechPak);
	};

	std::string chosenLocale;
	if (resourcesExist(KLocale)) {
		chosenLocale = KLocale;
	}
	else if (resourcesExist(KLocale_default)) {
		chosenLocale = KLocale_default;
	}
	else {
		chosenLocale = KLocale_fallback;
	}

	// Mount game data
	fs::add_source(basePath.c_str(), (FFSAddSourceFlags::ENUM)258);

	for (int i = 0; i < 4; ++i) {
		std::string dataPakPath = std::format("{}\\Data{}.pak", basePath, i);
		fs::add_source(dataPakPath.c_str(), FFSAddSourceFlags::SUBDIRS);
	}

	fs::add_source(dataPath.c_str(), (FFSAddSourceFlags::ENUM)7);

	std::string localePath = dataPath + chosenLocale;
	std::string localePak = localePath + ".pak";
	std::string speechPath = basePath + "\\Speech" + chosenLocale;
	std::string speechPak = speechPath + ".pak";

	fs::add_source(localePath.c_str(), (FFSAddSourceFlags::ENUM)265);
	fs::add_source(localePak.c_str(), (FFSAddSourceFlags::ENUM)9);
	fs::add_source(speechPath.c_str(), (FFSAddSourceFlags::ENUM)265);
	fs::add_source(speechPak.c_str(), (FFSAddSourceFlags::ENUM)9);

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

	pIGame->SetLocaleID(chosenLocale.c_str());
	pIGame->SetSpeechID(chosenLocale.c_str(), false);
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
    auto g_pMatMgr = std::bit_cast<CMaterialMgr*>(r_MatMgr);

	//load matpaks, rpacks, call post init for asi mods
	Loader::LoadMaterialPacks(g_pMatMgr);
	Loader::LoadResourcePaks(s_ResourceLoadingRuntime);
	Loader::LoadTinyResourcePaks(pIGame);
	Loader::PostInitialize(pIGame);

	//set custom title because I can
	pIGame->SetGameName(ttl::string_base<char>("Dying Light (DLCE)"));

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