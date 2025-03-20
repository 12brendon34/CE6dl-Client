#pragma once
#include "pch.h"
#include "../TTL.h"
#include "IGame.h"

struct mtx34 {
    float m[3][4];
};

class CGame {
    public:
        IGame* m_IGame;

        virtual void FUN_180250540();
        virtual ~CGame();
        virtual void FUN_18012c960();
        virtual void GetNativeClass();
        virtual void* IPhBody();
        virtual void* IPhBody_1();
        virtual void GetEngineRTTIObject();
        virtual void GetEngineRTTIObject_1();
        virtual void GetPrivateObjects();
        virtual void DestroyPrivateObjects();
        virtual void* IPhBody_2();
        virtual void GetAllObjects();
        virtual void GetAllObjects_1();
        virtual void AreFlagsSet();
        virtual void* IPhBody_3();
        virtual void GetRTTIObjectName();
        virtual void FUN_180036880();
        virtual void FUN_1800368a0();
        virtual void FUN_180250c10();
        virtual void CallVoidMethod();
        virtual void LoadFields();
        virtual void SaveFields();
        virtual void ToBufferReplicated();
        virtual void FromBufferReplicated();
        virtual void GetBufferReplicatedDataSize();
        virtual void GetFieldBoolEditor();
        virtual void GetFieldBoolEditor_1();
        virtual void GetFieldBoolEditor_2();
        virtual void GetFieldBoolEditor_3();
        virtual void GetFieldBoolEditor_4();
        virtual void GetFieldEnumEditor();
        virtual void GetFieldBoolEditor_5();
        virtual void GetFieldBoolEditor_6();
        virtual void GetFieldBoolEditor_7();
        virtual void GetFieldBoolEditor_8();
        virtual void GetFieldBoolEditor_9();
        virtual void GetFieldBoolEditor_10();
        virtual void GetFieldStringEditor();
        virtual void GetFieldBoolEditor_11();
        virtual void GetFieldBoolEditor_12();
        virtual void GetFieldBoolEditor_13();
        virtual void GetFieldBoolEditor_14();
        virtual void GetFieldBoolEditor_15();
        virtual void GetFieldStringEditor_1();
        virtual void SetFieldBoolEditor();
        virtual void SetFieldBoolEditor_1();
        virtual void SetFieldShortEditor();
        virtual void SetFieldShortEditor_1();
        virtual void SetFieldIntEditor();
        virtual void SetFieldEnumEditor();
        virtual void SetFieldIntEditor_2();
        virtual void SetFieldInt64Editor();
        virtual void SetFieldInt64Editor_2();
        virtual void SetFieldFloatEditor();
        virtual void SetFieldDoubleEditor();
        virtual void SetFieldBoolEditor_2();
        virtual void SetFieldStringEditor();
        virtual void SetFieldMtx34Editor();
        virtual void SetFieldMtx34Editor_2();
        virtual void SetFieldMtx34Editor_3();
        virtual void SetFieldMtx34Editor_4();
        virtual void SetFieldMtx34Editor_5();
        virtual void SetFieldStringEditor_2();
        virtual void CanSetFieldEditor();
        virtual void FUN_180250a90();
        virtual void FUN_180250aa0();
        virtual void FUN_180250ab0();
        virtual void FUN_180250ac0();
        virtual void FUN_180250ad0();
        virtual void FUN_180250ae0();
        virtual void LAB_180250af0();
        virtual void LAB_180250b00();
        virtual void LAB_180250b10();
        virtual void LAB_180250b20();
        virtual void LAB_180250b30();
        virtual void LAB_180250b40();
        virtual void LAB_180250b50();
        virtual void LAB_180250b60();
        virtual void LAB_180250b70();
        virtual void LAB_180250b80();
        virtual void LAB_180250b90();
        virtual void LAB_180250ba0();
        virtual void LAB_180250bb0();
        virtual void LAB_180250bc0();
        virtual void LAB_180250bd0();
        virtual void LAB_180250be0();
        virtual ttl::string_base<char> ExecuteEditorCommand(ttl::string_base<char>, ttl::string_base<char>, ttl::string_base<char>);
        virtual void FUN_180036660();
        virtual void CopyFields();
        virtual void CopyPointerFields();
        virtual void ExchangePointerFields();
        virtual void LAB_18024fa40();
        virtual void LAB_18024fa90();
        virtual void LAB_18024fb20();
        virtual void FUN_1802507e0();
        virtual void LAB_18024ebd0();
        virtual void LAB_18024ec40();
        virtual void LAB_180250bf0();
        virtual void LAB_1800367f0();
        virtual void FUN_180036810();
        virtual void OnFieldChanged2();
        virtual void LAB_18024e9d0();
        virtual void LAB_18024e950();
        virtual void CanGoToSimpleObjectsEditor();
        virtual void CanGoToSimpleObjectsEditor_1();
        virtual void IPhBody_4();
        virtual void Query();
        virtual void SaveObjectHierarchy();
        virtual void FUN_18013a110();
        virtual void FUN_180036590();
        virtual void LAB_1800365f0();
        virtual void IPhBody_5();
        virtual void FUN_180250150();
        virtual void LAB_18024ec50();
        virtual void FUN_18003b070();
        virtual void FUN_180231b50();
        virtual void FUN_18003b240();
        virtual void FUN_18024f650();
        virtual void FUN_18003b3a0();
        virtual void FUN_180226160();
        virtual void LAB_18024e4d0();
        virtual void IPhBody_6();
        virtual void LAB_18024ec70();
        virtual void FUN_18024ec80();
        virtual void FUN_18024edb0();
        virtual void FUN_18022c950();
        virtual void FUN_18024e4e0();
        virtual void FUN_18024e550();
        virtual void FUN_18024e6d0();
        virtual void FUN_18022c8f0();
        virtual void LAB_18024e070();
        virtual void FUN_18024e1c0();
        virtual void FUN_18024f830();
        virtual void FUN_18024f7a0();
        virtual void FUN_18024e090();
        virtual void FUN_18024fd40();
        virtual void LAB_18024fdf0();
        virtual void FUN_18024fdc0();
        virtual void LAB_18024ff10();
        virtual void LAB_18024fe90();
        virtual void LAB_18024f9f0();
        virtual void FUN_180250c30();
        virtual void FUN_18024e3c0();
        virtual void FUN_18024f8b0();
        virtual void FUN_18014b390();
        virtual void FUN_18024ff80();
        virtual void LAB_180250080();
        virtual void LAB_1802500d0();
        virtual void GoDedicated(); // I think
        virtual void LAB_18022e660();
        virtual void LAB_18022e680();
        virtual void LAB_18024fa10();
        virtual void LAB_18024fa20();
        virtual void LAB_18022e670();
        virtual void LAB_18024fa30();
        virtual void FUN_1802501d0();
        virtual void FUN_180226b30();
        virtual void FUN_18022e3e0();
        virtual void FUN_180230f70();
        virtual void LAB_180230f50();
        virtual void FUN_180229220();
        virtual void Initialize();
        virtual void LAB_18022c7e0();
        virtual void LAB_1802368f0();
        virtual void LAB_180235230();
        virtual void LAB_180228fc0();
        virtual void LAB_180228cb0();
        virtual void FUN_180230eb0();
        virtual void LAB_1802353a0();
        virtual void LAB_180235420();
        virtual void FUN_1802353f0();
        virtual void FUN_180235470();
        virtual void LAB_180232e50();
        virtual void LAB_180232f70();
        virtual void LAB_180232f30();
        virtual void LAB_180234070();
        virtual void FUN_180234090();
        virtual void LAB_180234110();
        virtual void FUN_180234130();
        virtual void FUN_1802341b0();
        virtual void LAB_180234200();
        virtual void FUN_180236860();
        virtual void FUN_180235ab0();
        virtual void LAB_180235bf0();
        virtual void LAB_180236850();
        virtual void LAB_180234a60();
        virtual void FUN_180234ad0();
        virtual void LAB_180234b90();
        virtual void GetVisualizationSizeM();
        virtual void DAT_1808e9fb0();
};

