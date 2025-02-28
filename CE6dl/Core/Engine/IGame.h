#pragma once
#include "pch.h"
#include "../TTL.h"

class CRTTIVariant {
public:
    __int64 data[2] = { 0 }; // Mimic your provided array

    CRTTIVariant() = default;

    template <typename T>
    CRTTIVariant(T* ptr) {
        data[1] = std::bit_cast<__int64>(ptr);
    }

    template <typename T>
    T* GetPointer() const {
        return std::bit_cast<T*>(data[1]);
    }
};

class __declspec(dllimport) IGame {
public:

    //this is the actuall struct, it's actually just empty in engine
    //prety much never used also I think, might just be cast to something like CResourceDataPack or smt IDGAF
    struct SRPackHandle {
    };

    __cdecl IGame(void);
    __cdecl IGame(class IGame const&);

    //static
    static bool InitializeOnlineServices(void*);
    static bool IsOnlineServicesInitialized(void);
    static void ShutdownOnlineServices(void);
    static class CRTTI const* __ptr64 GetNativeClass(void);

    static class ttl::string_base<char> GetDefaultLocaleID(void);
    static class ttl::string_base<char> GetDefaultSpeechID(class ttl::string_base<char> const&);
    static class ttl::string_base<char> GetFallbackLocaleID(void);
    static class ttl::string_base<char> GetFallbackSpeechID(void);
    static class ttl::string_base<char> GetSystemLocaleID(void);
    static class ttl::string_base<char> CheckForceLangParameter(class ttl::string_base<char>&);

    // Initialization, Resource Pack Loading, and Level Loading
    int Initialize(char*, int, struct HICON__*, struct HICON__*, unsigned long, unsigned long, class IProgressIndicator*);

    bool LoadPack(class ttl::string_base<char> const&, bool, bool, struct IGame::SRPackHandle**);
    void FreePack(class ttl::string_base<char> const&);
    bool IsAnyRPackLoaded(void);

    //Level
    class ILevel* __ptr64 GetActiveLevel(void);
    class ILevel* __ptr64 LoadModule(class ttl::string_base<char> const&, class IGSObject*, class IProgressIndicator*);
    class ILevel* __ptr64 LoadModuleEnd(struct SLoadModuleData*, bool);

    //CGame
    class CGame* __ptr64 ToCGame(void);
    class CGame const* __ptr64 ToCGame(void) const;


    //CRC Checks
    unsigned int GetMultiplayerFilesCrc(void) const;
    bool AreDataAuthenticatedToPlayMultiplayer(void) const;
    //Repl
    bool ReplInitialize(void);
    void ReplAddVerifyData(char const*, unsigned int, bool);
    void ReplDump(char const*) const;
    void ReplEnableReplicationIntervalChange(bool);
    void ReplGetConnectedTargets(class ttl::vector<unsigned short>&) const;
    unsigned int ReplGetConnectedTargetsCount(void) const;
    unsigned short ReplGetLocalId(void) const;
    unsigned int ReplGetNetworkId(unsigned short) const;
    unsigned short ReplGetTargetId(unsigned int) const;
    bool ReplIsConnectedTargetId(unsigned short) const;
    void ReplSetReplicationIntervalMultipliers(float, float, float, float);


    //Editor / Debug
    bool IsGameInEditor(void) const;
    bool IsGameInEditorRunning(void);

    void EnableDebugSocket(bool, class ttl::string_base<char> const*);
    bool IsGuiEditorMode(void);
    bool IsEditorGameMode(void);

    void AddEditorCriticalError(class ttl::string_base<char> const&);
    void AddEditorWarning(class ttl::string_base<char> const&);

    char const* __ptr64* __ptr64 GetCommandLineArgs(void);
    int GetCommandLineArgsCount(void);
    void DebugDisableHyperThreading(void);


    //SDL / Window
    void DoSdlLoop(void);
    void PollSdlEvents(void);
    void OnPaint(void);
    struct HWND__* __ptr64 GethWnd(void) const;

    //Screen
    int GetScreenHeight(void);
    int GetScreenWidth(void);
    float GetScaleToSafeAreaFactor(void) const;
    float GetCameraAspect(void) const;

    //Render
    bool IsBackgroundRender(void);
    bool IsBackgroundRenderBlocked(void);
    bool IsGameRenderingEnabled(void);
    void EnableGameRendering(bool);

