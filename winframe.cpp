#include <pch.h>
#include "utils/Utils.h"
#include "engine/Link.h"

typedef uint32 AppId_t;
const AppId_t k_uAppId = 239140;

int Alert(const char* lpCaption, const char* lpText)
{
	return ::MessageBox(NULL, lpText, lpCaption, MB_OK);
}

void MiniDumpFunction(unsigned int nExceptionCode, EXCEPTION_POINTERS* pException)
{
	bool MiniDumpType = false;
	Filesystem::WriteFullDump(nExceptionCode, pException, NULL, MiniDumpType, NULL);
}

void GameLoop(void* pGame) {
	MSG msg;

	while (true) {
		while (PeekMessageA(&msg, nullptr, 0, 0, PM_REMOVE) == NULL) {
			Engine::OnPaint(pGame);
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

#ifdef _DEBUG
	//not really a good thing but I use it alot
	while (!::IsDebuggerPresent())
		::Sleep(100);
#endif

	Utils::InitConsole();

	if (!LoadGameLibarys()) {
		return EXIT_FAILURE;
	}

	std::string WorkingDirectory;
	std::string gamedir = "DW";
	std::string locale = "En";
	bool DumpRTTI = false;
	bool WriteFullDump = false;

	//cmdline param's here
	if (WorkingDirectory.empty()) {
		WorkingDirectory = Utils::GetWorkingDirectory();
	}

	int EngineMain = Engine::Main();
	if (EngineMain == NULL) {
		return EXIT_SUCCESS;
	}

	// Get Resorces for splash
	auto hSplash = MAKEINTRESOURCE(159);  // Game Splash Resource
	auto hText = MAKEINTRESOURCE(160);    // Dying Light String Resource
	auto hIcon = MAKEINTRESOURCE(161);    // Game Icon Resource

	int smallIconWidth = GetSystemMetrics(SM_CXSMICON);
	int smallIconHeight = GetSystemMetrics(SM_CYSMICON);
	auto smallIcon = LoadImage(hInstance, hIcon, IMAGE_ICON, smallIconWidth, smallIconHeight, 0);

	int largeIconWidth = GetSystemMetrics(SM_CXICON);
	int largeIconHeight = GetSystemMetrics(SM_CYICON);
	auto largeIcon = LoadImage(hInstance, hIcon, IMAGE_ICON, largeIconWidth, largeIconHeight, 0);
	Engine::ShowSplashscreen(hInstance, hSplash, hText, smallIcon);

	//Filesystem Setup
	int fsAddSourceFlags;
	std::string fsDestinationPath;
	std::string fsSaveDir = "DyingLight"; // Default is Documents folder/DyingLight

	bool useWorkingDir = false;
	bool isFullPath = (Filesystem::IsFullPath(fsSaveDir.c_str()) != NULL);

	// Won't be a full path unless hardcoded
	if (isFullPath) {
		fsDestinationPath = fsSaveDir;
		fsAddSourceFlags = 1;
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
			fsAddSourceFlags = 1;
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
		fsAddSourceFlags = 5;
	}

	//Initalize Filesystem, last 4 flags might be unused
	Filesystem::Init(fsDestinationPath.c_str(), fsAddSourceFlags, "out/cache", false, true, nullptr);

	void* AssetMngVt = Engine::GetAssetManager();
	Engine::AssetManager = *reinterpret_cast<Engine::T_AssetManager**>(AssetMngVt)[0];
	Engine::AssetManager(AssetMngVt, gamedir.c_str(), WorkingDirectory.c_str(), 0, NULL, NULL);

	//Low Priority Paks Here
	// Define paths
	std::string DW_Path = WorkingDirectory + gamedir;
	std::string Data_Path = WorkingDirectory + gamedir + "/Data";
	std::string Locale_Path = WorkingDirectory + gamedir + "/Data" + locale;
	std::string LocalePak_Path = WorkingDirectory + gamedir + "/Data" + locale + ".pak";
	std::string Speech_Path = WorkingDirectory + gamedir + "/speech" + locale;
	std::string SpeechPak_Path = WorkingDirectory + gamedir + "/speech" + locale + ".pak";

	// Add DW folder
	Filesystem::Add_Source(DW_Path.c_str(), 258);

	// Add data0-3.pak sources
	for (int CurrentDataPak = 0; CurrentDataPak < 4; ++CurrentDataPak) {
		std::string dataPakPath = WorkingDirectory + gamedir + "/Data" + std::to_string(CurrentDataPak) + ".pak";
		Filesystem::Add_Source(dataPakPath.c_str(), 1);
	}

	// Add additional sources
	Filesystem::Add_Source(Data_Path.c_str(), 7);
	Filesystem::Add_Source(Locale_Path.c_str(), 265);
	Filesystem::Add_Source(LocalePak_Path.c_str(), 9);
	Filesystem::Add_Source(Speech_Path.c_str(), 265);
	Filesystem::Add_Source(SpeechPak_Path.c_str(), 9);
	//High Priority Paks Here

	//Calls SteamAPI_Init() and other online stuff
	//Might be diffrent on some other chrome engine versions, such as SteamInitialize on older CE6 versions
	if (!Engine::InitializeOnlineServices()) {
		//Should not exit unless steam shanaigans, happened to a friend oddly
		ExitProcess(1);
	}

	std::string GameDll_Path = WorkingDirectory + "gamedll";
	Engine::InitializeGameScript(GameDll_Path.c_str(), false);

	void* pGame = Engine::CreateGame("GameDI", hInstance, true, gamedir.c_str());
	Engine::SetRootDirectory(pGame, WorkingDirectory.c_str());

	//MountHelper (Loads DLC's)

	Engine::HideSplashscreen();

	if (Engine::Initialize(pGame, lpCmdLine, nShowCmd, smallIcon, largeIcon, 0, 0, nullptr) != 0) {
		OutputDebugString("IGame::Initialize() failed\n");
		Alert("Fatal Error", "Game failed to initalize (IGame::Initialize() failed)\n");
		return EXIT_FAILURE;
	}

	GameLoop(pGame);

	//Destroy Game instance if still running
	if (pGame)
		Engine::DestroyGame(NULL, NULL, NULL, NULL);

	// Shutdown the SteamAPI
	SteamAPI_Shutdown();

	//shutdown
	Engine::UninitializeGameScript();
	Engine::ShutdownOnlineServices();

	//fs shutdown
	Filesystem::CrashClose();
	Filesystem::Shutdown();

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