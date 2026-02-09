//
// Created by Brendon on 2/7/2026.
//

#include "MainFrame.h"

#include <memory>
#include <shlobj_core.h>

#include "engine/Debug.h"
#include "engine/engine/ChromeEngine.h"
#include "engine/engine/FNode/MeshLinker.h"
#include "engine/engine/resourcemanagement/AssetManager.h"
#include "engine/engine/resourcemanagement/MountHelper.h"
#include "engine/filesystem/Filesystem.h"

#define BUF_SIZE MAX_PATH
constexpr bool bUseMyDocuments = false;
constexpr auto kGameDir = "DW"; // Dead World
constexpr auto kSubPath = "DyingLight";
constexpr auto kCacheSubPath = "out/cache";

// IMPLEMENT_DYNAMIC(CMainFrame, CFrameWnd)
BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
ON_WM_CREATE()
ON_WM_SETFOCUS()
END_MESSAGE_MAP()

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT &cs) {
    if (!CFrameWnd::PreCreateWindow(cs))
        return FALSE;
    // TODO: Modify the Window class or styles here by modifying
    //  the CREATESTRUCT cs

    cs.style = WS_OVERLAPPED | WS_CAPTION | FWS_ADDTOTITLE | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_SYSMENU;

    cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
    cs.lpszClass = AfxRegisterWndClass(0);
    return TRUE;
}

void LogCallback(Log::ELevel::TYPE, const char *a, const char *b) {
    dbgprintf("%s , %s", a, b);
}

class IEditorimpl {
public:
    virtual ~IEditorimpl() = default;
    virtual const char *func1() { return "DW"; }
    virtual void func2() { dbgprintf("Call2"); } // need to figure out what this is supposted to do
    virtual const char *targetFunction() { return "UNKNOWN"; }
    virtual void func4() { dbgprintf("Call4"); }
    virtual void func5() { dbgprintf("Call5"); }
    virtual void func6() { dbgprintf("Call6"); } //called
    virtual void func7() { dbgprintf("Call7"); }
    virtual void func8() { dbgprintf("Call8"); }
    virtual void func9() { dbgprintf("Call9"); }
    virtual void func10() { dbgprintf("Call10"); }
    virtual void func11() { dbgprintf("Call11"); }
    virtual void func12() { dbgprintf("Call12"); }
    virtual void func13() { dbgprintf("Call13"); }
    virtual void func14() { dbgprintf("Call14"); }
    virtual void func15() { dbgprintf("Call15"); }
    virtual void func16() { dbgprintf("Call16"); }
    virtual void func17() { dbgprintf("Call17"); }
    virtual void func18() { dbgprintf("Call18"); }
    virtual void func19() { dbgprintf("Call19"); }
    virtual void func20() { dbgprintf("Call20"); }
    virtual void func21() { dbgprintf("Call21"); } //called
    virtual void func22() { dbgprintf("Call22"); }
    virtual void func23() { dbgprintf("Call23"); }
    virtual void func24() { dbgprintf("Call24"); }
    virtual void func25() { dbgprintf("Call25"); }
    virtual void func26() { dbgprintf("Call26"); }
    virtual void func27() { dbgprintf("Call27"); }
    virtual void func28() { dbgprintf("Call28"); }
    virtual void func29() { dbgprintf("Call29"); }
    virtual void func30() { dbgprintf("Call30"); }
    virtual void func31() { dbgprintf("Call31"); }
    virtual void func32() { dbgprintf("Call32"); }
    virtual void func33() { dbgprintf("Call33"); }
    virtual bool targetFunction2() {
        dbgprintf("Target Func 2");
        // jump to 34B130
        return false;
    }
    virtual void func35() { dbgprintf("Call35"); }
    virtual void func36() { dbgprintf("Call36"); }
    virtual void func37() { dbgprintf("Call37"); }
    virtual void func38() { dbgprintf("Call38"); }
    virtual void func39() { dbgprintf("Call39"); } //called
    virtual void func40() { dbgprintf("Call40"); }
    virtual void func41() { dbgprintf("Call41"); }
    virtual void func42() { dbgprintf("Call42"); }
    virtual void func43() { dbgprintf("Call43"); }
    virtual void func44() { dbgprintf("Call44"); }
    virtual void func45() { dbgprintf("Call45"); }
    virtual void func46() { dbgprintf("Call46"); }
    virtual void func47() { dbgprintf("Call47"); }
    virtual void func48() { dbgprintf("Call48"); }
    virtual void func49() { dbgprintf("Call49"); }
    virtual void func50() { dbgprintf("Call50"); }
    virtual void func51() { dbgprintf("Call51"); }
    virtual void func52() { dbgprintf("Call52"); }
    virtual void func53() { dbgprintf("Call53"); }
    // 53 total
};


