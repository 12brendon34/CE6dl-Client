//
// Created by Brendon on 1/12/2026.
//
#pragma once
#include <bit>
#include <windows.h>
#include "engine/Export.h"
#include "engine/Kernel/ttl/String.h"
#include "engine/engine/Levels/ILevel.h"
#include "games/DeadIsland/Game/Game/SessionCooperativeDI.h"

//class CRTTI {};

class CGame {};

//class IGSObject {};

//class CGSObject {};

//class ILevel {};

//wish I had more to go off of
class CRTTIVariant {
public:
    __int64 data[2] = {0};

    template<typename T>
    explicit CRTTIVariant(T *ptr) {
        data[1] = std::bit_cast<__int64>(ptr);
    }
};

struct SRPackHandle {};

struct SLoadModuleData {};

class IProgressIndicator {};

class IRecorderClientCallback {};

class ICountersSystem {};

struct SGameAddressEos {};

struct SPlayerIdEos {};

//class CVarSet {};

class ISaveManager {};

class ITagSystem {};

class PlayerState {};

class GameplayParamsManager {};

class QuestsConsole {};

class ContentManagerDI {};

class ENGINE_API IGame {
public:
    IGame();
    IGame(IGame const &);

    //static
    static bool InitializeOnlineServices(void *);
    static bool IsOnlineServicesInitialized();
    static void ShutdownOnlineServices();
    static CRTTI const *__ptr64 GetNativeClass();
    static ttl::string_base<char> GetDefaultLocaleID();
    static ttl::string_base<char> GetDefaultSpeechID(ttl::string_base<char> const &);
    static ttl::string_base<char> GetFallbackLocaleID();
    static ttl::string_base<char> GetFallbackSpeechID();
    static ttl::string_base<char> GetSystemLocaleID();
    static ttl::string_base<char> CheckForceLangParameter(ttl::string_base<char> &);

    // Initialization, Resource Pack Loading, and Level Loading
    int Initialize(char *, int, struct HICON__ *, struct HICON__ *, unsigned long, unsigned long, IProgressIndicator *);
    bool LoadPack(ttl::string_base<char> const &, bool, bool, struct SRPackHandle **);
    void FreePack(ttl::string_base<char> const &);
    bool IsAnyRPackLoaded();

    //Level
    ILevel *__ptr64 GetActiveLevel();
    ILevel *__ptr64 LoadModule(ttl::string_base<char> const &, IGSObject *, IProgressIndicator *);
    ILevel *__ptr64 LoadModuleEnd(struct SLoadModuleData *, bool);

    //CGame
    CGame *__ptr64 ToCGame();
    CGame const *__ptr64 ToCGame() const;

    //CRC Checks
    unsigned int GetMultiplayerFilesCrc() const;
    bool AreDataAuthenticatedToPlayMultiplayer() const;

    //Repl
    bool ReplInitialize();
    void ReplAddVerifyData(char const *, unsigned int, bool);
    void ReplDump(char const *) const;
    void ReplEnableReplicationIntervalChange(bool);
    //void ReplGetConnectedTargets(ttl::vector<unsigned short> &) const;

    unsigned int ReplGetConnectedTargetsCount() const;
    unsigned short ReplGetLocalId() const;
    unsigned int ReplGetNetworkId(unsigned short) const;
    unsigned short ReplGetTargetId(unsigned int) const;
    bool ReplIsConnectedTargetId(unsigned short) const;
    void ReplSetReplicationIntervalMultipliers(float, float, float, float);

    //Editor / Debug
    bool IsGameInEditor() const;
    bool IsGameInEditorRunning();
    void EnableDebugSocket(bool, ttl::string_base<char> const *);
    bool IsGuiEditorMode();
    bool IsEditorGameMode();
    void AddEditorCriticalError(ttl::string_base<char> const &);
    void AddEditorWarning(ttl::string_base<char> const &);
    char const *__ptr64*__ptr64 GetCommandLineArgs();
    int GetCommandLineArgsCount();
    void DebugDisableHyperThreading();

