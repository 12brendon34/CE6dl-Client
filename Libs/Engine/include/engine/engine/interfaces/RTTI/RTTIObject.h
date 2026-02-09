//
// Created by Brendon on 2/9/2026.
//

#pragma once
#include "engine/engine/Rtti/RTTI.h"

class IClassWriter;

class IObject {
public:
    virtual void ClassWriterSave(IClassWriter *block, bool i_am_virtual_base);
    virtual ~IObject();
};

class CRTTIObject : public IObject {
public:
    virtual void ClassWriterSave(IClassWriter *block, bool i_am_virtual_base);
    virtual ~CRTTIObject();

    virtual CRTTI GetRTTI();
    virtual CRTTI GetEngineRTTI(); // same address as GetRTTI();

    // all 4 of these return
    /*
    CRTTIObject * __thiscall CRTTIObject::GetScriptRTTIObject(CRTTIObject *this)
    {
      return this;
    }
     */
    virtual CRTTIObject *GetEngineRTTIObject();
    virtual CRTTIObject *GetScriptRTTIObject();
    virtual CRTTIObject *GetEngineRTTIObject_1();
    virtual CRTTIObject *GetScriptRTTIObject_1();

    // same as CRTTIObject::GetPrivateObjects
    virtual void GetPrivateObjects(class ttl::list<class IGSObject *, class ttl::allocator> *, bool, bool);
    virtual void DestroyPrivateObjects();
    virtual void GetSubstParentForPrivateObjects(); // stripped/ ret 0
    virtual void GetAllObjects(class ttl::vector<class IGSObject *> &, bool);
    virtual void GetAllObjects(class ttl::set<class CRTTIObject *, struct ttl::less<class CRTTIObject *>, class ttl::allocator> &, bool);
    virtual bool BlockRpackOperationsByPendingPackUiOperations(); //stripped/ret false

    //+ 4 billion other virtual functions I haven't bothered implementing
    //when I do get arround to actually doing this, remember that I need to correct the overrides in ../../GameObject.h

