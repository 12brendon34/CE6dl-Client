//
// Created by Brendon on 1/13/2026.
//
#pragma once
#include "engine/ChromeTypes.h"
#include "engine/Export.h"
#include "engine/Kernel3D/Matrix.h"
#include "engine/engine/Rtti/RTTI.h"
#include "engine/filesystem/File.h"

// unimp
class CLevelView {
};

//forward dec (circular ts)
class IBaseCamera;

class ENGINE_API CCamera {
public:
    virtual ~CCamera();
    virtual void Save(fs::ifile *param_2);
    virtual void Save_1(fs::ifile *param_2);
    virtual void Load(fs::ifile *param_2);
    virtual void LoadOldMtx43(fs::ifile *param_2);
    mtx34 m_ViewMatrix;
    mtx34 m_InvViewMatrix;
    mtx44 m_Projection;
    mtx44 m_Combined;
    vec4a m_FrustumPlanes[6];
    float m_Left;
    float m_Right;
    float m_Bottom;
    float m_Top;
    float m_Near;
    float m_Far;
    float m_DepthBias;
    std::byte field14_0x16c[20];
    vec3 m_FrustumPoints[8];
    extents m_Extents;
    aabb m_AABB;
    std::byte field18_0x210[24];
    bool m_InfiniteFar;
    bool m_ZNormalized;
    //end of CCamera
};

class ENGINE_API CBaseCamera : public CCamera {
    struct CBaseCameraMemento {
    };

public:
    static void DeleteMemento(CBaseCameraMemento const *);
    static CBaseCameraMemento const *LoadMemento(fs::ifile &);
    static CRTTI m_RTTI;

    virtual ~CBaseCamera();
    virtual void Save(fs::ifile* param_2);
    virtual void Save_1(fs::ifile* param_2);
    virtual void Load(fs::ifile* param_2);
    virtual void Load_1(fs::ifile* param_2);
    virtual void Frame();
    virtual void PostUpdate();
    virtual void SetupBeforeRender();
    virtual void SetFrustum(float fovRadians, float ClipNear, float ClipFar);
    virtual void SetOrthoView(int param_1);
    virtual void SetPerspectiveView();
    virtual char *GetModeName();
    virtual void ChangeToUSERMode();
    virtual void EnterDirectFrustumMode(float DFLeft, float DFRight, float DFTop, float DFBottom);
    virtual void EnterDirectFrustumMode(float halfWidth, float halfHeight);
    virtual void LeaveDirectFrustumMode();
    virtual void SetZoom(float zoom);
    virtual float GetZoom();
    virtual CBaseCameraMemento *GetMemento();
    virtual void UpdateToMemento(CBaseCameraMemento *param_2);

    std::byte field21_0x22a[126]; //Contains GCSObject & CGameObject & CSerializableObject or whatever
    IBaseCamera *m_IBC;
    float m_DFLeft;
    float m_DFRight;
    float m_DFTop;
    float m_DFBottom;
    bool m_bOrthoView;
    bool m_UseUserZoom;
    bool m_DirectFrustum;
    bool m_UNKNOWN;
    int m_OrthoMode;
    float m_fZoom;
    float m_fFOV;
    float m_fAlternativeFOV;
    float m_fNearRange;
    float m_fFarRange;
    float m_fHFOV;
    float m_fVFOV;
    vec3 m_vPosPersp;
    vec3 m_vBaseXPersp;
    vec3 m_vBaseYPersp;
    vec3 m_vBaseZPersp;
    int _padding_;
    CLevelView *m_pView;
    float m_fUserZoom;
    float m_fZoomScale;
    float m_fZoomScale2;
    float m_fInvZoomScale2;
    float m_fInvZoomScale;
    bool Shakeable;
    bool m_UNKNOWN2; //might be _pad
};