    //Render Debug
    void SetRenderDebugVis(bool);

    //Font
    bool RegisterFontStyle(class ttl::string_base<char> const&, class ttl::string_base<char> const&, float, float);
    void SetDefaultFont(class ttl::string_base<char> const&);

    void RemoveFontStyle(class ttl::string_base<char> const&);
    void RemoveFontStyles(void);
    void RemoveFonts(void);
    bool IsFontStyle(class ttl::string_base<char> const&);
    bool LoadFontsScript(class ttl::string_base<char> const&, bool);
    bool LoadFontsStyleScript(class ttl::string_base<char> const&);

    //Server
    void GoDedicated(void);
    bool IsDedicatedServer(void);

    //Recording
    void EnableAVIRecording(class ttl::string_base<char> const&, float, bool);
    void DisableAVIRecording(void);
    void ChooseAVICodecAndExit(void);
    void StopAVIRecording(void);
    void RecordGameplayClip(class ttl::string_base<wchar_t>, class ttl::string_base<wchar_t>, float, float, float, class IRecorderClientCallback*);


    //Screenshot
    void TakeScreenshot(class ttl::string_base<char> const&);
    void TakeScreenshot(class ttl::string_base<char> const&, int, int);
    void TakeScreenshot(void);
    void EnableContinuousScreenshotRecording(class ttl::string_base<char> const&, float);
    void DisableContinuousScreenshotRecording(void);

    //Input
    void AcquireInput(bool);
    void StartInputPlaying(class ttl::string_base<char> const&);
    void StopInputPlaying(void);

    void StartInputRecording(class ttl::string_base<char> const&);
    void StopInputRecording(void);
    void EnableInputPlaying(class ttl::string_base<char> const&, float);
    void EnableInputRecording(class ttl::string_base<char> const&, float, class ttl::string_base<char> const&);

    //Timers / Time
    void TimersDefaultFrozen(bool);
    void TimersNextStep(float);
    void TimersStart(void);
    void TimersStop(void);
    void TimersUpdate(void);
    void TimersUpdateFromServer(float);
    void TimersUpdateSkip(void);

    float GetGameLastTime(void) const;
    float GetGameTimeDelta(void) const;
    float GetGameTime(void) const;

    void FreezeTimersOnLevels(void);
    void UnFreezeTimersOnLevels(void);
    void SaveLevelsTimersState(void);
    void RestoreLevelsTimersState(void);


    //Sound
    void StartSoundRecording(class ttl::string_base<char> const&);
    void StopSoundRecording(void);

    //Quit
    void CrashQuit(class ttl::string_base<char> const&);
    void ExitGame(void);



    //Too Lazy to sort
    void EnableDontDropConnetion(bool);
    void EnableFramePipelining(bool);

    int GetCodePage(void);
    class ICountersSystem const* __ptr64 GetCountersSystem(void) const;

    class ttl::string_base<char> GetLocaleID(void);
    char const* __ptr64 GetRootDirectory(void) const;
    bool IsRenderUiInEditor(void);
    bool IsUseScaleToSafeArea(void) const;
    bool IsWPFInteropMode(void);
    struct SLoadModuleData* __ptr64 LoadModuleBegin(class ttl::string_base<char> const&, class IGSObject*, class IProgressIndicator*);
    bool LoadModuleFinished(struct SLoadModuleData*);
    struct SGameAddressEos const LobbyGetClientAddress(unsigned int);
    struct SPlayerIdEos LobbyGetClientPlayerId(unsigned int);
    class ttl::string_base<wchar_t> const LobbyGetClientProfileName(unsigned int);
    unsigned int LobbyGetMasterNetId(void);
    bool LobbyIsNetworkIdValid(unsigned int);
    void MsgSend(unsigned int, unsigned char const*, unsigned int);
    void PauseContinuousScreenshotRecording(bool);
    class ttl::string_base<char> const ReadAdditionalTextFromInputFile(class ttl::string_base<char> const&);

    void ResetPerformanceTest(void);

    void SetDefaultModuleStartTime(float);
    void SetGameName(class ttl::string_base<char> const&);
    void SetGameNameExplicit(class ttl::string_base<wchar_t> const&);
    void SetLoadingPercentage(float, float);
    bool SetLocaleID(char const*) const;
    bool SetRootDirectory(char const*);
    void SetSafeMode(bool);
    void SetScreenshotParams(int, int);
    bool SetSpeechID(char const*, bool) const;
    void SetSpeedUpInternalOnLevels(float);
    void SetUseScaleToSafeArea(bool, float);
    void SetXboxOneMatchHopper(int);

