#include <pch.h>
#include "Resources/Resource.h"
#include "Core/Sdk/Steam/steam_api.h"
//Game
#include "Core/Sdk/Filesystem/Filesystem.h"
#include "Core/Sdk/Engine/engine.h"
#include "Core/Sdk/Engine/IGame.h"

//Utils
#include "Core/Util/Alert.h"
#include "Core/Util/Directory.h"
#include "Core/Util/Console.h"

//Loader
#include "Loader.h"
#include "Hooks.h"

typedef uint32 AppId_t;
const AppId_t k_uAppId = 239140;
std::string WorkingDirectory;
//make not magic at some point
constexpr const char* kGameDir = "DW"; //Dead World
constexpr const char* KLocale = "En";

bool SteamInit() {
	if (SteamAPI_RestartAppIfNecessary(k_uAppId))
		return EXIT_FAILURE;

	if (!SteamAPI_Init())
	{
		dbgprintf("SteamAPI_Init() failed\n");
		Utils::Alert("Fatal Error", "Steam must be running to play Dying Light (SteamAPI_Init() failed).");

		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

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

//Calls fs::init, if fallback is true it will write to the CWD
//if kSubPath is a full path, it will use that instead
bool FilesystemInit(bool fallback = false) {
	constexpr const char* kSubPath = "DyingLight";
	constexpr const char* kCacheSubPath = "out/cache";

	dbgprintf("FilesystemInit: Starting initialization (fallback = %s)\n", fallback ? "true" : "false");

	// If subPath is already a full path, use it directly
	if (fs::is_full_path(kSubPath)) {
		dbgprintf("FilesystemInit: '%s' is a full path, using it directly.\n", kSubPath);
		return fs::init(kSubPath, FFSAddSourceFlags::SUBDIRS, kCacheSubPath, false, true, nullptr);
	}

	// Try to get the Documents folder
	PWSTR documentsPath = nullptr;
	HRESULT hr = SHGetKnownFolderPath(FOLDERID_Documents, 0, nullptr, &documentsPath);

	if (SUCCEEDED(hr) && documentsPath != nullptr) {
		std::filesystem::path fullPath = std::filesystem::path(documentsPath) / kSubPath;
		CoTaskMemFree(documentsPath);

		std::string fullPathStr = fullPath.string(); // Store the string to ensure lifetime
		dbgprintf("FilesystemInit: Got Documents folder, resolved path: %s\n", fullPathStr.c_str());

		if (!fallback) {
			return fs::init(fullPathStr.c_str(), FFSAddSourceFlags::SUBDIRS, kCacheSubPath, false, true, nullptr);
		}
	}

	dbgprintf("FilesystemInit: Failed to get Documents folder (HRESULT: 0x%08X)\n", hr);

	//cleanup if still existing
	if (documentsPath) 
		CoTaskMemFree(documentsPath);

	// Fallback to using the working directory
	std::filesystem::path fallbackPath = std::filesystem::path(WorkingDirectory) / kGameDir / "out";
	dbgprintf("FilesystemInit: Falling back to working directory path: %s\n", fallbackPath.string().c_str());
	return fs::init(fallbackPath.string().c_str(), (FFSAddSourceFlags::ENUM)5, kCacheSubPath, false, true, nullptr);
}


void __cdecl LogCallback(enum Log::ELevel::TYPE level, const char* category, const char* message) {
	printf("%s", message);
}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	if (SteamInit())
		return EXIT_FAILURE;

	if (!Main())
		return EXIT_FAILURE;

#ifdef _DEBUG
	Utils::InitConsole();
	
	LogSetPrintCallback(LogCallback);
#endif

	//parse arguments
	WorkingDirectory = Utils::GetWorkingDirectory().string();


	auto hSplash = MAKEINTRESOURCE(IDB_SplashA); // Splash Screen
	auto hText = MAKEINTRESOURCE(IDS_Title);    // Dying Light String Resource
	auto hIcon = MAKEINTRESOURCE(IDI_ICON);    // Game Icon Resource

	int smallIconWidth = GetSystemMetrics(SM_CXSMICON);
	int smallIconHeight = GetSystemMetrics(SM_CYSMICON);
	auto smallIcon = LoadImage(hInstance, hIcon, IMAGE_ICON, smallIconWidth, smallIconHeight, 0);

	int largeIconWidth = GetSystemMetrics(SM_CXICON);
	int largeIconHeight = GetSystemMetrics(SM_CYICON);
	auto largeIcon = LoadImage(hInstance, hIcon, IMAGE_ICON, largeIconWidth, largeIconHeight, 0);

	ShowSplashscreen(hInstance, hSplash, hText, smallIcon);
	FilesystemInit();
	Loader::IndexMods();
	Loader::LoadNativeMods();
	Hooks::Init();
	Hooks::Enable();

	auto s_AssetManagerImpl = GetAssetManager();
	s_AssetManagerImpl->SetGame(kGameDir, WorkingDirectory.c_str(), 0, NULL, nullptr);

	// Define paths
	std::string Game_Path = WorkingDirectory + kGameDir;
	std::string Data_Path = WorkingDirectory + kGameDir + "\\Data";
	std::string Locale_Path = WorkingDirectory + kGameDir + "\\Data" + KLocale;
	std::string LocalePak_Path = WorkingDirectory + kGameDir + "\\Data" + KLocale + ".pak";
	std::string Speech_Path = WorkingDirectory + kGameDir + "\\Speech" + KLocale;
	std::string SpeechPak_Path = WorkingDirectory + kGameDir + "\\Speech" + KLocale + ".pak";

	// Add Game/DW folder
	fs::add_source(Game_Path.c_str(), (FFSAddSourceFlags::ENUM)258);

	// Add data0-3.pak sources
	for (int CurrentDataPak = 0; CurrentDataPak < 4; ++CurrentDataPak) {
		std::string dataPakPath = WorkingDirectory + kGameDir + "\\Data" + std::to_string(CurrentDataPak) + ".pak";
		fs::add_source(dataPakPath.c_str(), FFSAddSourceFlags::SUBDIRS);
	}

	// Add additional sources
	fs::add_source(Data_Path.c_str(), (FFSAddSourceFlags::ENUM)7);
	fs::add_source(Locale_Path.c_str(), (FFSAddSourceFlags::ENUM)265);
	fs::add_source(LocalePak_Path.c_str(), (FFSAddSourceFlags::ENUM)9);
	fs::add_source(Speech_Path.c_str(), (FFSAddSourceFlags::ENUM)265);
	fs::add_source(SpeechPak_Path.c_str(), (FFSAddSourceFlags::ENUM)9);

	Loader::LoadModPaks();

	if (!IGame::InitializeOnlineServices(nullptr)) {
		dbgprintf("IGame::InitializeOnlineServices Failed!\n");
		ExitProcess(1);
	}

	std::string GameDll_Path = WorkingDirectory + "gamedll";
	InitializeGameScript(GameDll_Path.c_str(), false);

	IGame* pIGame = CreateGame("GameDI", hInstance, true, kGameDir);
	dbgprintf("CreateGame GameDI at: %p\n", pIGame);

	pIGame->SetRootDirectory(WorkingDirectory.c_str());
	dbgprintf("IGame::SetRootDirectory at: %s\n", WorkingDirectory.c_str());

	auto mountHelper = Mount::CreateMountHelper(WorkingDirectory.c_str(), kGameDir, nullptr);
	CRTTIVariant variant(mountHelper);
	ttl::string_base<char> ClassName("MountHelper");
	pIGame->SetProperty(ClassName, variant);

	HideSplashscreen();

	//dbgprintf("IsGameInEditor: %s\n", pIGame->IsGameInEditor() ? "true" : "false");
	//dbgprintf("IsDedicatedServer: %s\n", pIGame->IsDedicatedServer() ? "true" : "false");
	//dbgprintf("IsGameRenderingEnabled: %s\n", pIGame->IsGameRenderingEnabled() ? "true" : "false");

	//callback for asi mods
	Loader::PreInitialize();

	if (pIGame->Initialize(lpCmdLine, nShowCmd, (HICON__*)smallIcon, (HICON__*)largeIcon, 0, 0, nullptr) != 0)
	{
		dbgprintf("IGame::Initialize() failed\n");
		Utils::Alert("Fatal Error", "Game failed to initalize (IGame::Initialize() failed)\n");
		return EXIT_FAILURE;
	}
	Hooks::MaterialMgrInit();
	auto s_ResourceLoadingRuntime = CResourceLoadingRuntime::Get();

	Loader::LoadMaterialPacks(s_MaterialMgr);
	Loader::LoadResourcePaks(s_ResourceLoadingRuntime);
	Loader::LoadTinyResourcePaks(pIGame);
	Loader::PostInitialize(pIGame);

	//set custom title
	ttl::string_base<char> TitleStr("Dying Light (CE6DL)");
	pIGame->SetGameName(TitleStr);

	//start rendering loop
	GameLoop(pIGame);

	if (pIGame)
		DestroyGame(NULL, NULL, NULL, NULL);

	IGame::ShutdownOnlineServices();
	Mount::DestroyMountHelper(mountHelper);
	UninitializeGameScript();
	//CrashClose();
	fs::shutdown();
	//SetDumpFunction(DumpFunc);

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