    //SDL / Window
    void DoSdlLoop();
    void PollSdlEvents();
    void OnPaint();
    HWND__ *__ptr64 GethWnd() const;

    //Screen
    int GetScreenHeight();
    int GetScreenWidth();
    float GetScaleToSafeAreaFactor() const;
    float GetCameraAspect() const;

    //Render
    bool IsBackgroundRender();
    bool IsBackgroundRenderBlocked();
    bool IsGameRenderingEnabled();
    void EnableGameRendering(bool);

    //Render Debug
    void SetRenderDebugVis(bool);

    //Font
    bool RegisterFontStyle(ttl::string_base<char> const &, ttl::string_base<char> const &, float, float);
    void SetDefaultFont(ttl::string_base<char> const &);
    void RemoveFontStyle(ttl::string_base<char> const &);
    void RemoveFontStyles();
    void RemoveFonts();
    bool IsFontStyle(ttl::string_base<char> const &);
    bool LoadFontsScript(ttl::string_base<char> const &, bool);
    bool LoadFontsStyleScript(ttl::string_base<char> const &);

    //Server
    void GoDedicated();
    bool IsDedicatedServer();

    //Recording
    void EnableAVIRecording(ttl::string_base<char> const &, float, bool);
    void DisableAVIRecording();
    void ChooseAVICodecAndExit();
    void StopAVIRecording();
    void RecordGameplayClip(ttl::string_base<wchar_t>, ttl::string_base<wchar_t>, float, float, float, IRecorderClientCallback *);

    //Screenshot
    void TakeScreenshot(ttl::string_base<char> const &);
    void TakeScreenshot(ttl::string_base<char> const &, int, int);
    void TakeScreenshot();

    void EnableContinuousScreenshotRecording(ttl::string_base<char> const &, float);
    void DisableContinuousScreenshotRecording();

    //Input
    void AcquireInput(bool);
    void StartInputPlaying(ttl::string_base<char> const &);
    void StopInputPlaying();
    void StartInputRecording(ttl::string_base<char> const &);
    void StopInputRecording();
    void EnableInputPlaying(ttl::string_base<char> const &, float);
    void EnableInputRecording(ttl::string_base<char> const &, float, ttl::string_base<char> const &);

    //Timers / Time
    void TimersDefaultFrozen(bool);
    void TimersNextStep(float);
    void TimersStart();
    void TimersStop();
    void TimersUpdate();
    void TimersUpdateFromServer(float);
    void TimersUpdateSkip();
    float GetGameLastTime() const;
    float GetGameTimeDelta() const;
    float GetGameTime() const;
    void FreezeTimersOnLevels();
    void UnFreezeTimersOnLevels();
    void SaveLevelsTimersState();
    void RestoreLevelsTimersState();

    //Sound
    void StartSoundRecording(ttl::string_base<char> const &);
    void StopSoundRecording();

    //Quit
    void CrashQuit(ttl::string_base<char> const &);
    void ExitGame();

    //Too Lazy to sort
    void EnableDontDropConnetion(bool);
    void EnableFramePipelining(bool);
    int GetCodePage();
    ICountersSystem const *__ptr64 GetCountersSystem() const;
    ttl::string_base<char> GetLocaleID();
    char const *__ptr64 GetRootDirectory() const;
    bool IsRenderUiInEditor();
    bool IsUseScaleToSafeArea() const;
    bool IsWPFInteropMode();
    SLoadModuleData *__ptr64 LoadModuleBegin(ttl::string_base<char> const &, IGSObject *, IProgressIndicator *);
    bool LoadModuleFinished(SLoadModuleData *);
    SGameAddressEos const LobbyGetClientAddress(unsigned int);
    SPlayerIdEos LobbyGetClientPlayerId(unsigned int);
    ttl::string_base<wchar_t> const LobbyGetClientProfileName(unsigned int);
    unsigned int LobbyGetMasterNetId();
    bool LobbyIsNetworkIdValid(unsigned int);
    void MsgSend(unsigned int, unsigned char const *, unsigned int);
    void PauseContinuousScreenshotRecording(bool);
    ttl::string_base<char> const ReadAdditionalTextFromInputFile(ttl::string_base<char> const &);
    void ResetPerformanceTest();
    void SetDefaultModuleStartTime(float);
    void SetGameName(ttl::string_base<char> const &);
    void SetGameNameExplicit(ttl::string_base<wchar_t> const &);
    void SetLoadingPercentage(float, float);
    bool SetLocaleID(char const *) const;
    bool SetRootDirectory(char const *);
    void SetSafeMode(bool);
    void SetScreenshotParams(int, int);
    bool SetSpeechID(char const *, bool) const;
    void SetSpeedUpInternalOnLevels(float);
    void SetUseScaleToSafeArea(bool, float);
    void SetXboxOneMatchHopper(int);
    void WaitForPipelineThreads();