    void WaitForPipelineThreads(void);

    //haven't bothered fixing these exported funcs
    //void CallOnFrameEnd(class CRTTIVoidFunctor<class IGSObject> const&);
    //class ChromeSpy::IDataCollector* __ptr64 GetDataCollector(void) const;
    //enum EPadDevice::TYPE GetForceShowControllerId(void) const;
    //float GetScreenResolutionScale(enum EScreenResolutionScale::TYPE);
    //void RemoveFromFrameEnd(class CRTTIVoidFunctor<class IGSObject> const&);
    //void RemoveFromFrameEnd(class IGSObject*);
    //enum IGame::StreamStatus StreamIsFinished(struct IGame::SRPackStreamHandle*, bool);
    //struct IGame::SRPackStreamHandle* __ptr64 StreamLoadMesh(struct IGame::SRPackHandle*, class ttl::string_base<char> const&, int);
    //void StreamUnloadMesh(struct IGame::SRPackStreamHandle*);


    //Vtable funcs, some of the "stripped" functions are prob just not exported and are set on runtime or smt idk
    virtual void __cdecl SetEngineObject(class CGSObject* __ptr64);
    virtual ~IGame(void);

    //stripped functions
    virtual void Stripped();//IPhBody::~IPhBody
    virtual void Stripped1();//IPhBody::~IPhBody
    virtual void Stripped2();//IPhBody::~IPhBody
    virtual void Stripped3();//IPhBody::~IPhBody
    virtual void Stripped4();//IPhBody::~IPhBody
    virtual void Stripped5();//IPhBody::~IPhBody
    virtual void Stripped6();//IPhBody::~IPhBody
    virtual void Stripped7();//IPhBody::~IPhBody
    virtual void Stripped8();//IPhBody::~IPhBody
    virtual void Stripped9();//IPhBody::~IPhBody
    virtual void Stripped10();//IPhBody::~IPhBody
    virtual void Stripped11();//IPhBody::~IPhBody

    virtual void OnContentChanged(void);

    virtual void Stripped12();//IPhBody::~IPhBody
    virtual void Stripped13();//IPhBody::~IPhBody
    virtual void Stripped14();//IPhBody::~IPhBody
    virtual void Stripped15();//IPhBody::~IPhBody
    virtual void Stripped16();//IPhBody::~IPhBody
    virtual void Stripped17();//IPhBody::~IPhBody
    virtual void Stripped18();//IPhBody::~IPhBody
    virtual void Stripped19();//IPhBody::~IPhBody
    virtual void Stripped20();//IPhBody::~IPhBody
    virtual void Stripped21();//IPhBody::~IPhBody
    virtual void Stripped22();//IPhBody::~IPhBody
    virtual void Stripped23();//IPhBody::~IPhBody
    virtual void Stripped24();//IPhBody::~IPhBody
    virtual void Stripped25();//IPhBody::~IPhBody
    virtual void Stripped26();//IPhBody::~IPhBody
    virtual void Stripped27();//IPhBody::~IPhBody
    virtual void Stripped28();//IPhBody::~IPhBody
    virtual void Stripped29();//IPhBody::~IPhBody
    virtual void Stripped30();//IPhBody::~IPhBody
    virtual bool Stripped31();
    virtual void Stripped32();//IPhBody::~IPhBody
    virtual void Stripped33();//IPhBody::~IPhBody
    virtual void Stripped34();//IPhBody::~IPhBody
    virtual void Stripped35();//IPhBody::~IPhBody
    virtual void Stripped36();//IPhBody::~IPhBody
    virtual void Stripped37();//IPhBody::~IPhBody
    virtual void Stripped38();//IPhBody::~IPhBody
    virtual void Stripped39();//IPhBody::~IPhBody
    virtual void Stripped40();//IPhBody::~IPhBody
    virtual void Stripped41();//IPhBody::~IPhBody
    virtual void Stripped42();//IPhBody::~IPhBody
    virtual void Stripped43();//IPhBody::~IPhBody
    virtual void Stripped44();//IPhBody::~IPhBody
    virtual void Stripped45();//IPhBody::~IPhBody

