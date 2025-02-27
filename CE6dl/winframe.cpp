#include <pch.h>
#include <random>
#include "Utils/Utils.h"
#include "Core/Engine/engine_x64_rwdi.h"
//#include "engine/Link.h"
//#include "mod/Loader.h"
#include "Core/Filesystem/filesystem_x64_rwdi.h"
#include "Core/Loader.h"

typedef uint32 AppId_t;
const AppId_t k_uAppId = 239140;

int Alert(const char* lpCaption, const char* lpText)
{
	return ::MessageBox(nullptr, lpText, lpCaption, MB_OK);
}

void MiniDumpFunction(unsigned int nExceptionCode, EXCEPTION_POINTERS* pException)
{
	bool MiniDumpType = false;
	WriteFullDump(nExceptionCode, pException, nullptr, MiniDumpType, nullptr);
}

void GameLoop(IGame* pGame) {
	MSG msg;

	while (true) {
		while (PeekMessageA(&msg, nullptr, 0, 0, PM_REMOVE) == NULL) {
			pGame->OnPaint();
		}

		if (msg.message == WM_QUIT)
			break;

		TranslateMessage(&msg);
		DispatchMessageA(&msg);
	}
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	if (SteamAPI_RestartAppIfNecessary(k_uAppId))
	{
		// if Steam is not running or the game wasn't started through Steam, SteamAPI_RestartAppIfNecessary starts the 
		// local Steam client and also launches this game again.
		return EXIT_FAILURE;
	}

	//IGame::InitializeOnlineServices will also call this
	if (!SteamAPI_Init())
	{
		OutputDebugString("SteamAPI_Init() failed\n");
		Alert("Fatal Error", "Steam must be running to play Dying Light (SteamAPI_Init() failed).\n");
		return EXIT_FAILURE;
	}
	
	/*
	//not really good but I use it a lot
	while (!::IsDebuggerPresent())
		::Sleep(100);
	*/

#ifdef _DEBUG
	Utils::InitConsole();
#endif

	std::string WorkingDirectory;
	std::string gamedir = "DW"; //Dead World lol
	std::string locale = "En"; // ISteamApps::GetCurrentGameLanguage maybe some time
	bool DumpRTTI = false;
	bool WriteFullDump = false;

	//cmdline param's here
	if (WorkingDirectory.empty()) {
		WorkingDirectory = Utils::GetWorkingDirectory();
	}

	if (!Main()) {
		return EXIT_FAILURE;
	}

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dist(101, 106);

	int randomSplash = dist(gen);
	auto hSplash = MAKEINTRESOURCE(randomSplash);  // Game Splash Resource

	auto hText = MAKEINTRESOURCE(100);    // Dying Light String Resource
	auto hIcon = MAKEINTRESOURCE(110);    // Game Icon Resource

	int smallIconWidth = GetSystemMetrics(SM_CXSMICON);
	int smallIconHeight = GetSystemMetrics(SM_CYSMICON);
	auto smallIcon = LoadImage(hInstance, hIcon, IMAGE_ICON, smallIconWidth, smallIconHeight, 0);

	int largeIconWidth = GetSystemMetrics(SM_CXICON);
	int largeIconHeight = GetSystemMetrics(SM_CYICON);
	auto largeIcon = LoadImage(hInstance, hIcon, IMAGE_ICON, largeIconWidth, largeIconHeight, 0);
	ShowSplashscreen(hInstance, hSplash, hText, smallIcon);
	Sleep(2000);

	//Filesystem Setup
	FFSAddSourceFlags::ENUM fsAddSourceFlags;
	std::string fsDestinationPath;
	std::string fsSaveDir = "DyingLight"; // Default is Documents folder/DyingLight

	bool useWorkingDir = false;
	bool isFullPath = fs::is_full_path(fsSaveDir.c_str()) != NULL;

	// Won't be a full path unless hardcoded
	if (isFullPath) {
		fsDestinationPath = fsSaveDir;
		fsAddSourceFlags = FFSAddSourceFlags::SUBDIRS;
	}
	// If not hardcoded to use workingdir it will use the documents folder instead
	// this is expected in most cases
	if (!useWorkingDir) {
		PWSTR path = nullptr;

		// Retrieve the path to the Documents folder
		HRESULT hr = SHGetKnownFolderPath(FOLDERID_Documents, 0, nullptr, &path);
		if (SUCCEEDED(hr)) {
			// Convert the wide string to a standard string
			char pathBuffer[MAX_PATH];
			WideCharToMultiByte(CP_UTF8, 0, path, -1, pathBuffer, MAX_PATH, NULL, NULL);

			fsDestinationPath = std::string(pathBuffer) + "\\" + fsSaveDir;
			fsAddSourceFlags = FFSAddSourceFlags::SUBDIRS;
		}
		else {
			// Fallback to using the working directory
			useWorkingDir = true;
		}

		if (path) {
			CoTaskMemFree(path); // Free memory allocated by SHGetKnownFolderPath
		}
	}

	//if this happens either it was forced, or it failed to get the documents folder for some reason
	if (useWorkingDir) {
		fsDestinationPath = WorkingDirectory + std::string(gamedir) + "\\out";
		fsAddSourceFlags = (FFSAddSourceFlags::ENUM)5;
	}

	//Initalize Filesystem, last 4 flags might be unused
	dbgprintf("Initalizing Filesystem at: %s, With Flags: %i\n", fsDestinationPath.c_str(), fsAddSourceFlags);
	fs::init(fsDestinationPath.c_str(), fsAddSourceFlags, "out/cache", false, true, nullptr);

	Loader::IndexMods(); //after FS init due to some fs::add_source calls
	Loader::LoadNativeMods();

	//call before InitalizeGameScript
	auto s_AssetManagerImpl = GetAssetManager();
	s_AssetManagerImpl->SetGame(gamedir.c_str(), WorkingDirectory.c_str(), 0, NULL, nullptr);

	// Define paths
	std::string Game_Path = WorkingDirectory + gamedir;
	std::string Data_Path = WorkingDirectory + gamedir + "/Data";
	std::string Locale_Path = WorkingDirectory + gamedir + "/Data" + locale;
	std::string LocalePak_Path = WorkingDirectory + gamedir + "/Data" + locale + ".pak";
	std::string Speech_Path = WorkingDirectory + gamedir + "/speech" + locale;
	std::string SpeechPak_Path = WorkingDirectory + gamedir + "/speech" + locale + ".pak";

	// Add Game/DW folder
	fs::add_source(Game_Path.c_str(), (FFSAddSourceFlags::ENUM)258);

	// Add data0-3.pak sources
	for (int CurrentDataPak = 0; CurrentDataPak < 4; ++CurrentDataPak) {
		std::string dataPakPath = WorkingDirectory + gamedir + "/Data" + std::to_string(CurrentDataPak) + ".pak";
		fs::add_source(dataPakPath.c_str(), FFSAddSourceFlags::SUBDIRS);
	}

	// Add additional sources
	fs::add_source(Data_Path.c_str(), (FFSAddSourceFlags::ENUM)7);
	fs::add_source(Locale_Path.c_str(), (FFSAddSourceFlags::ENUM)265);
	fs::add_source(LocalePak_Path.c_str(), (FFSAddSourceFlags::ENUM)9);
	fs::add_source(Speech_Path.c_str(), (FFSAddSourceFlags::ENUM)265);
	fs::add_source(SpeechPak_Path.c_str(), (FFSAddSourceFlags::ENUM)9);

	Loader::LoadModPaks();
	//with pak's the last loaded overwrites the previous
	//with rpacks it's the opposite


	//Calls SteamAPI_Init() and setup online
	//Might be diffrent on some other chrome engine versions, named SteamInitialize on older CE6 versions
	if (!IGame::InitializeOnlineServices(nullptr)) {
		dbgprintf("InitializeOnlineServices Failed!");
		//Should not exit unless steam shanaigans, happened to a friend oddly
		ExitProcess(1);
	}

	//PreInitializeGameScript
	std::string GameDll_Path = WorkingDirectory + "gamedll";
	InitializeGameScript(GameDll_Path.c_str(), false);

	IGame* pGame = CreateGame("GameDI", hInstance, true, gamedir.c_str());
	dbgprintf("CreateGame GameDI at: %p\n", pGame);

	pGame->SetRootDirectory(WorkingDirectory.c_str());
	dbgprintf("IGame::SetRootDirectory at: %s\n", WorkingDirectory.c_str());

	//DLC
	auto mountHelper = Mount::CreateMountHelper(WorkingDirectory.c_str(), gamedir.c_str(), nullptr);
	CRTTIVariant variant(mountHelper);
	ttl::string_base<char> ClassName("MountHelper");

	pGame->SetProperty(ClassName, variant);

	//hide spash
	HideSplashscreen();

	//Initalize Game
	Loader::PreInitialize();


	//random test stuff
	ttl::string_base<char> bruh("Debug");

	pGame->SetRenderDebugVis(true);
	pGame->EnableDebugSocket(true, &bruh);
	//pGame->SetSpeedUpInternalOnLevels(20.0f);
	//pGame->SetUseScaleToSafeArea(true, 0.75f);
	//pGame->TimersUpdateFromServer(20.0f);
	pGame->ReplDump("DebugReplDump.txt");
	//pGame->GoDedicated();

	std::cout << "IsGameInEditor " << pGame->IsGameInEditor() << std::endl;
	std::cout << "IsDedicatedServer " << pGame->IsDedicatedServer() << std::endl;
	std::cout << "VideoSettingsIsFullScreen " << pGame->VideoSettingsIsFullScreen() << std::endl;

	if (pGame->Initialize(lpCmdLine, nShowCmd, (HICON__*)smallIcon, (HICON__*)largeIcon, 0, 0, nullptr) != 0) {
		dbgprintf("IGame::Initialize() failed\n");
		OutputDebugString("IGame::Initialize() failed\n");
		Alert("Fatal Error", "Game failed to initalize (IGame::Initialize() failed)\n");
		return EXIT_FAILURE;
	}

	ttl::string_base<char> TitleStr("Dying Light (CE6DL)");
	pGame->SetGameName(TitleStr);

	Loader::PostInitialize();

	//might try IGame rpack load func pre init and see if that works
	//after InitalizeGame, which loads the basegame rpacks
	//custom rpacks now loaded will not be able to replace base game rpacks
	Loader::LoadResourcePaks(s_AssetManagerImpl);

	//start rendering loop
	GameLoop(pGame);

	pGame->ShutdownOnlineServices();
	//Destroy Game instance if still running
	if (pGame)
		DestroyGame(NULL, NULL, NULL, NULL);

	// Shutdown the SteamAPI
	SteamAPI_Shutdown();

	//shutdown
	UninitializeGameScript();

	//fs shutdown
	CrashClose();
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