//
// Created by Brendon on 2/5/2026.
//

#pragma once
#include <cstdint>


#include "engine/Kernel3D/Matrix.h"
#include "engine/engine/CtrlOBJ/ModelObject.h"
class IEngineImpl {
public:
    virtual ~IEngineImpl();
    virtual void Fn_0002();
    virtual void Fn_0003();
    virtual void Fn_0004();
    virtual void Fn_0005();
    virtual void Fn_0006();
    virtual void Fn_0007();
    virtual void Fn_0008();
    virtual void Fn_0009();
    virtual void Fn_0010();
    virtual void Fn_0011();
    virtual void Fn_0012();
    virtual void Fn_0013();
    virtual void Fn_0014();
    virtual void Fn_0015();
    virtual void Fn_0016();
    virtual void Fn_0017();
    virtual void Fn_0018();
    virtual void Fn_0019();
    virtual void Fn_0020();
    virtual void Fn_0021();
    virtual void Fn_0022();
    virtual void Fn_0023();
    virtual void Fn_0024();
    virtual void Fn_0025();
    virtual void Fn_0026();
    virtual void Fn_0027();
    virtual void Fn_0028();
    virtual void Fn_0029();
    virtual void Fn_0030();
    virtual void Fn_0031();
    virtual void Fn_0032();
    virtual void Fn_0033();
    virtual void Fn_0034();
    virtual void Fn_0035();
    virtual void Fn_0036();
    virtual void Fn_0037();
    virtual void Fn_0038();
    virtual void Fn_0039();
    virtual void Fn_0040();
    virtual void Fn_0041();
    virtual void Fn_0042();
    virtual void Fn_0043();
    virtual void Fn_0044();
    virtual void Fn_0045();
    virtual void Fn_0046();
    virtual void Fn_0047();
    virtual void Fn_0048();
    virtual void Fn_0049();
    virtual void Fn_0050();
    virtual void Fn_0051();
    virtual void Fn_0052();
    virtual void Fn_0053();
    virtual void Fn_0054();
    virtual void Fn_0055();
    virtual void Fn_0056();
    virtual void Fn_0057();
    virtual void Fn_0058();
    virtual void Fn_0059();
    virtual void Fn_0060();
    virtual void Fn_0061();
    virtual void Fn_0062();
    virtual void Fn_0063();
    virtual void Fn_0064();
    virtual void Fn_0065();
    virtual void Fn_0066();
    virtual CModelObject* AddModelObject(__int64 param_2, char *ObjectClassName, char *mesh, mtx34* identityMatrix, char add_to_grid, uint8_t load_defaults, bool call_editor_on_create, char *object_name);
};