    virtual void SetProperty(class ttl::string_base<char> const&, class CRTTIVariant const&);
    virtual class CVarSet* __ptr64 GetVarSet(void);
    virtual int StrippedENUMORINT();
    virtual char const* __ptr64 GetGameDirectoryName(void) const;
    virtual class ttl::string_base<char> GetGameCustomText(void);
    virtual class ILevel* __ptr64 GetLevelEditor(void);
    virtual char const* __ptr64 GetVoiceLocaleID(void);

    virtual int Stripped46();
    virtual void Stripped47();//IPhBody::~IPhBody
    virtual void Stripped48();//IPhBody::~IPhBody
    virtual void Stripped49();//IPhBody::~IPhBody
    virtual void Stripped50();//IPhBody::~IPhBody
    virtual void Stripped51();//IPhBody::~IPhBody
    virtual bool Stripped52();
    virtual bool Stripped53();
    virtual void Stripped54();//IPhBody::~IPhBody
    virtual void Stripped55();//IPhBody::~IPhBody
    virtual void Stripped56();//IPhBody::~IPhBody

    virtual int Main(void);
    virtual void NonInteractiveSequenceBegin(void);
    virtual void NonInteractiveSequenceEnd(void);
    virtual void RestartTimeoutTimer(void);

    virtual bool Stripped57();
    virtual void Stripped58();//IPhBody::~IPhBody
    virtual bool Stripped59();
    virtual void Stripped60();//IPhBody::~IPhBody
    virtual void Stripped61();//IPhBody::~IPhBody
    virtual void Stripped62();//IPhBody::~IPhBody
    virtual void Stripped63();//IPhBody::~IPhBody
    virtual void Stripped64();//IPhBody::~IPhBody
    virtual void Stripped65();//IPhBody::~IPhBody
    virtual void Stripped66();//IPhBody::~IPhBody
    virtual void Stripped67();//IPhBody::~IPhBody
    virtual void Stripped68();//IPhBody::~IPhBody
    virtual void Stripped69();//IPhBody::~IPhBody
    virtual void Stripped70();//IPhBody::~IPhBody
    virtual void Stripped71();//IPhBody::~IPhBody
    virtual void Stripped72();//IPhBody::~IPhBody
    virtual void Stripped73();//IPhBody::~IPhBody
    virtual void Stripped74();//IPhBody::~IPhBody
    virtual void Stripped75();//IPhBody::~IPhBody
    virtual void Stripped76();//IPhBody::~IPhBody
    virtual void Stripped77();//IPhBody::~IPhBody
    virtual void Stripped78();//IPhBody::~IPhBody
    virtual void Stripped79();//IPhBody::~IPhBody
    virtual void Stripped80();//IPhBody::~IPhBody
    virtual void Stripped81();//IPhBody::~IPhBody
    virtual void Stripped82();//IPhBody::~IPhBody
    virtual void Stripped83();//IPhBody::~IPhBody
    virtual void Stripped84();//IPhBody::~IPhBody
    virtual void Stripped85();//IPhBody::~IPhBody
    virtual void Stripped86();//IPhBody::~IPhBody
    virtual void Stripped87();//IPhBody::~IPhBody
    virtual void Stripped88();//IPhBody::~IPhBody
    
    virtual class ttl::string_base<char> GetProperFont(class ttl::string_base<char> const&);
    virtual float GetProperFontScale(class ttl::string_base<char> const&, float, bool);
    virtual class ttl::string_base<char> GetDefaultFont(void);
    virtual void Stripped89();//IPhBody::~IPhBody
    virtual void Stripped90();//IPhBody::~IPhBody
    virtual void Stripped91();//IPhBody::~IPhBody
    virtual class ttl::string_base<char> GetGamescriptUIVersion(void);
    virtual int Stripped92();
    virtual class ISaveManager* __ptr64 GetSaveManager(void);
    virtual bool Stripped93();
    virtual void Stripped94();//IPhBody::~IPhBody
    virtual class ITagSystem& GetTagSystem(void);
    virtual bool Stripped95();
    virtual int Stripped96();
    virtual void Stripped97();//IPhBody::~IPhBody
    virtual void Stripped98();//IPhBody::~IPhBody
    virtual void Stripped99();//IPhBody::~IPhBody
    virtual void Stripped100();//IPhBody::~IPhBody
    virtual void Stripped101();//IPhBody::~IPhBody
    virtual void Stripped102();//IPhBody::~IPhBody
    virtual int Stripped103();
    virtual int Stripped104();
    virtual int Stripped105();
    virtual void Stripped106();//IPhBody::~IPhBody
    virtual int Stripped107();
    virtual int Stripped108();
    virtual void Stripped109();//IPhBody::~IPhBody
    virtual void Stripped110();//IPhBody::~IPhBody