    //The names here are likely partually wrong, things like IPhBody::~IPhBody or IModelObject::CanGoToSimpleObjectsEditor are stripped functions that all return the same thing, compiler optimization type shit
    //a similar thing with GetEngineRTTIObject, where those 4 functions all point to the same thing, as they all return 'this'
    virtual void Func_1807e8d48(); //IPhBody::~IPhBody
    virtual void Func_1807e8d50(); //CRTTIObject::GetRTTIObjectName
    virtual void Func_1807e8d58(); //IPhBody::~IPhBody
    virtual void Func_1807e8d60(); //IUIElementControl::CanBeEnabled
    virtual void Func_1807e8d68(); //IPhBody::~IPhBody
    virtual void Func_1807e8d70(); //CRTTIObject::CallVoidMethod
    virtual void Func_1807e8d78(); //CRTTIObject::LoadFields
    virtual void Func_1807e8d80(); //CRTTIObject::SaveFields
    virtual void Func_1807e8d88(); //CRTTIObject::ToBufferReplicated
    virtual void Func_1807e8d90(); //CRTTIObject::FromBufferReplicated
    virtual void Func_1807e8d98(); //CRTTIObject::GetBufferReplicatedDataSize
    virtual void Func_1807e8da0(); //CRTTIObject::GetFieldBoolEditor
    virtual void Func_1807e8da8(); //CRTTIObject::GetFieldBoolEditor
    virtual void Func_1807e8db0(); //CRTTIObject::GetFieldBoolEditor
    virtual void Func_1807e8db8(); //CRTTIObject::GetFieldBoolEditor
    virtual void Func_1807e8dc0(); //CRTTIObject::GetFieldBoolEditor
    virtual void Func_1807e8dc8(); //CRTTIObject::GetFieldBoolEditor
    virtual void Func_1807e8dd0(); //CRTTIObject::GetFieldBoolEditor
    virtual void Func_1807e8dd8(); //CRTTIObject::GetFieldBoolEditor
    virtual void Func_1807e8de0(); //CRTTIObject::GetFieldBoolEditor
    virtual void Func_1807e8de8(); //CRTTIObject::GetFieldBoolEditor
    virtual void Func_1807e8df0(); //CRTTIObject::GetFieldBoolEditor
    virtual void Func_1807e8df8(); //CRTTIObject::GetFieldBoolEditor
    virtual void Func_1807e8e00(); //CRTTIObject::GetFieldStringEditor
    virtual void Func_1807e8e08(); //CRTTIObject::GetFieldBoolEditor
    virtual void Func_1807e8e10(); //CRTTIObject::GetFieldBoolEditor
    virtual void Func_1807e8e18(); //CRTTIObject::GetFieldBoolEditor
    virtual void Func_1807e8e20(); //CRTTIObject::GetFieldBoolEditor
    virtual void Func_1807e8e28(); //CRTTIObject::GetFieldBoolEditor
    virtual void Func_1807e8e30(); //CRTTIObject::GetFieldStringEditor
    virtual void Func_1807e8e38(); //CRTTIObject::GetFieldBoolEditor
    virtual void Func_1807e8e40(); //CRTTIObject::GetFieldBoolEditor
    virtual void Func_1807e8e48(); //CRTTIObject::SetFieldShortEditor
    virtual void Func_1807e8e50(); //CRTTIObject::SetFieldShortEditor
    virtual void Func_1807e8e58(); //CRTTIObject::SetFieldIntEditor
    virtual void Func_1807e8e60(); //CRTTIObject::SetFieldEnumEditor
    virtual void Func_1807e8e68(); //CRTTIObject::SetFieldIntEditor
    virtual void Func_1807e8e70(); //CRTTIObject::SetFieldInt64Editor
    virtual void Func_1807e8e78(); //CRTTIObject::SetFieldInt64Editor
    virtual void Func_1807e8e80(); //CRTTIObject::SetFieldFloatEditor
    virtual void Func_1807e8e88(); //CRTTIObject::SetFieldDoubleEditor
    virtual void Func_1807e8e90(); //CRTTIObject::SetFieldBoolEditor
    virtual void Func_1807e8e98(); //CRTTIObject::SetFieldStringEditor
    virtual void Func_1807e8ea0(); //CRTTIObject::SetFieldMtx34Editor
    virtual void Func_1807e8ea8(); //CRTTIObject::SetFieldMtx34Editor
    virtual void Func_1807e8eb0(); //CRTTIObject::SetFieldMtx34Editor
    virtual void Func_1807e8eb8(); //CRTTIObject::SetFieldMtx34Editor
    virtual void Func_1807e8ec0(); //CRTTIObject::SetFieldMtx34Editor
    virtual void Func_1807e8ec8(); //CRTTIObject::SetFieldStringEditor
    virtual void Func_1807e8ed0(); //CRTTIObject::CanSetFieldEditor
    virtual void Func_1807e8ed8(); //IUIElementControl::CanBeEnabled
    virtual void Func_1807e8ee0(); //IUIElementControl::CanBeEnabled
    virtual void Func_1807e8ee8(); //IUIElementControl::CanBeEnabled
    virtual void Func_1807e8ef0(); //IUIElementControl::CanBeEnabled
    virtual void Func_1807e8ef8(); //IUIElementControl::CanBeEnabled
    virtual void Func_1807e8f00(); //IUIElementControl::CanBeEnabled
    virtual void Func_1807e8f08(); //IUIElementControl::CanBeEnabled
    virtual void Func_1807e8f10(); //IUIElementControl::CanBeEnabled
    virtual void Func_1807e8f18(); //IUIElementControl::CanBeEnabled
    virtual void Func_1807e8f20(); //IUIElementControl::CanBeEnabled
    virtual void Func_1807e8f28(); //IUIElementControl::CanBeEnabled
    virtual void Func_1807e8f30(); //IUIElementControl::CanBeEnabled
    virtual void Func_1807e8f38(); //IUIElementControl::CanBeEnabled
    virtual void Func_1807e8f40(); //IUIElementControl::CanBeEnabled
    virtual void Func_1807e8f48(); //IUIElementControl::CanBeEnabled
    virtual void Func_1807e8f50(); //IUIElementControl::CanBeEnabled
    virtual void Func_1807e8f58(); //IUIElementControl::CanBeEnabled
    virtual void Func_1807e8f60(); //IUIElementControl::CanBeEnabled
    virtual void Func_1807e8f68(); //IUIElementControl::CanBeEnabled
    virtual void Func_1807e8f70(); //IUIElementControl::CanBeEnabled
    virtual void Func_1807e8f78(); //IUIElementControl::CanBeEnabled
    virtual void Func_1807e8f80(); //IUIElementControl::CanBeEnabled
    virtual void Func_1807e8f88(); //CRTTIObject::ExecuteEditorCommand
    virtual void Func_1807e8f90(); //IUIElementControl::CanBeEnabled
    virtual void Func_1807e8f98(); //CRTTIObject::CopyFields
    virtual void Func_1807e8fa0(); //CRTTIObject::CopyPointerFields
    virtual void Func_1807e8fa8(); //CRTTIObject::ExchangePointerFields
    virtual void Func_1807e8fb0(); //CRTTIObject::FindObjectByID
    virtual void Func_1807e8fb8(); //IModelObject::CanGoToSimpleObjectsEditor
    virtual void Func_1807e8fc0(); //CRTTIObject::GetNetPointer
    virtual void Func_1807e8fc8(); //CRTTIObject::CalcMemoryUsage
    virtual void Func_1807e8fd0(); //IPhBody::~IPhBody
    virtual void Func_1807e8fd8(); //CRTTIObject::GetValidFieldValuesEditor
    virtual void Func_1807e8fe0(); //IModelObject::CanGoToSimpleObjectsEditor
    virtual void Func_1807e8fe8(); //CRTTIObject::IsFieldChanged
    virtual void Func_1807e8ff0(); //CRTTIObject::SetFieldChangedFlag
    virtual void Func_1807e8ff8(); //CRTTIObject::OnFieldChanged2
    virtual void Func_1807e9000(); //BlockRpackOperationsByPendingPackUiOperations
    virtual void Func_1807e9008(); //BlockRpackOperationsByPendingPackUiOperations
    virtual void Func_1807e9010(); //IModelObject::CanGoToSimpleObjectsEditor
    virtual void Func_1807e9018(); //IModelObject::CanGoToSimpleObjectsEditor
    virtual void Func_1807e9020(); //IPhBody::~IPhBody
    virtual void Func_1807e9028(); //CRTTIObject::Query
    virtual void Func_1807e9030(); //CRTTIObject::SaveObjectHierarchy
};
