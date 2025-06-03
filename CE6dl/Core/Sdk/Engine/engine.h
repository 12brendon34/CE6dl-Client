#pragma once
#include "igame.h"

#define DLL_EXPORT __declspec(dllimport)

namespace Mount {
    class IMountHelper {

        virtual void Func_00(); // FUN_180257140
        virtual void Func_01(); // LAB_180257230
        virtual void Func_02(); // FUN_180258CB0
        virtual void Func_03(); // FUN_180258D20
        virtual void Func_04(); // LAB_1807D6F10
        virtual void Func_05(); // FUN_1802587E0
        virtual void Func_06(); // FUN_180258AE0
        virtual void Func_07(); // LAB_180258B00
        virtual void Func_08(); // FUN_1802570D0
        virtual void Func_09(); // FUN_180259520
        virtual void Func_10(); // LAB_180259A50
        virtual void Func_11(); // LAB_180259AD0
        virtual void Func_12(); // Stripped
        virtual void Func_13(); // LAB_18025A550
        virtual void Func_14(); // DAT_1808EAAD0
    };

    IMountHelper* __cdecl CreateMountHelper(const char* param1, const char* param2, const char* param3);
    void __cdecl DestroyMountHelper(IMountHelper* helper);
}

struct AssetManager {
    //RDPMainHeader::Platform
    virtual ULONG SetGame(LPCSTR DW, LPCSTR WD, int Platform, bool, char const*);

    //Unsure
    virtual void FUN_1803e5590(); //SetMountDirs
    virtual void FUN_1803e55a0(); //GetMountDirs
    virtual void Stripped();
    virtual void FUN_1803e5a00(); //GetCurrentPlatform
    virtual void FUN_1803e55d0(); //SetForceRpackCreationMode

    virtual void RegRpack(void* CResourceDataPack, char const** string_base);
    virtual void UnregRpack(void* CResourceDataPack, char const** string_base);
    virtual void CopyPackData(void* CResourceDataPack);
    virtual void PastePackData(void* CResourceDataPack);
    virtual void LoadPackData(char const* param_1, long* param_3, long long* param_4);
    virtual void ChangePackMemory(void* CResourceDataPack, long* param_3, long* param_4);
    virtual void CalcResPackInfo();
    virtual void LoadAssetAutoBuild(char const* param_1, unsigned int param_2, char const*);
    virtual void ReleasePack(void* CResourceDataPack);

    virtual void FUN_1803e5160();
    virtual void FUN_1803e5680();
    virtual void FUN_1803e3a00();
    virtual void GetMaxValue();
    virtual void FUN_1803eb1d0();
    virtual void FUN_1803eb200();
    virtual void FUN_1803e37d0();

    virtual void LoadAsset(char const* Path, UINT param_2, char const* param_3);

    virtual ~AssetManager() = default;
};

struct AssetManager* __cdecl GetAssetManager(void);