    virtual class ttl::string_base<char> GetTitleId(void) const;
    virtual void SetTitleId(class ttl::string_base<char> const&);

    virtual bool Stripped111();
    virtual void Stripped112();//IPhBody::~IPhBody
    virtual void Stripped113();//IPhBody::~IPhBody
    virtual void Stripped114();//IPhBody::~IPhBody
    virtual void Stripped115();//IPhBody::~IPhBody
    virtual bool Stripped116();
    virtual bool Stripped117();
    virtual bool Stripped118();
    virtual void Stripped119();//IPhBody::~IPhBody

    virtual bool VideoSettingsIsFullScreen(void);
    virtual void SetFocusOnWindow(void);
    virtual void SetVisibilityFactors(float, float);
    virtual void GetVisibilityFactors(float&, float&);
    virtual unsigned int GetFrameCounter(void) const;

    virtual void Stripped120();//IPhBody::~IPhBody
    virtual void Stripped121();//IPhBody::~IPhBody
    virtual void Stripped122();//IPhBody::~IPhBody
    virtual void Stripped123();//IPhBody::~IPhBody
    virtual void Stripped124();//IPhBody::~IPhBody
    virtual bool Stripped125();
    virtual void Stripped126();//IPhBody::~IPhBody
    virtual void Stripped127();//IPhBody::~IPhBody
    virtual void Stripped128();//IPhBody::~IPhBody

    virtual class ttl::string_base<char> GetConfigurationName(void) const;

    virtual bool Stripped129();
    virtual void Stripped130();//IPhBody::~IPhBody
    virtual void Stripped131();//IPhBody::~IPhBody
    virtual void Stripped132();//IPhBody::~IPhBody
    virtual void Stripped133();//IPhBody::~IPhBody
    virtual void Stripped134();//IPhBody::~IPhBody

    virtual bool IsLowViolence(void) const;
    virtual class ttl::string_base<char> GetGameCustomText_AGAIN(void); //again for some reason, same exact func

    virtual bool Stripped135();

    virtual class ttl::string_base<char> const& GetTitleStorageFullGameProductId(class ttl::string_base<char> const&) const;

    virtual int Stripped136();
    virtual bool Stripped137();

    virtual class ttl::string_base<char> const& GetTitleStorageFullGameProductId_FUCKINGAGAINLIKEIMADAMWARLOCK(class ttl::string_base<char> const&) const; //again

    //idk DAT_1808d1390
    

