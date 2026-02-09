//
// Created by Brendon on 1/12/2026.
//
#pragma once
#include "CBaseCamera.h"
#include "engine/ChromeTypes.h"
#include "engine/Export.h"
#include "engine/Kernel/ttl/String.h"
#include "engine/engine/Rtti/RTTI.h"

class ECameraMode {
public:
    enum TYPE {
        PERSPECTIVE = 41,
        USER = 42,
        FRONT = 43,
        BACK = 44,
        TOP = 45,
        BOTTOM = 46,
        LEFT = 47,
        RIGHT = 48
    };
};

class ENGINE_API IBaseCamera {
public:
    IBaseCamera();
    IBaseCamera(IBaseCamera const &);
    CBaseCamera *ToCBaseCamera();
    CBaseCamera const *ToCBaseCamera() const;
    static CRTTI const *GetNativeClass();
    static ttl::string_base<char> FormatCameraParams(vec3 const &, vec3 const &);
    static bool ParseCameraParams(ttl::string_base<char> const &, vec3 &, vec3 &, vec3 &);
    void ForceFrame();
    void Rotate(float angle, vec3 const &axis);
    float GetAspect();
    float GetClipNear();
    float GetClipFar();
    float GetFOV();
    float GetUserZoomScale() const;
    void SetClipNear(float);
    void SetClipFar(float);
    void SetFOV(float);
    void SetUserZoomScale(float);

    // matrices
    mtx44 const &GetCombinedMatrix();
    mtx44 const &GetProjectionMatrix();
    mtx34 const &GetViewMatrix();
    mtx34 const &GetInvCameraMatrix();
    void SetCameraMatrix(mtx34 const &);
    void SetInvCameraMatrix(mtx34 const &);
    vec3 const GetPosition() const;
    void SetPosition(vec3 const &);
    vec3 const GetForwardVector() const;
    vec3 const GetLeftVector() const;
    vec3 const GetUpVector() const;
    vec4a const *GetFrustumPlanes() const;
    bool IsInFrustum(vec3 const &);

    //bool IsInFrustum(IControlObject*);
    //bool IsInFrustum(IModelObject*, int);
    //bool GetObjectsInFrustum(ttl::vector<IControlObject*>*, float);

    vec3 const GetOnScreenPoint(int, int);
    vec3 const GetOnScreenPointF(float, float);
    vec3 const GetOnScreenVector(int, int);
    vec2 const PointToScreen(vec3 const &);
    vec3 const PointToScreenClampToFrustum(vec3 const &);
    vec3 GetListenerOffset() const;
    void SetListenerOffset(vec3 const &);
    void SetOrthoView(ECameraMode::TYPE);
    void SetShakeable(bool);
    virtual ~IBaseCamera();

    /*
    virtual void FromForwardUpPos(vec3 const&, vec3 const&, vec3 const&);
    virtual void OnActivate();
    virtual void OnAttachedToView(CLevelView*);
    virtual void OnDeactivate();
    virtual void OnDetachedFromView(CLevelView*);
    virtual void SetEngineObject(CGSObject*);
    */
    CBaseCamera *m_CBC;
    char _pad[0x40];

};
static_assert(sizeof(IBaseCamera) == 0x50u);