class __declspec(dllimport) CRTTIObject {
public:
    CRTTIObject(CRTTIObject const&);
    //CRTTIObject(ClassReaderResolve const&);
    CRTTIObject();
    //CRTTIField const* FindField(char const*) const;
    //CRTTIMethod const* FindMethod(char const*) const;
    //int FromBufferFieldVec(ttl::vector<CRTTIField const*> const*, char*, int);
    bool FromClass(int) const;
    bool FromClass(char const*) const;
    bool FromClass(CRTTI const*) const;
    bool FromClassOrInterface(int) const;
    bool FromClassOrInterface(char const*) const;
    bool FromClassOrInterface(CRTTI const*) const;
    bool FromEngineClass(int) const;
    //int GetBufferFieldVecDataSize(ttl::vector<CRTTIField const*> const*);
    char const* GetClassNameA() const;
    /*
    CRTTIFieldBool const* GetFieldBool(char const*, bool&) const;
    CRTTIFieldChar const* GetFieldChar(char const*, char&) const;
    CRTTIFieldDouble const* GetFieldDouble(char const*, double&) const;
    CRTTIFieldEnum const* GetFieldEnum(char const*, int&) const;
    CRTTIFieldFloat const* GetFieldFloat(char const*, float&) const;
    CRTTIFieldInt64 const* GetFieldInt64(char const*, __int64&) const;
    CRTTIFieldInt const* GetFieldInt(char const*, int&) const;
    CRTTIFieldMtx34 const* GetFieldMtx34(char const*, mtx34&) const;
    CRTTIFieldMtx44 const* GetFieldMtx44(char const*, mtx44&) const;
    CRTTIFieldQuat const* GetFieldQuat(char const*, quat&) const;
    CRTTIFieldShort const* GetFieldShort(char const*, short&) const;
    CRTTIFieldString const* GetFieldString(char const*, ttl::string_base<char>&) const;
    CRTTIFieldStringVector const* GetFieldStringVector(char const*, ttl::vector<ttl::string_base<char> >&) const;
    CRTTIFieldUChar const* GetFieldUChar(char const*, unsigned char&) const;
    CRTTIFieldUInt64 const* GetFieldUInt64(char const*, unsigned __int64&) const;
    CRTTIFieldUInt const* GetFieldUInt(char const*, unsigned int&) const;
    CRTTIFieldUShort const* GetFieldUShort(char const*, unsigned short&) const;
    CRTTIFieldVec2 const* GetFieldVec2(char const*, vec2&) const;
    CRTTIFieldVec3 const* GetFieldVec3(char const*, vec3&) const;
    CRTTIFieldVec4 const* GetFieldVec4(char const*, vec4&) const;
    */
    bool IsExactClass(int) const;
    bool IsExactClass(char const*) const;
    bool IsExactClass(CRTTI const*) const;
    bool IsExactEngineClass(int) const;
    //static CRTTIObject* LoadObjectHierarchy(fs::ifile&, bool);
    static void RegisterRTTI();
    //static void RegisterValidator(IBaseValidator&);
    //void SaveFieldVec(ttl::vector<CRTTIField const*> const*, fs::ifile&, int);
    /*
    CRTTIFieldBool const* SetFieldBool(char const*, bool);
    CRTTIFieldChar const* SetFieldChar(char const*, char);
    CRTTIFieldDouble const* SetFieldDouble(char const*, double);
    CRTTIFieldEnum const* SetFieldEnum(char const*, int);
    CRTTIFieldFloat const* SetFieldFloat(char const*, float);
    CRTTIFieldInt64 const* SetFieldInt64(char const*, __int64);
    CRTTIFieldInt const* SetFieldInt(char const*, int);
    CRTTIFieldMtx34 const* SetFieldMtx34(char const*, mtx34 const&);
    CRTTIFieldMtx44 const* SetFieldMtx44(char const*, mtx44 const&);
    CRTTIFieldQuat const* SetFieldQuat(char const*, quat const&);
    CRTTIFieldShort const* SetFieldShort(char const*, short);
    CRTTIFieldString const* SetFieldString(char const*, ttl::string_base<char> const&);
    CRTTIFieldStringVector const* SetFieldStringVector(char const*, ttl::vector<ttl::string_base<char> > const&);
    CRTTIFieldUChar const* SetFieldUChar(char const*, unsigned char);
    CRTTIFieldUInt64 const* SetFieldUInt64(char const*, unsigned __int64);
    CRTTIFieldUInt const* SetFieldUInt(char const*, unsigned int);
    CRTTIFieldUShort const* SetFieldUShort(char const*, unsigned short);
    CRTTIFieldVec2 const* SetFieldVec2(char const*, vec2 const&);
    CRTTIFieldVec3 const* SetFieldVec3(char const*, vec3 const&);
    CRTTIFieldVec4 const* SetFieldVec4(char const*, vec4 const&);
    */
    //int ToBufferFieldVec(ttl::vector<CRTTIField const*> const*, char*, int);
    /*
    virtual ~CRTTIObject();
    virtual void CalcMemoryUsage(SObjectMemoryUsage&) const;
    virtual void CallOnUpdateEditorAttributes(CRTTIField const*);
    virtual void CallVoidMethod(char const*, ...);
    virtual bool CanSetFieldBoolEditor(char const*, bool, ttl::string_base<char>&) const;
    virtual bool CanSetFieldCharEditor(char const*, char, ttl::string_base<char>&) const;
    virtual bool CanSetFieldDoubleEditor(char const*, double, ttl::string_base<char>&) const;
    virtual bool CanSetFieldEditor(char const*, char const*, ttl::string_base<char>&) const;
    virtual bool CanSetFieldEnumEditor(char const*, int, ttl::string_base<char>&) const;
    virtual bool CanSetFieldFlagsEditor(char const*, int, ttl::string_base<char>&) const;
    virtual bool CanSetFieldFloatEditor(char const*, float, ttl::string_base<char>&) const;
    virtual bool CanSetFieldInt64Editor(char const*, __int64, ttl::string_base<char>&) const;
    virtual bool CanSetFieldIntEditor(char const*, int, ttl::string_base<char>&) const;
    virtual bool CanSetFieldMtx34Editor(char const*, mtx34 const&, ttl::string_base<char>&) const;
    virtual bool CanSetFieldMtx44Editor(char const*, mtx44 const&, ttl::string_base<char>&) const;
    virtual bool CanSetFieldPtrContainerEditor(char const*, ttl::vector<IGSObject*> const&, ttl::string_base<char>&) const;
    virtual bool CanSetFieldPtrEditor(char const*, IGSObject const*, ttl::string_base<char>&) const;
    virtual bool CanSetFieldShortEditor(char const*, short, ttl::string_base<char>&) const;
    virtual bool CanSetFieldStringEditor(char const*, ttl::string_base<char> const&, ttl::string_base<char>&) const;
    virtual bool CanSetFieldStringVectorEditor(char const*, ttl::vector<ttl::string_base<char> > const&, ttl::string_base<char>&) const;
    virtual bool CanSetFieldUCharEditor(char const*, unsigned char, ttl::string_base<char>&) const;
    virtual bool CanSetFieldUInt64Editor(char const*, unsigned __int64, ttl::string_base<char>&) const;
    virtual bool CanSetFieldUIntEditor(char const*, unsigned int, ttl::string_base<char>&) const;
    virtual bool CanSetFieldUShortEditor(char const*, unsigned short, ttl::string_base<char>&) const;
    virtual bool CanSetFieldVec2Editor(char const*, vec2 const&, ttl::string_base<char>&) const;
    virtual bool CanSetFieldVec3Editor(char const*, vec3 const&, ttl::string_base<char>&) const;
    virtual bool CanSetFieldVec4Editor(char const*, vec4 const&, ttl::string_base<char>&) const;
    virtual void ClassWriterSave(IClassWriter*, bool) const;
    virtual bool CopyFields(CRTTIObject const*, bool);
    virtual bool CopyPointerFields(CRTTIObject const*);
    virtual void DestroyPrivateObjects();
    virtual bool ExchangePointerFields(CRTTIObject*);
    virtual ttl::string_base<char> ExecuteEditorCommand(ttl::string_base<char> const&, ttl::string_base<char> const&);
    virtual IGSObject* FindObjectByID(int) const;
    virtual IGSObject* FindObjectByNetPointer(SRttiNetPointer const&) const;
    virtual int FromBufferReplicated(char*, int);
    virtual void GetAllObjects(ttl::set<CRTTIObject*, ttl::less<CRTTIObject*>, ttl::allocator>&, bool);
    virtual void GetAllObjects(ttl::vector<IGSObject*>&, bool);
    virtual int GetBufferReplicatedDataSize();
    virtual IDynamicRTTIObject* GetDynamicRTTIObject();
    virtual IDynamicRTTIObject const* GetDynamicRTTIObject() const;
    virtual CRTTI const* GetEngineRTTI() const;
    virtual CRTTIObject* GetEngineRTTIObject();
    virtual CRTTIObject const* GetEngineRTTIObject() const;
    virtual CRTTIFieldBool const* GetFieldBoolEditor(char const*, bool&) const;
    virtual CRTTIFieldChar const* GetFieldCharEditor(char const*, char&) const;
    virtual CRTTIFieldDouble const* GetFieldDoubleEditor(char const*, double&) const;
    virtual CRTTIFieldEnum const* GetFieldEnumEditor(char const*, int&) const;
    virtual CRTTIFieldFloat const* GetFieldFloatEditor(char const*, float&) const;
    virtual CRTTIFieldInt64 const* GetFieldInt64Editor(char const*, __int64&) const;
    virtual CRTTIFieldInt const* GetFieldIntEditor(char const*, int&) const;
    virtual CRTTIFieldMtx34 const* GetFieldMtx34Editor(char const*, mtx34&) const;
    virtual CRTTIFieldMtx44 const* GetFieldMtx44Editor(char const*, mtx44&) const;
    virtual CRTTIFieldShort const* GetFieldShortEditor(char const*, short&) const;
    virtual CRTTIFieldString const* GetFieldStringEditor(char const*, ttl::string_base<char>&) const;
    virtual CRTTIFieldStringVector const* GetFieldStringVectorEditor(char const*, ttl::vector<ttl::string_base<char> >&) const;
    virtual CRTTIFieldUChar const* GetFieldUCharEditor(char const*, unsigned char&) const;
    virtual CRTTIFieldUInt64 const* GetFieldUInt64Editor(char const*, unsigned __int64&) const;
    virtual CRTTIFieldUInt const* GetFieldUIntEditor(char const*, unsigned int&) const;
    virtual CRTTIFieldUShort const* GetFieldUShortEditor(char const*, unsigned short&) const;
    virtual CRTTIFieldVec2 const* GetFieldVec2Editor(char const*, vec2&) const;
    virtual CRTTIFieldVec3 const* GetFieldVec3Editor(char const*, vec3&) const;
    virtual CRTTIFieldVec4 const* GetFieldVec4Editor(char const*, vec4&) const;
    virtual SRttiNetPointer GetNetPointer() const;
    virtual void GetPrivateObjects(ttl::list<IGSObject*, ttl::allocator>*, bool, bool);
    virtual CRTTI const* GetRTTI() const;
    virtual char const* GetRTTIObjectName() const;
    virtual CRTTIObject* GetScriptRTTIObject();
    virtual CRTTIObject const* GetScriptRTTIObject() const;
    virtual EEditorObjectOrAttributeStatus::TYPE GetStatusEditor(CRTTIField const*);
    virtual CGSObject* GetSubstParentForPrivateObjects();
    virtual bool GetValidFieldValuesEditor(CRTTIField const&, ttl::vector<ttl::string_base<char> >&, ttl::vector<ttl::string_base<char> >&);
    virtual void GetVisibleFields(ttl::vector<CRTTIField const*>&);
    virtual bool IsFieldChanged(CRTTIField const*) const;
    virtual bool IsFieldExpanded(CRTTIField const*, int) const;
    virtual bool IsRTTIObjectNameReadOnly();
    virtual void LoadFields(fs::ifile&, IPtrResolver&, bool);
    virtual bool OnFailedToLoadField(char const*, fs::ifile&, unsigned char, int);
    virtual bool OnFieldChanged2(CRTTIField const*);
    virtual bool OnFieldChanged(CRTTIField const*);
    virtual void Query(IBaseValidator&, ttl::vector<CRTTIObject*>&) const;
    virtual void SaveFields(fs::ifile&, int);
    virtual void SaveObjectHierarchy(fs::ifile&);
    virtual CRTTIFieldBool const* SetFieldBoolEditor(char const*, bool);
    virtual void SetFieldChangedFlag(CRTTIField const*, bool);
    virtual CRTTIFieldChar const* SetFieldCharEditor(char const*, char);
    virtual CRTTIFieldDouble const* SetFieldDoubleEditor(char const*, double);
    virtual CRTTIFieldEnum const* SetFieldEnumEditor(char const*, int);
    virtual void SetFieldExpanded(CRTTIField const*, int, bool);
    virtual CRTTIFieldFloat const* SetFieldFloatEditor(char const*, float);
    virtual CRTTIFieldInt64 const* SetFieldInt64Editor(char const*, __int64);
    virtual CRTTIFieldInt const* SetFieldIntEditor(char const*, int);
    virtual CRTTIFieldMtx34 const* SetFieldMtx34Editor(char const*, mtx34 const&);
    virtual CRTTIFieldMtx44 const* SetFieldMtx44Editor(char const*, mtx44 const&);
    virtual CRTTIFieldShort const* SetFieldShortEditor(char const*, short);
    virtual CRTTIFieldString const* SetFieldStringEditor(char const*, ttl::string_base<char> const&);
    virtual CRTTIFieldStringVector const* SetFieldStringVectorEditor(char const*, ttl::vector<ttl::string_base<char> > const&);
    virtual CRTTIFieldUChar const* SetFieldUCharEditor(char const*, unsigned char);
    virtual CRTTIFieldUInt64 const* SetFieldUInt64Editor(char const*, unsigned __int64);
    virtual CRTTIFieldUInt const* SetFieldUIntEditor(char const*, unsigned int);
    virtual CRTTIFieldUShort const* SetFieldUShortEditor(char const*, unsigned short);
    virtual CRTTIFieldVec2 const* SetFieldVec2Editor(char const*, vec2 const&);
    virtual CRTTIFieldVec3 const* SetFieldVec3Editor(char const*, vec3 const&);
    virtual CRTTIFieldVec4 const* SetFieldVec4Editor(char const*, vec4 const&);
    virtual void SetRTTIObjectName(char const*);
    virtual bool ShouldSaveField(CRTTIField const*) const;
    virtual int ToBufferReplicated(char*, int);
    virtual void Validate(IBaseValidator&) const;
    */
};