/*
class CGame// : public IGame
{
public:
    virtual void* FUN_180250540_2(LONGLONG* param_2, byte param_3);
    virtual uint64_t FUN_180226a10(LONGLONG param_2, uint64_t param_3, uint64_t param_4);

    virtual void* FUN_18012c960_2(LONGLONG param_1);
    virtual class CRTTI* GetNativeClass();
    //stripped
    virtual void* IPhBody();
    virtual void* IPhBody_1();

    virtual class CRTTIObject* GetEngineRTTIObject();
    virtual class CRTTIObject* GetEngineRTTIObject_1();
    virtual void DummyBcIDontWanaImplement();//virtual void GetPrivateObjects(class list<class_IGSObject* ___ptr64, class_ttl::allocator>* param_1, bool param_2, bool param_3);
    virtual void DestroyPrivateObjects();

    //stripped
    virtual void* IPhBody_2();

    virtual void DummyBcIDontWanaImplement_1();//virtual void GetAllObjects(class vector<class_IGSObject* ___ptr64>* param_1, bool param_2) {}
    virtual void DummyBcIDontWanaImplement_2();//virtual void GetAllObjects(class set<class_CRTTIObject* ___ptr64, struct_ttl::less<class_CRTTIObject* ___ptr64>, class_ttl::allocator>* param_1, bool param_2);

    //stripped
    virtual bool AreFlagsSet(int param_1);
    virtual void IPhBody_3();
    virtual char* GetRTTIObjectName();

    virtual void FUN_180036880(LONGLONG param_1);
    virtual ULONGLONG FUN_1800368a0(LONGLONG param_1);
    virtual void FUN_180250c10(LONGLONG param_1);

    virtual void CallVoidMethod(char* param_1);
    virtual void LoadFields(class ifile* param_1, class IPtrResolver* param_2, bool param_3);
    virtual void SaveFields(class ifile* param_1, int param_2);
    virtual int ToBufferReplicated(char* param_1, int param_2);
    virtual int FromBufferReplicated(char* param_1, int param_2);
    virtual int GetBufferReplicatedDataSize();

    //stripped
    virtual class CRTTIFieldBool* GetFieldBoolEditor(char* param_1, bool* param_2);
    virtual class CRTTIFieldBool* GetFieldBoolEditor_1(char* param_1, bool* param_2);
    virtual class CRTTIFieldBool* GetFieldBoolEditor_2(char* param_1, bool* param_2);
    virtual class CRTTIFieldBool* GetFieldBoolEditor_3(char* param_1, bool* param_2);
    virtual class CRTTIFieldBool* GetFieldBoolEditor_4(char* param_1, bool* param_2);
    virtual class CRTTIFieldEnum* GetFieldEnumEditor(char* param_1, int* param_2);
    virtual class CRTTIFieldBool* GetFieldBoolEditor_5(char* param_1, bool* param_2);
    virtual class CRTTIFieldBool* GetFieldBoolEditor_6(char* param_1, bool* param_2);
    virtual class CRTTIFieldBool* GetFieldBoolEditor_7(char* param_1, bool* param_2);
    virtual class CRTTIFieldBool* GetFieldBoolEditor_8(char* param_1, bool* param_2);
    virtual class CRTTIFieldBool* GetFieldBoolEditor_9(char* param_1, bool* param_2);
    virtual class CRTTIFieldBool* GetFieldBoolEditor_10(char* param_1, bool* param_2);
    virtual class CRTTIFieldString* GetFieldStringEditor(char* param_1, ttl::string_base<char>* param_2);
    virtual class CRTTIFieldBool* GetFieldBoolEditor_11(char* param_1, bool* param_2);
    virtual class CRTTIFieldBool* GetFieldBoolEditor_12(char* param_1, bool* param_2);
    virtual class CRTTIFieldBool* GetFieldBoolEditor_13(char* param_1, bool* param_2);
    virtual class CRTTIFieldBool* GetFieldBoolEditor_14(char* param_1, bool* param_2);
    virtual class CRTTIFieldBool* GetFieldBoolEditor_15(char* param_1, bool* param_2);
    virtual class CRTTIFieldString* GetFieldStringEditor_1(char* param_1, ttl::string_base<char>* param_2);
    virtual class CRTTIFieldBool* SetFieldBoolEditor(char* param_1, bool param_2);
    virtual class CRTTIFieldBool* SetFieldBoolEditor_1(char* param_1, bool param_2);
    virtual class CRTTIFieldShort* SetFieldShortEditor(char* param_1, short param_2);
    virtual class CRTTIFieldShort* SetFieldShortEditor_1(char* param_1, short param_2);
    virtual class CRTTIFieldInt* SetFieldIntEditor(char* param_1, int param_2);
    virtual class CRTTIFieldEnum* SetFieldEnumEditor(char* param_1, int param_2);
    virtual class CRTTIFieldInt* SetFieldIntEditor_1(char* param_1, int param_2);
    virtual class CRTTIFieldInt64* SetFieldInt64Editor(char* param_1, __int64 param_2);
    virtual class CRTTIFieldInt64* SetFieldInt64Editor_1(char* param_1, __int64 param_2);
    virtual class CRTTIFieldFloat* SetFieldFloatEditor(char* param_1, float param_2);
    virtual class CRTTIFieldDouble* SetFieldDoubleEditor(char* param_1, double param_2);
    virtual class CRTTIFieldBool* SetFieldBoolEditor_2(char* param_1, bool param_2);
    virtual class CRTTIFieldString* SetFieldStringEditor(char* param_1, ttl::string_base<char>* param_2);
    virtual class CRTTIFieldMtx34* SetFieldMtx34Editor(char* param_1, mtx34* param_2);
    virtual class CRTTIFieldMtx34* SetFieldMtx34Editor_1(char* param_1, mtx34* param_2);
    virtual class CRTTIFieldMtx34* SetFieldMtx34Editor_2(char* param_1, mtx34* param_2);
    virtual class CRTTIFieldMtx34* SetFieldMtx34Editor_3(char* param_1, mtx34* param_2);
    virtual class CRTTIFieldMtx34* SetFieldMtx34Editor_4(char* param_1, mtx34* param_2);
    virtual class CRTTIFieldString* SetFieldStringEditor_1(char* param_1, ttl::string_base<char>* param_2);
    virtual bool CanSetFieldEditor(char* param_1, char* param_2, ttl::string_base<char>* param_3) {}

    //these all do the same thing ffs
    void FUN_180250a90(LONGLONG param_1);
    void FUN_180250aa0(LONGLONG param_1);
    void FUN_180250ab0(LONGLONG param_1);
    void FUN_180250ac0(LONGLONG param_1);
    void FUN_180250ad0(LONGLONG param_1);
    void FUN_180250ae0(LONGLONG param_1);
    void FUN_180250af0(LONGLONG param_1);
    void FUN_180250b00(LONGLONG param_1);
    void FUN_180250b10(LONGLONG param_1);
    void FUN_180250b20(LONGLONG param_1);
    void FUN_180250b30(LONGLONG param_1);
    void FUN_180250b40(LONGLONG param_1);
    void FUN_180250b50(LONGLONG param_1);
    void FUN_180250b60(LONGLONG param_1);
    void FUN_180250b70(LONGLONG param_1);
    void FUN_180250b80(LONGLONG param_1);
    void FUN_180250b90(LONGLONG param_1);
    void FUN_180250ba0(LONGLONG param_1);
    void FUN_180250bb0(LONGLONG param_1);
    void FUN_180250bc0(LONGLONG param_1);
    void FUN_180250bd0(LONGLONG param_1);
    void FUN_180250be0(LONGLONG param_1);


    virtual void* ExecuteEditorCommand(ttl::string_base<char>, ttl::string_base<char>, ttl::string_base<char>);
    //virtual class ttl::string_base<char> ExecuteEditorCommand(class ttl::string_base<char> const&, class ttl::string_base<char> const&, class ttl::string_base<char> const&);
    //virtual ttl::string_base<char> __thiscall ExecuteEditorCommand(ttl::string_base<char>, ttl::string_base<char>, ttl::string_base<char>);
    //virtual ttl::string_base<char> ExecuteEditorCommand(ttl::string_base<char>, ttl::string_base<char>, ttl::string_base<char>); // class __declspec(dllimport)
    //virtual void** ExecuteEditorCommand(void** param_2, void** param_3, void** param_4);
    virtual uint64_t FUN_180036660(LONGLONG param_2);
    virtual bool CopyFields(class CRTTIObject* param_1, bool param_2);
    virtual bool CopyPointerFields(class CRTTIObject* param_1);
    virtual bool ExchangePointerFields(class CRTTIObject* param_1);
    /*
    CGSObject::ClassWriterSave
    CGame::~CGame
    CGame::~CGame
    CGame::GetRTTI
    CGame::GetEngineRTTI
    CRTTIObject::GetEngineRTTIObject
    CGSObject::GetScriptRTTIObject
    CRTTIObject::GetEngineRTTIObject
    CGSObject::GetScriptRTTIObject
    CRTTIObject::GetPrivateObjects
    CRTTIObject::DestroyPrivateObjects
    CGSObject::GetSubstParentForPrivateObjects
    CRTTIObject::GetAllObjects
    CRTTIObject::GetAllObjects
    CRTTIObject::IsRTTIObjectNameReadOnly
    CRTTIObject::SetRTTIObjectName
    CRTTIObject::GetRTTIObjectName
    CGameObject::SetFieldExpanded
    CGameObject::IsFieldExpanded
    CGSObject::GetVisibleFields
    CRTTIObject::CallVoidMethod
    CRTTIObject::LoadFields
    CRTTIObject::ToBufferReplicated
    CRTTIObject::FromBufferReplicated
    CRTTIObject::GetBufferReplicatedDataSize
    CGameObject::ShouldSaveField
    CRTTIObject::CopyFields
    CRTTIObject::CopyPointerFields
    CRTTIObject::ExchangePointerFields
    CGSObject::FindObjectByID
    CGSObject::FindObjectByNetPointer
    CGSObject::GetNetPointer
    CGSObject::CalcMemoryUsage
    CGSObject::CallOnUpdateEditorAttributes
    CGSObject::GetValidFieldValuesEditor
    CGSObject::GetStatusEditor
    CGameObject::IsFieldChanged
    CGameObject::SetFieldChangedFlag
    CRTTIObject::OnFieldChanged2
    CGSObject::OnFieldChanged
    CGSObject::OnFailedToLoadField
    CRTTIObject::GetDynamicRTTIObject
    CRTTIObject::GetDynamicRTTIObject
    CRTTIObject::Validate
    CRTTIObject::Query
    CGSObject::SelectObjectEditor
    CGSObject::HideObjectEditor
    CGameObject::IsObjectHiddenEditor
    CGSObject::OnDeleteObjectEditor
    CGSObject::CopyObjectEditor
    CGSObject::EnableVisualizationEditor
    CSerializableObject::Load
    CGame::LoadChunk
    CSerializableObject::ChunkLoadGSObject
    CGame::SetGameScriptObject
    CGSObject::DeleteThis
    CGSObject::ConstructObject
    CGSObject::PreInitializeObject
    CGSObject::InitializeObject
    CGSObject::InitObject
    CGame::DestroyObject
    CGSObject::CallOnPreCreate
    CGSObject::CallOnCreate
    CGSObject::CallOnPostCreate
    CGame::CallOnDestroy
    CGSObject::FindIndirectPrivateOwner
    CGSObject::FindPrivateObject
    CGSObject::LinkOwnerPtr
    CGSObject::LinkOwnerPtr
    CGSObject::GetPresetsId
    CGSObject::SetAndProcessPresets
    CGSObject::SetAndProcessPresets
    CGSObject::ProcessPresets
    CGSObject::ProcessPresets
    CGSObject::SetRenderVisualisation
    CGSObject::SetName
    CGSObject::SetLevel
    CGSObject::Repl_GetObject
    CGSObject::Repl_GetId
    CGSObject::Repl_GetName
    CGSObject::Repl_GetRtti
    CGSObject::Repl_GetPresetsId
    CGSObject::Repl_OnReplicationStart
    CGSObject::Repl_OnReplicationStop
    CGSObject::Repl_OnReplicationPrepare
    CGSObject::Repl_OnReplicationResolve
    CGSObject::Repl_OnOwnerChanged
    CGSObject::Repl_GetSystemProfileFeature
    CGSObject::GetDescriptionEditor
    CGSObject::GetGuidDescriptionEditor
    CGSObject::SetPresetsDataEditor
    CGSObject::ProcessPresetsEditor
    CGSObject::SetAndProcessPresetsEditor
    CGSObject::CanSetFieldCharEditor
    CGSObject::CanSetFieldUCharEditor
    CGSObject::CanSetFieldShortEditor
    CGSObject::CanSetFieldUShortEditor
    CGSObject::CanSetFieldIntEditor
    CGSObject::CanSetFieldUIntEditor
    CGSObject::CanSetFieldInt64Editor
    CGSObject::CanSetFieldUInt64Editor
    CGSObject::CanSetFieldFloatEditor
    CGSObject::CanSetFieldDoubleEditor
    CGSObject::CanSetFieldBoolEditor
    CGSObject::CanSetFieldStringEditor
    CGSObject::CanSetFieldVec2Editor
    CGSObject::CanSetFieldVec3Editor
    CGSObject::CanSetFieldVec4Editor
    CGSObject::CanSetFieldMtx34Editor
    CGSObject::CanSetFieldMtx44Editor
    CGSObject::CanSetFieldPtrEditor
    CGSObject::CanSetFieldPtrContainerEditor
    CGSObject::CanSetFieldEnumEditor
    CGSObject::CanSetFieldFlagsEditor
    CGSObject::CanSetFieldStringVectorEditor
    CGame::OnFrame
    CGame::OnFrameEditor
    CGSObject::OnPreAnimUpdate
    CGSObject::OnPostAnimUpdate
    CGame::OnPostUpdate
    CGSObject::OnPostUpdateEditor
    CGSObject::IsExactUIEngineObject
    CGame::ClearVars
    CGame::Initialize
    CGame::InitializeGamerProfile
    CGame::GetGameDirectoryName
    CGame::Initialize
    CGame::OnChunkInstalled
    CGame::WaitForPipelineThreads
    CGame::AddFrameEnd
    CGame::RemoveFromFrameEnd
    CGame::RemoveFromFrameEnd
    CGame::GetIReportingTool
    CGame::InitializeReportingTool
    CGame::GetIChromeSync
    CGame::CreateChromeSync
    CGame::InitializeChromeSync
    CGame::ShutdownChromeSync
    CGame::Repl_FindRtti
    CGame::Repl_OnLocalIdChanged
    CGame::Repl_OnTargetJoined
    CGame::Repl_OnTargetLeft
    CGame::OnMsgReceived
    CGame::Lobby_OnRemotePeerJoined
    CGame::Lobby_OnRemotePeerLeft
    CGame::Lobby_OnRemotePeerStartedJoining
    CGame::Lobby_OnRemotePeerFailedJoining
    CGame::Lobby_OnJoined
    CGame::Lobby_OnSessionEnd
    CGame::Lobby_OnLeft
    CGame::Lobby_OnSessionCreateFailure
    CGame::Lobby_OnSessionCreateSuccess
    CGame::Lobby_OnSessionInviteReceived
    CGame::Lobby_OnBecameMaster
    CGame::Lobby_ReleaseNetworkObjects
    CGame::Lobby_CreateNetworkObjects
    CGame::Lobby_GetLocalClient
    CGame::Lobby_OnFullVersionEnabled
    CGame::Lobby_OnGamePresenceOffline
    CGame::Lobby_OnNetworkConnectionLost
    CGame::Lobby_OnInactiveUserInvited
    CGame::Lobby_OnPartyGameCreated
    CGame::Lobby_OnPartyGameCreationFailure
    CGame::Lobby_OnPartyGameJoined
    CGame::Lobby_OnPartyGameJoiningFailure
    CGame::Lobby_OnPartyGameJoiningReady
    CGame::Lobby_OnPartyGameJoiningNotAvailable
    CGame::Lobby_OnInviteReceived
    CGame::Lobby_OnInviteAccepted
    CGame::Lobby_OnInviteRejected
    CGame::Lobby_OnAppSuspending
    CGame::Lobby_OnAppResuming
    CGame::Lobby_OnActivePlayerSigningOut
    CGame::Lobby_OnContentChanged
    CGame::Lobby_OnProfileDataRemotelyChanged
    CGame::Lobby_OnSessionStart
    CGame::Lobby_OnSessionEnd
    CGame::Lobby_InviteAcceptingFailure
    CGame::Lobby_OnAntiCheatStatusChanged
    CGame::Lobby_OnNatChanged
    CGame::GetConfigurationName
    CGame::IsLightFXDisabled
    CGame::SetScreenAdjust
    CGame::GetScreenAdjust
    CGame::GetScreenAdjustRanges
    CGame::GetDefaultScreenAdjust
    * /
};
*/