    /*
    virtual bool BlockRpackOperationsByPendingPackUiOperations(void) const;
    virtual bool CanUseExternalSpeaker(unsigned int, bool) const;
    virtual bool IsAnyCommonRpackToLoad(void);
    //virtual bool IsDlcOwned(enum EGameDlc::TYPE) const;
    //virtual bool IsDlcPresent(enum EGameDlc::TYPE) const;
    //virtual bool IsDlcProvidingData(enum EGameDlc::TYPE, int) const;
    virtual bool IsNetPlayerPlaying(int);
    virtual bool IsPendingActiveProfileHandlingEnabled(void);
    virtual bool IsRestUsingLocalFiles(void) const;
    virtual bool IsSystemUIShowing(void);
    virtual bool IsTitleStorageStoreCategory(class ttl::string_base<char> const&) const;
    virtual void CompileAIData(void) const;
    virtual void FlushVM(void);
    //virtual void FillStatusList(class ttl::vector<struct SCounterLevelInfo>&) const;
    //virtual void GatherGameResources(class ttl::list<class ttl::string_base<char>, class ttl::allocator>&, enum EGatherGameResourcesMode::TYPE);
    virtual class ICampaignManager* __ptr64 GetCampaignManagerInterface(void) const;
    virtual void ForceProgressDialogTimeoutReset(void);
    virtual void ForceReloadTexts(void);
    virtual class ttl::string_base<char> GetDefaultFont(void);
    virtual class IDialogManager* __ptr64 GetDialogManager(void) const;
    //virtual class Chatters::IChatterPlayer* __ptr64 GetEditorChatterPlayer(void) const;
    virtual int GetGuiSoundBus(void) const;
    virtual class IMapPortalsManager* __ptr64 GetIMapPortalsManager(void) const;
    virtual class IQuestManager* __ptr64 GetIQuestManager(void) const;
    virtual class ttl::string_base<char> GetInvokeScriptPathEditor(void);
    virtual class ILiveSpaData* __ptr64 GetLiveSpaData(void);
    //virtual class Mount::IMountHelper* __ptr64 GetMountHelper(void);
    //virtual void GetRestAuthData(struct RestClient::SRestAuthData&) const;
    virtual void GetSaveDataUtilityContext(struct SSaveDataUtilityContext&);
    virtual int GetTitleStorageServiceLabel(class ttl::string_base<char> const&) const;
    virtual class ttl::string_base<char> const& GetTitleStorageStoreCategory(class ttl::string_base<char> const&) const;
    virtual bool IsBackButtonPairedWithB(void) const;
    virtual bool IsStartButtonPairedWithA(void) const;
    virtual void LobbyCallback_OnBecomeMaster(void);
    virtual bool Lobby_IsGameVisibleByScannerThread(void);
    virtual void Lobby_OnCreateInternetSessionFailed(void);
    virtual void Lobby_OnFailedSignInForInviteAsync(bool);
    virtual void Lobby_OnInviteAccepted(struct SGameSearchResult const&, bool, struct SPlayerIdEos, unsigned long);
    virtual void Lobby_OnInviteReceived(struct SGameSearchResult const&, bool, struct SPlayerIdEos, unsigned long);
    //virtual void Lobby_OnInviteRejected(struct SGameSearchResult const&, enum EInviteRejectReason::TYPE);
    virtual void Lobby_OnSessionInviteReceived(class ttl::string_base<char> const&);
    //virtual enum EDisconnectReason::TYPE Lobby_IsGameJoinableThread(enum ETeam::TYPE);
    virtual void NotifyXboxOffers(class ttl::vector<struct SXboxOfferReport> const&);
    virtual void OnAchievementWritten(unsigned long);
    virtual void OnAchievementsReloaded(void);
    virtual void OnActivePlayerSigningOut(void);
    virtual void OnBlockInputProcessing(void);
    virtual void OnBubbleEnter(class ttl::string_base<char> const&);
    virtual void OnBubbleLeave(class ttl::string_base<char> const&);
    virtual void OnChunkInstalled(class ttl::string_base<char> const&);
    virtual void OnContentUpdateBegin(void);
    virtual void OnContentUpdateEnd(void);
    virtual void OnCreatePLS(void);
    virtual void OnDeleteSaveGameUtilityFinished(void);
    virtual bool OnDemoTimeoutPassed(void);
    virtual void OnEntitlementsChanged(void);
    virtual void OnFinishedLoadingLevelEditor(class ttl::string_base<char> const&);
    virtual void OnGameResuming(void);
    virtual void OnGameSuspending(void);
    virtual void OnInitialize(void);
    virtual void OnInitializePLS(void);
    virtual void OnLiveConnectionChanged(long);
    virtual void OnLoadCommonRpacks(void);
    virtual void OnLobbyAntiCheatStatusChanged(void);
    virtual void OnLobbyBecameMaster(void);
    virtual void OnLobbyErrorRemovedFromSystem(int);
    virtual void OnLobbyFullVersionEnabled(void);
    virtual void OnLobbyGamePresenceOffline(void);
    virtual void OnLobbyInactiveUserInvited(struct SPlayerIdEos const&);
    //virtual void OnLobbyInviteAcceptingFailure(enum EDisconnectReason::TYPE);
    virtual void OnLobbyJoined(void);
    virtual void OnLobbyLeft(class LobbyDisconnectError);
    virtual void OnLobbyNatChanged(void);
    virtual void OnLobbyPartyGameCreated(void);
    //virtual void OnLobbyPartyGameCreationFailure(enum EDisconnectReason::TYPE);
    virtual void OnLobbyPartyGameJoined(struct SGameSearchResult const&);
    //virtual void OnLobbyPartyGameJoiningFailure(enum EDisconnectReason::TYPE);
    virtual void OnLobbyPartyGameJoiningNotAvailable(void);
    virtual void OnLobbyPartyGameJoiningReady(struct SGameSearchResult const&);
    //virtual void OnLobbyRemotePeerFailedJoining(unsigned int, enum EDisconnectReason::TYPE);
    virtual void OnLobbyRemotePeerJoined(unsigned int);
    //virtual void OnLobbyRemotePeerLeft(unsigned int, enum EDisconnectReason::TYPE);
    //virtual void OnLobbyRemotePeerStartedJoining(unsigned int, enum ETeam::TYPE);
    //virtual void OnLobbySessionCreateFailure(enum ELobbyMode::TYPE, enum EDisconnectReason::TYPE);
    //virtual void OnLobbySessionCreateSuccess(enum ELobbyMode::TYPE);
    virtual void OnLobbySessionEnd(class ttl::string_base<wchar_t> const&);
    virtual void OnLobbySessionEnd(void);
    virtual void OnLobbySessionStart(class ttl::string_base<wchar_t> const&);
    virtual void OnMovieEnded(void);
    virtual void OnMovieStarted(void);
    virtual void OnMsgReceived(unsigned int, unsigned char const*, unsigned int);
    virtual void OnNetworkCablePlugged(void);
    virtual void OnNetworkCableUnplugged(void);
    virtual void OnNetworkGameDestroyed(void);
    virtual void OnPostDestroyLevelInGIEMode(char const*);
    virtual void OnPostLoadLevelInGIEMode(char const*);
    virtual void OnPostResetRenderer(void);
    virtual void OnPreDestroyLevelInGIEMode(char const*);
    virtual void OnPreInitialize(char const**, int);
    virtual void OnPreLoadLevelInGIEMode(char const*);
    virtual void OnProfileCorrupted(void);
    virtual void OnProfileDataRemotelyChanged(void);
    virtual void OnProfileLoaded(bool);
    virtual void OnProfileNotOwner(void);
    virtual void OnProfileUnloaded(void);
    virtual void OnReadErrorException(void);
    virtual void OnReloadAnimationsScr(void);
    virtual void OnRendererInitialized(void);
    virtual void OnReplLocalIdChanged(unsigned short, unsigned short);
    virtual void OnReplTargetJoined(unsigned short, unsigned int);
    virtual void OnReplTargetLeft(unsigned short, unsigned int);
    //virtual void OnShowKeyboardUIXBox(struct mpl::_MPLOVERLAPPED**, class IConsolesKeyboardCallback*, wchar_t**);
    virtual void OnSignInChanged(void);
    virtual void OnSignInResult(int);
    virtual void OnStorageDeviceChanged(void);
    virtual void OnStorageDeviceSelectionCompleted(bool);
    virtual void OnStorageImportAvailabilityCheckCompleted(bool);
    virtual void OnStorageImportCompleted(bool, int);
    virtual void OnSwitchActiveUserRequest(void);
    virtual void OnSystemUIClosed(void);
    virtual void OnSystemUIOpened(void);
    //virtual void OnTitleStorageSettingLoaded(class parser::func_iterator&);
    virtual void OnUnblockInputProcessing(void);
    virtual void OnValidateSettings(void);
    virtual void OnWindowActivate(bool);
    virtual void OnWriteProfileCancelAsync(int);
    virtual void OnWriteProfileError(int, bool);
    virtual void OnWriteProfileStart(int);
    virtual void OnWriteProfileStartAsync(int);
    virtual void OnWriteProfileStopAsync(int, bool, bool);
    virtual void OnWriteProfileSuccess(int);
    //virtual void PopulateRestUserData(class ttl::map<class ttl::string_base<char>, class ttl::string_base<char>, struct ttl::less<class ttl::string_base<char> >, class ttl::allocator>&) const;
    //virtual void QueryChatterPlayerTexts(class ttl::map<class ttl::string_base<char>, class ttl::vectorm<30, class ttl::string_base<char> >, struct ttl::less<class ttl::string_base<char> >, class ttl::allocator>&) const;
    virtual void QueryTextResourcesUsed(class ILocalizationManager&) const;
    virtual void RegisterEditorRenderOption(void);
    virtual void SetEngineObject(class CGSObject*);
    virtual void SetGameDirectories(char const*, char const*, char const*);
    virtual void SetPS3TitleId(char*, int);
    virtual void SetRestEnabled(bool);
    //virtual void SetTrialStatusFromServer(enum ETrialStatus::TYPE);
    virtual void SetVMWorkSize(unsigned int);
    virtual void SetXbox360TitleId(int);
    virtual void ShowNetworkWaitScreen(bool);
    */
};