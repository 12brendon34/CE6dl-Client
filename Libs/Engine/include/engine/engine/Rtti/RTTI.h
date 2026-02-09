//
// Created by Brendon on 2/5/2026.
//

#pragma once
#include "engine/Export.h"
#include "engine/engine/interfaces/RTTI/RTTIField.h"

class ENGINE_API CRTTI {
public:
    CRTTI(CRTTI const &);
    //CRTTI(char const *,int, (*);
    void AddField(CRTTIField const *);
    void AddImplementation(CRTTI const *);
    void AddInterface(CRTTI const *);
    //void AddMethod(CRTTIMethod const *);
    bool ArePresetsLoaded() const;
    static void CheckDuplicated(bool);
    bool CheckFilterFlag(__int64) const;
    void ClearClassFlags(int);
    void ClearFieldsList();
    void ClearFilterFlag(__int64) const;
    //void Construct(int, (*);
    //bool CopyFields(CRTTIObject *,CRTTIObject const *,bool) const;
    //bool CopyPointerFields(CRTTIObject *,CRTTIObject const *) const;
    static bool EatWhiteChars(char * &);
    //bool ExchangePointerFields(CRTTIObject *,CRTTIObject *) const;
    CRTTIField const * FindField(char const *) const;
    //CRTTIMethod const * FindMethod(char const *) const;
    CRTTIField const * FindRenamedField(char const *) const;
    bool FromAbstractClass() const;
    bool FromClass(int) const;
    bool FromClass(char const *) const;
    bool FromClass(CRTTI const *) const;
    bool FromClassOrInterface(int) const;
    bool FromClassOrInterface(char const *) const;
    bool FromClassOrInterface(CRTTI const *) const;
    bool FromEngineClass(int) const;
    CRTTI const * GetBaseClass(CRTTI const *) const;
    int GetClassFlags() const;
    int GetClassID() const;
    int GetClassIDUnsafe() const;
    //IScriptManager * GetFactory() const;
    //ttl::vector<CRTTIField const *> const & GetFields() const;
    //void GetFieldsToEdit(ttl::list<CRTTIField const *,ttl::allocator> &) const;
    //void GetFieldsToEditUnsorted(ttl::list<CRTTIField const *,ttl::allocator> &) const;
    //ttl::list<CRTTI const *,ttl::allocator> const & GetImplementingClasses() const;
    //EMem::TYPE GetMemCategory() const;
    //ttl::list<CRTTIMethod const *,ttl::allocator> & GetMethods();
    //ttl::list<CRTTIMethod const *,ttl::allocator> const & GetMethods() const;
    CRTTI const * GetNativeClass() const;
    //Net::Repl::CRttiInfo * GetNetInfo();
    //Net::Repl::CRttiInfo const * GetNetInfo() const;
    //ttl::vector<CRTTIField const *> const & GetReplicatedFields() const;
    int GetSizeofClass() const;
    //CRTTIDebugVis & GetVis();
    //CRTTIDebugVis const & GetVis() const;
    void HideField(char const *);
    void InitializeClassId(int);
    bool IsAbstract() const;
    bool IsExactClass(int) const;
    bool IsExactClass(char const *) const;
    bool IsExactClass(CRTTI const *) const;
    bool IsFieldHidden(CRTTIField const *) const;
    bool IsImplementingInterface(int) const;
    bool IsImplementingInterface(char const *) const;
    bool IsImplementingInterface(CRTTI const *) const;
    bool IsInterface() const;
    bool IsObsolete() const;
    bool IsReplicated() const;
    bool IsSetFieldForcedToSave(CRTTIField const &) const;
    static bool NameGreater(CRTTI const *,CRTTI const *);
    void NetInfoCreate();
    void NetInfoInitialize();
    void NetInfoPreInitialize();
    void OverrideField(char const *);
    bool ParseInfoString(char const *);
    void PrepareReplicatedFields();
    static __int64 RegisterRttiFilterFlag();
    void ReleaseUnusedMemory();
    bool RequiresMatrixChangedNotifications() const;
    void ResetFilterFlags() const;
    void ResolveHiddenFields();
    void ResolveMyAndBaseFields();
    void SetClassDescription(char const *);
    void SetClassFlags(int);
    //void SetFactory(IScriptManager *);
    void SetFilterFlag(__int64) const;
    void SetForcedToSaveField(CRTTIField const &,bool);
    void SetPresetsLoaded(bool) const;
    void Shutdown();
    void UnhideField(char const *);
    static void UnregisterRttiFilterFlag(__int64);
    virtual ~CRTTI();

    //virtual CRTTIObject * CreateInstance() const;
    //virtual IObject * CreateObject() const;
    //virtual char const * GetClassDescription() const;
    //virtual char const * GetClassNameA() const;
};