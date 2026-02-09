//
// Created by Brendon on 2/5/2026.
//

#pragma once
#include "engine/Export.h"
#include "engine/Kernel3D/Matrix.h"
#include "engine/engine/CtrlOBJ/ModelObject.h"

class ENGINE_API CMeshLinker {
public:
    struct MeshParams { /* PlaceHolder Structure */
    };

    CMeshLinker();
    bool Add(CModelObject *,bool);
    bool Build(fs::ifile & outpath,fs::ifile * logpath,MeshParams * idfk);
    void Clear();
    void SetPivot(mtx34 const &);
    virtual ~CMeshLinker();
};