    //unimp
    //void CallOnFrameEnd(CRTTIVoidFunctor<IGSObject> const&);
    //ChromeSpy::IDataCollector* __ptr64 GetDataCollector() const;
    //EPadDevice::TYPE GetForceShowControllerId() const;
    //float GetScreenResolutionScale(EScreenResolutionScale::TYPE);
    //void RemoveFromFrameEnd(CRTTIVoidFunctor<IGSObject> const&);
    //void RemoveFromFrameEnd(IGSObject*);
    //StreamStatus StreamIsFinished(SRPackStreamHandle*, bool);
    //SRPackStreamHandle* __ptr64 StreamLoadMesh(SRPackHandle*, ttl::string_base<char> const&, int);
    //void StreamUnloadMesh(SRPackStreamHandle*);

    virtual void __cdecl SetEngineObject(CGSObject *__ptr64);
    virtual ~IGame();

    //stripped functions
    virtual void Stripped(); //IPhBody::~IPhBody
    virtual void Stripped1(); //IPhBody::~IPhBody
    virtual void Stripped2(); //IPhBody::~IPhBody
    virtual void Stripped3(); //IPhBody::~IPhBody
    virtual void Stripped4(); //IPhBody::~IPhBody
    virtual void Stripped5(); //IPhBody::~IPhBody
    virtual void Stripped6(); //IPhBody::~IPhBody
    virtual void Stripped7(); //IPhBody::~IPhBody
    virtual void Stripped8(); //IPhBody::~IPhBody
    virtual void Stripped9(); //IPhBody::~IPhBody
    virtual void Stripped10(); //IPhBody::~IPhBody
    virtual void Stripped11(); //IPhBody::~IPhBody

    virtual void OnContentChanged();

    virtual void Stripped12(); //IPhBody::~IPhBody
    virtual void Stripped13(); //IPhBody::~IPhBody
    virtual void Stripped14(); //IPhBody::~IPhBody
    virtual void Stripped15(); //IPhBody::~IPhBody
    virtual void Stripped16(); //IPhBody::~IPhBody
    virtual void Stripped17(); //IPhBody::~IPhBody
    virtual void Stripped18(); //IPhBody::~IPhBody
    virtual void Stripped19(); //IPhBody::~IPhBody
    virtual void Stripped20(); //IPhBody::~IPhBody
    virtual void Stripped21(); //IPhBody::~IPhBody
    virtual void Stripped22(); //IPhBody::~IPhBody
    virtual void Stripped23(); //IPhBody::~IPhBody
    virtual void Stripped24(); //IPhBody::~IPhBody
    virtual void Stripped25(); //IPhBody::~IPhBody
    virtual void Stripped26(); //IPhBody::~IPhBody
    virtual void Stripped27(); //IPhBody::~IPhBody
    virtual void Stripped28(); //IPhBody::~IPhBody
    virtual void Stripped29(); //IPhBody::~IPhBody
    virtual void Stripped30(); //IPhBody::~IPhBody
    virtual bool Stripped31();

