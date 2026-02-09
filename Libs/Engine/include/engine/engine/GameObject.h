//
// Created by Brendon on 2/8/2026.
//

#pragma once
#include "Editor/EditorData.h"
#include "Rtti/RTTI.h"
#include "engine/Export.h"
#include "interfaces/RTTI/RTTIObject.h"

class CGameObject : public CRTTIObject {
public:
    void ClassWriterSave(IClassWriter *block, bool i_am_virtual_base) override;
    ~CGameObject() override;

    CRTTI GetRTTI() override;
    CRTTI GetEngineRTTI() override;

    // Newly overridden from CRTTIObject (their vtable slots replace CRTTIObject's)
    void Func_1807e8d58() override; //is now overriden LAB_180036880
    void Func_1807e8d60() override; //LAB_1800368a0

    void Func_1807e8f90() override;

    void Func_1807e8fc8() override;


    void Func_1807e8fe8() override;
    void Func_1807e8ff0() override;

    void Func_1807e9000() override;
    void Func_1807e9008() override;

    //new to CGameObject
    virtual void Func_1807fbfe0();
    virtual void Func_1807fbfe8();
    virtual void Func_1807fbff0();
    virtual void Func_1807fbff8();
    virtual void Func_1807fc000();
    virtual void Func_1807fc008();
    CEditorData *m_pEditorData;
};