int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct) {
    char szCurrDir[BUF_SIZE] = {};
    char szPath[BUF_SIZE] = {};

#ifdef _DEBUG
    FILE *fp;
    AllocConsole();
    freopen_s(&fp, "CONOUT$", "w", stdout);
    freopen_s(&fp, "CONOUT$", "w", stderr);

    while (!::IsDebuggerPresent())
        ::Sleep(100); // to avoid 100% CPU load
#endif

    if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
        return -1;

    // create a view to occupy the client area of the frame
    if (!m_wndView.Create(nullptr, nullptr, AFX_WS_DEFAULT_VIEW, CRect(0, 0, 0, 0), this, AFX_IDW_PANE_FIRST, nullptr)) {
        TRACE0("Failed to create view window\n");
        return -1;
    }


    //a lot of this is likely not needed, but I still haven't gotten Initialize to pass without patching the engine (which breaks things anyways)
    //sorta a test project to see if I can setup a "editor", I linked against the base game exe, so it might have a chance with the real editor binarys
    //although this doesn't do much, it's a example MFC app with a empty window + the IEngineImpl = Initialize ofc

    char szExeDir[BUF_SIZE] = {};
    char drive[_MAX_DRIVE] = {};
    char dir[_MAX_DIR] = {};

    if (!Main())
        return EXIT_FAILURE;

    GetModuleFileName(nullptr, szExeDir, BUF_SIZE);
    _splitpath_s(szExeDir, drive, _MAX_DRIVE, dir, _MAX_DIR, nullptr, 0, nullptr, 0);
    strcpy_s(szExeDir, BUF_SIZE, drive);
    strcat_s(szExeDir, BUF_SIZE, dir);
    strcpy_s(szCurrDir, BUF_SIZE, szExeDir);

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

    const auto bInitSuccess = fs::init(szPath, write_path_flags, kCacheSubPath, false, true, nullptr);
    if (!bInitSuccess)
        return -1;

    const auto s_AssetManagerImpl = GetAssetManager();
    s_AssetManagerImpl->SetGame(kGameDir, szCurrDir, 0, NULL, nullptr);

    // Get DW path
    char sBaseDir[BUF_SIZE] = {};
    strcpy_s(sBaseDir, BUF_SIZE, szCurrDir);
    strcat_s(sBaseDir, BUF_SIZE, kGameDir);
    fs::add_source(sBaseDir, FFSAddSourceFlags::APPEND);

    char sEngineDir[BUF_SIZE] = {};
    strcpy_s(sEngineDir, BUF_SIZE, szCurrDir);
    strcat_s(sEngineDir, BUF_SIZE, "Engine");
    fs::add_source(sEngineDir, FFSAddSourceFlags::APPEND);


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

    // Add Engine Data dir
    char sEDataDir[BUF_SIZE] = {};
    strcpy_s(sEDataDir, BUF_SIZE, sBaseDir);
    strcat_s(sEDataDir, BUF_SIZE, "\\Data");
    fs::add_source(sEDataDir, FFSAddSourceFlags::SUBDIRS | FFSAddSourceFlags::APPEND | FFSAddSourceFlags::PRELOAD);


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

    const auto mountHelper = Mount::CreateMountHelper(szCurrDir, kGameDir, nullptr);
    const CRTTIVariant variant(mountHelper);

    HINSTANCE hInst = lpCreateStruct->hInstance;
    HWND hwndMain = this->GetSafeHwnd();
    HWND hwndMsgTarget = this->GetSafeHwnd();
    void *userContext = nullptr;

    const char *gameName = "GameDI";
    const char *videoScr = "Out/Settings/EditorVideo.scr";
    const char *audioScr = "Out/Settings/EditorAudio.scr";

    dbgprintf("GameClass :%s\n", gameName);
    dbgprintf("szGameScriptDLL :%s\n", szGameScriptDLL);
    dbgprintf("videoScr :%s\n", videoScr);
    dbgprintf("audioScr :%s\n", audioScr);

    IEditorimpl Dummy;
    const auto IEngineImpl = Initialize(hInst, hwndMain, hwndMsgTarget, &Dummy, gameName, szGameScriptDLL, videoScr, audioScr, LogCallback, userContext);

    return 0;
}

void CMainFrame::OnSetFocus(CWnd * /*pOldWnd*/) {
    // forward focus to the view window
    m_wndView.SetFocus();
}