    virtual void Stripped32(); //IPhBody::~IPhBody
    virtual void Stripped33(); //IPhBody::~IPhBody
    virtual void Stripped34(); //IPhBody::~IPhBody
    virtual void Stripped35(); //IPhBody::~IPhBody
    virtual void Stripped36(); //IPhBody::~IPhBody
    virtual void Stripped37(); //IPhBody::~IPhBody
    virtual void Stripped38(); //IPhBody::~IPhBody
    virtual void Stripped39(); //IPhBody::~IPhBody
    virtual void Stripped40(); //IPhBody::~IPhBody
    virtual void Stripped41(); //IPhBody::~IPhBody
    virtual void Stripped42(); //IPhBody::~IPhBody
    virtual void Stripped43(); //IPhBody::~IPhBody
    virtual void Stripped44(); //IPhBody::~IPhBody
    virtual void Stripped45(); //IPhBody::~IPhBody

    virtual void SetProperty(ttl::string_base<char> const &, CRTTIVariant const &);
    virtual CVarSet *__ptr64 GetVarSet();
    virtual int StrippedENUMORINT();
    virtual char const *__ptr64 GetGameDirectoryName() const;
    virtual ttl::string_base<char> GetGameCustomText();
    virtual ILevel *__ptr64 GetLevelEditor();
    virtual char const *__ptr64 GetVoiceLocaleID();

    virtual int Stripped46();
    virtual void Stripped47(); //IPhBody::~IPhBody
    virtual void Stripped48(); //IPhBody::~IPhBody
    virtual void Stripped49(); //IPhBody::~IPhBody
    virtual void Stripped50(); //IPhBody::~IPhBody
    virtual void Stripped51(); //IPhBody::~IPhBody
    virtual bool Stripped52();
    virtual bool Stripped53();
    virtual void Stripped54(); //IPhBody::~IPhBody
    virtual void Stripped55(); //IPhBody::~IPhBody
    virtual void Stripped56(); //IPhBody::~IPhBody

    virtual int Main();

    virtual void NonInteractiveSequenceBegin();
    virtual void NonInteractiveSequenceEnd();
    virtual void RestartTimeoutTimer();

    virtual bool Stripped57();
    virtual void Stripped58(); //IPhBody::~IPhBody
    virtual bool Stripped59();
    virtual void Stripped60(); //IPhBody::~IPhBody
    virtual void Stripped61(); //IPhBody::~IPhBody
    virtual void Stripped62(); //IPhBody::~IPhBody
    virtual void Stripped63(); //IPhBody::~IPhBody
    virtual void Stripped64(); //IPhBody::~IPhBody
    virtual void Stripped65(); //IPhBody::~IPhBody
    virtual void Stripped66(); //IPhBody::~IPhBody
    virtual void Stripped67(); //IPhBody::~IPhBody
    virtual void Stripped68(); //IPhBody::~IPhBody
    virtual void Stripped69(); //IPhBody::~IPhBody
    virtual void Stripped70(); //IPhBody::~IPhBody
    virtual void Stripped71(); //IPhBody::~IPhBody
    virtual void Stripped72(); //IPhBody::~IPhBody
    virtual void Stripped73(); //IPhBody::~IPhBody
    virtual void Stripped74(); //IPhBody::~IPhBody
    virtual void Stripped75(); //IPhBody::~IPhBody
    virtual void Stripped76(); //IPhBody::~IPhBody
    virtual void Stripped77(); //IPhBody::~IPhBody
    virtual void Stripped78(); //IPhBody::~IPhBody
    virtual void Stripped79(); //IPhBody::~IPhBody
    virtual void Stripped80(); //IPhBody::~IPhBody
    virtual void Stripped81(); //IPhBody::~IPhBody
    virtual void Stripped82(); //IPhBody::~IPhBody
    virtual void Stripped83(); //IPhBody::~IPhBody
    virtual void Stripped84(); //IPhBody::~IPhBody
    virtual void Stripped85(); //IPhBody::~IPhBody
    virtual void Stripped86(); //IPhBody::~IPhBody
    virtual void Stripped87(); //IPhBody::~IPhBody
    virtual void Stripped88(); //IPhBody::~IPhBody

    virtual ttl::string_base<char> GetProperFont(ttl::string_base<char> const &);
    virtual float GetProperFontScale(ttl::string_base<char> const &, float, bool);
    virtual ttl::string_base<char> GetDefaultFont();