class __declspec(dllimport) CRTTI {
public:
    CRTTI(CRTTI const&);
    //CRTTI(char const*, int, (*);
    //void AddField(CRTTIField const*);
    void AddImplementation(CRTTI const*);
    void AddInterface(CRTTI const*);
    //void AddMethod(CRTTIMethod const*);
    bool ArePresetsLoaded() const;
    static void CheckDuplicated(bool);
    bool CheckFilterFlag(__int64) const;
    void ClearClassFlags(int);
    void ClearFieldsList();
    void ClearFilterFlag(__int64) const;
    //void Construct(int, (*);
    bool CopyFields(CRTTIObject*, CRTTIObject const*, bool) const;
    bool CopyPointerFields(CRTTIObject*, CRTTIObject const*) const;
    static bool EatWhiteChars(char*&);
    bool ExchangePointerFields(CRTTIObject*, CRTTIObject*) const;
    //CRTTIField const* FindField(char const*) const;
    //CRTTIMethod const* FindMethod(char const*) const;
    //CRTTIField const* FindRenamedField(char const*) const;
    bool FromAbstractClass() const;
    bool FromClass(int) const;
    bool FromClass(char const*) const;
    bool FromClass(CRTTI const*) const;
    bool FromClassOrInterface(int) const;
    bool FromClassOrInterface(char const*) const;
    bool FromClassOrInterface(CRTTI const*) const;
    bool FromEngineClass(int) const;
    CRTTI const* GetBaseClass(CRTTI const*) const;
    int GetClassFlags() const;
    int GetClassID() const;
    int GetClassIDUnsafe() const;
    //IScriptManager* GetFactory() const;
    //ttl::vector<CRTTIField const*> const& GetFields() const;
    //void GetFieldsToEdit(ttl::list<CRTTIField const*, ttl::allocator>&) const;
    //void GetFieldsToEditUnsorted(ttl::list<CRTTIField const*, ttl::allocator>&) const;
    ttl::list<CRTTI const*, ttl::allocator> const& GetImplementingClasses() const;
    //EMem::TYPE GetMemCategory() const;
    //ttl::list<CRTTIMethod const*, ttl::allocator>& GetMethods();
    //ttl::list<CRTTIMethod const*, ttl::allocator> const& GetMethods() const;
    CRTTI const* GetNativeClass() const;
    //Net::Repl::CRttiInfo* GetNetInfo();
    //Net::Repl::CRttiInfo const* GetNetInfo() const;
    //ttl::vector<CRTTIField const*> const& GetReplicatedFields() const;
    int GetSizeofClass() const;
    //CRTTIDebugVis& GetVis();
    //CRTTIDebugVis const& GetVis() const;
    void HideField(char const*);
    void InitializeClassId(int);
    bool IsAbstract() const;
    bool IsExactClass(int) const;
    bool IsExactClass(char const*) const;
    bool IsExactClass(CRTTI const*) const;
    //bool IsFieldHidden(CRTTIField const*) const;
    bool IsImplementingInterface(int) const;
    bool IsImplementingInterface(char const*) const;
    bool IsImplementingInterface(CRTTI const*) const;
    bool IsInterface() const;
    bool IsObsolete() const;
    bool IsReplicated() const;
    //bool IsSetFieldForcedToSave(CRTTIField const&) const;
    static bool NameGreater(CRTTI const*, CRTTI const*);
    void NetInfoCreate();
    void NetInfoInitialize();
    void NetInfoPreInitialize();
    void OverrideField(char const*);
    bool ParseInfoString(char const*);
    void PrepareReplicatedFields();
    static __int64 RegisterRttiFilterFlag();
    void ReleaseUnusedMemory();
    bool RequiresMatrixChangedNotifications() const;
    void ResetFilterFlags() const;
    void ResolveHiddenFields();
    void ResolveMyAndBaseFields();
    void SetClassDescription(char const*);
    void SetClassFlags(int);
    //void SetFactory(IScriptManager*);
    void SetFilterFlag(__int64) const;
    //void SetForcedToSaveField(CRTTIField const&, bool);
    void SetPresetsLoaded(bool) const;
    void Shutdown();
    void UnhideField(char const*);
    static void UnregisterRttiFilterFlag(__int64);

    virtual ~CRTTI();
    virtual CRTTIObject* CreateInstance() const;
    //virtual IObject* CreateObject() const;
    //virtual char const* GetClassDescription() const;
    //virtual char const* GetClassNameA() const;

};

extern "C" DLL_EXPORT bool Main(void);
extern "C" DLL_EXPORT int ShowSplashscreen(HINSTANCE hInst, LPCSTR Splash, LPSTR Title, HANDLE Icon);
extern "C" DLL_EXPORT void HideSplashscreen();
extern "C" DLL_EXPORT bool InitializeGameScript(LPCSTR GameDll, ULONGLONG param_2);
extern "C" DLL_EXPORT IGame* CreateGame(LPCSTR param_1, HINSTANCE hinstance, bool param_3, LPCSTR param_4);
extern "C" DLL_EXPORT void DestroyGame(__int64 param_1, __int64 param_2, __int64 param_3, __int64 param_4);
extern "C" DLL_EXPORT void UninitializeGameScript();