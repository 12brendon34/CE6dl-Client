#include <pch.h>
#include "SDK/Engine/engine_x64_rwdi.h"
#include "SDK/Filesystem/filesystem_x64_rwdi.h"
#include <random>
#include "Core/Loader.h"

typedef uint32 AppId_t;
const AppId_t k_uAppId = 239140;

bool SteamInit();
bool FilesystemInit(std::string WorkingDirectory, std::string gameDir, bool useWorkingDir = false);
void GameLoop(IGame* pGame);
int Alert(const char* lpCaption, const char* lpText);
void MiniDumpFunction(unsigned int nExceptionCode, EXCEPTION_POINTERS* pException);


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	if(SteamInit())
		return EXIT_FAILURE;

#ifdef _DEBUG
	Utils::InitConsole();
	std::cout << "Attach Debugger" << std::endl;
	
	while (!::IsDebuggerPresent())
		::Sleep(100);
#endif

	//parse arguments
	std::string WorkingDirectory;

	std::string gamedir = "DW"; //Dead World lol
	std::string locale = "En"; // ISteamApps::GetCurrentGameLanguage maybe some time

	if (WorkingDirectory.empty())
		WorkingDirectory = Utils::GetWorkingDirectory();

	std::string GameDll_Path = WorkingDirectory + "gamedll";


	if (!Main())
		return EXIT_FAILURE;

	//IDK what EDumpResult is so this is good enough I guess

	auto DumpFunc = GetDumpFunction();
	SetDumpFunction(reinterpret_cast<EDumpResult::TYPE(__cdecl*)(unsigned long, _EXCEPTION_POINTERS*)>(MiniDumpFunction));

	//select a random splash
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dist(101, 106);

	int randomSplash = dist(gen);
	auto hSplash = MAKEINTRESOURCE(randomSplash);
	auto hText = MAKEINTRESOURCE(100);    // Dying Light String Resource
	auto hIcon = MAKEINTRESOURCE(110);    // Game Icon Resource

	int smallIconWidth = GetSystemMetrics(SM_CXSMICON);
	int smallIconHeight = GetSystemMetrics(SM_CYSMICON);
	auto smallIcon = LoadImage(hInstance, hIcon, IMAGE_ICON, smallIconWidth, smallIconHeight, 0);

	int largeIconWidth = GetSystemMetrics(SM_CXICON);
	int largeIconHeight = GetSystemMetrics(SM_CYICON);
	auto largeIcon = LoadImage(hInstance, hIcon, IMAGE_ICON, largeIconWidth, largeIconHeight, 0);

	ShowSplashscreen(hInstance, hSplash, hText, smallIcon);
	Sleep(1500);

	//Filesystem
	FilesystemInit(WorkingDirectory, "DW", true);
	Loader::IndexMods();
	Loader::LoadNativeMods();

	//Needed for InitalizeGameScript
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


	//Initalization
	if (!IGame::InitializeOnlineServices(nullptr)) {
		dbgprintf("InitializeOnlineServices Failed!");
		ExitProcess(1);
	}

	InitializeGameScript(GameDll_Path.c_str(), false);
	IGame* pGame = CreateGame("GameDI", hInstance, true, gamedir.c_str());
	dbgprintf("CreateGame IGame at: %p\n", pGame);

	pGame->SetRootDirectory(WorkingDirectory.c_str());
	dbgprintf("IGame::SetRootDirectory at: %s\n", WorkingDirectory.c_str());

	//DLC
	auto mountHelper = Mount::CreateMountHelper(WorkingDirectory.c_str(), gamedir.c_str(), nullptr);
	CRTTIVariant variant(mountHelper);
	ttl::string_base<char> ClassName("MountHelper");

	pGame->SetProperty(ClassName, variant);
	HideSplashscreen();

	Loader::PreInitialize();	
	if (pGame->Initialize(lpCmdLine, nShowCmd, (HICON__*)smallIcon, (HICON__*)largeIcon, 0, 0, nullptr) != 0)
	{
		dbgprintf("IGame::Initialize() failed\n");
		OutputDebugString("IGame::Initialize() failed\n");
		Alert("Fatal Error", "Game failed to initalize (IGame::Initialize() failed)\n");
		return EXIT_FAILURE;
	}

	std::cout << "IsGameInEditor " << pGame->IsGameInEditor() << std::endl;
	std::cout << "IsDedicatedServer " << pGame->IsDedicatedServer() << std::endl;
	std::cout << "VideoSettingsIsFullScreen " << pGame->VideoSettingsIsFullScreen() << std::endl;

	ttl::string_base<char> TitleStr("Dying Light (CE6DL)");
	pGame->SetGameName(TitleStr);

	Loader::PostInitialize();
	Loader::LoadResourcePaks(pGame);

	//start rendering loop
	GameLoop(pGame);

	pGame->ShutdownOnlineServices();
	//Destroy Game instance if still running
	if (pGame)
		DestroyGame(NULL, NULL, NULL, NULL);

	Mount::DestroyMountHelper(mountHelper);

	// Shutdown the SteamAPI
	SteamAPI_Shutdown();

	//shutdown
	UninitializeGameScript();

	//fs shutdown
	CrashClose();
	fs::shutdown();
	SetDumpFunction(DumpFunc);

	return EXIT_SUCCESS;
}

bool FilesystemInit(std::string WorkingDirectory, std::string gameDir, bool useWorkingDir)
{
	//Documents folder name or full path
	std::string fsSaveDir("DyingLight");

	if (fs::is_full_path(fsSaveDir.c_str()))
		return fs::init(fsSaveDir.c_str(), FFSAddSourceFlags::SUBDIRS, "out/cache", false, true, nullptr);

	if (!useWorkingDir)
	{
		PWSTR path = nullptr;
		HRESULT hr = SHGetKnownFolderPath(FOLDERID_Documents, 0, nullptr, &path);

		if (SUCCEEDED(hr)) {
			char pathBuffer[MAX_PATH];
			WideCharToMultiByte(CP_UTF8, 0, path, -1, pathBuffer, MAX_PATH, NULL, NULL);

			CoTaskMemFree(path);

			std::string fsDestinationPath = std::string(pathBuffer) + "\\" + fsSaveDir;
			return fs::init(fsDestinationPath.c_str(), FFSAddSourceFlags::SUBDIRS, "out/cache", false, true, nullptr);
		}

		if (path) {
			CoTaskMemFree(path);
		}
	}

	std::string fsDestinationPath = WorkingDirectory + std::string(gameDir) + "\\out";
	return fs::init(fsDestinationPath.c_str(), (FFSAddSourceFlags::ENUM)5, "out/cache", false, true, nullptr);
}

bool SteamInit() {
	if (SteamAPI_RestartAppIfNecessary(k_uAppId))
		return EXIT_FAILURE;

	if (!SteamAPI_Init())
	{
		OutputDebugString("SteamAPI_Init() failed\n");
		Alert("Fatal Error", "Steam must be running to play Dying Light (SteamAPI_Init() failed).\n");
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
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

void MiniDumpFunction(unsigned int nExceptionCode, EXCEPTION_POINTERS* pException)
{
	bool MiniDumpType = false;
	WriteFullDump(nExceptionCode, pException, nullptr, MiniDumpType, nullptr);
}

int Alert(const char* lpCaption, const char* lpText)
{
	return ::MessageBox(nullptr, lpText, lpCaption, MB_OK);
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