    virtual void Stripped89(); //IPhBody::~IPhBody
    virtual void Stripped90(); //IPhBody::~IPhBody
    virtual void Stripped91(); //IPhBody::~IPhBody
    virtual ttl::string_base<char> GetGamescriptUIVersion();

    virtual int Stripped92();

    virtual ISaveManager *__ptr64 GetSaveManager();

    virtual bool Stripped93();
    virtual void Stripped94(); //IPhBody::~IPhBody
    virtual ITagSystem &GetTagSystem();

    virtual bool Stripped95();
    virtual int Stripped96();
    virtual void Stripped97(); //IPhBody::~IPhBody
    virtual void Stripped98(); //IPhBody::~IPhBody
    virtual void Stripped99(); //IPhBody::~IPhBody
    virtual void Stripped100(); //IPhBody::~IPhBody
    virtual void Stripped101(); //IPhBody::~IPhBody
    virtual void Stripped102(); //IPhBody::~IPhBody
    virtual int Stripped103();
    virtual int Stripped104();
    virtual int Stripped105();
    virtual void Stripped106(); //IPhBody::~IPhBody
    virtual int Stripped107();
    virtual int Stripped108();
    virtual void Stripped109(); //IPhBody::~IPhBody
    virtual void Stripped110(); //IPhBody::~IPhBody

    virtual ttl::string_base<char> GetTitleId() const;
    virtual void SetTitleId(ttl::string_base<char> const &);

    virtual bool Stripped111();
    virtual void Stripped112(); //IPhBody::~IPhBody
    virtual void Stripped113(); //IPhBody::~IPhBody
    virtual void Stripped114(); //IPhBody::~IPhBody
    virtual void Stripped115(); //IPhBody::~IPhBody
    virtual bool Stripped116();
    virtual bool Stripped117();
    virtual bool Stripped118();
    virtual void Stripped119(); //IPhBody::~IPhBody

    virtual bool VideoSettingsIsFullScreen();
    virtual void SetFocusOnWindow();
    virtual void SetVisibilityFactors(float, float);
    virtual void GetVisibilityFactors(float &, float &);
    virtual unsigned int GetFrameCounter() const;

    virtual void Stripped120(); //IPhBody::~IPhBody
    virtual void Stripped121(); //IPhBody::~IPhBody
    virtual void Stripped122(); //IPhBody::~IPhBody
    virtual void Stripped123(); //IPhBody::~IPhBody
    virtual void Stripped124(); //IPhBody::~IPhBody
    virtual bool Stripped125();
    virtual void Stripped126(); //IPhBody::~IPhBody
    virtual void Stripped127(); //IPhBody::~IPhBody
    virtual void Stripped128(); //IPhBody::~IPhBody

    virtual ttl::string_base<char> GetConfigurationName() const;

    virtual bool Stripped129();
    virtual void Stripped130(); //IPhBody::~IPhBody
    virtual void Stripped131(); //IPhBody::~IPhBody
    virtual void Stripped132(); //IPhBody::~IPhBody
    virtual void Stripped133(); //IPhBody::~IPhBody
    virtual void Stripped134(); //IPhBody::~IPhBody

    virtual bool IsLowViolence() const;
    virtual ttl::string_base<char> GetGameCustomText_2();

    virtual bool Stripped135();

    virtual ttl::string_base<char> const &GetTitleStorageFullGameProductId(ttl::string_base<char> const &) const;

    virtual int Stripped136();
    virtual bool Stripped137();
    virtual void Stripped139();

    //8 bytes
    CGame *m_CGame;
    char pad_0028[392];
    char *m_Username; //0x0198
    char pad_01A0[920]; //0x01A0
    ContentManagerDI *m_ContentManagerDI; //0x0538
    SessionCooperativeDI *m_Session; //0x0540
    char pad_0548[16]; //0x0548
    PlayerState *m_PlayerState; //0x0558
    PlayerState *m_MenuPlayerState; //0x0560
    GameplayParamsManager *m_GameplayParamsManager; //0x0568
    QuestsConsole *m_QuestsConsole; //0x0570
};
