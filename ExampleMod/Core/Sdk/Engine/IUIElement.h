#pragma once
#include <pch.h>
#include "../TTL.h"
#include "../ChromeCommon.h"

#include "engine.h"
#include "IUIElementControl.h"

class UIBoundingBox {

};

class IUIEditorElement {

};

class IUIScreen {

};

class CUIElement {

};

class IUITextPresenter {

};

class IUIHtmlPresenter {

};

class IUIVisual {

};

class TouchPadEvent {

};

class CUIElementControl {

};

class SHtmlSource {

};

class __declspec(dllimport) IUIElement {
public:

	IUIElement();
	IUIElement(IUIElement const&);

	static CRTTI const* GetNativeClass();
	static void RegisterRTTI();

	void AddChild(IUIElement*);
	void AssureValid();
	void AttachToElement(IUIElement*);
	void ChildrenJumpToNamedFrame(ttl::string_base<char> const&, float);
	void ClearOriginalXuiClass();
	IUIElement* Clone(IUIElement*);
	vec3 ConvertPositionFromTopLeft(vec3);
	vec3 ConvertPositionToTopLeft(vec3);
	int CreateFromXuiString(ttl::string_base<char>, ttl::list<IUIElement*, ttl::allocator>&);
	void DebugLinesVisibility(bool, bool);
	void DeleteThis();
	void DeleteThisRecursive();
	void DetachFromParent();
	void FeedInstanceParameters(IUIElementControl*);
	void FillChildList(ttl::list<IUIElement*, ttl::allocator>&);
	IUIElement* FindElement(ttl::string_base<char> const&, bool);
	IUIElement* FindElementByPath(ttl::string_base<char> const&);
	void ForceSyncFrameData();
	float GetActualOpacity();
	unsigned char GetAnchor();
	UIBoundingBox GetBoundingBox();
	UIBoundingBox GetBoundingBoxParentCoord();
	int GetChildIndex(IUIElement*);
	IUIElement* GetChildren(int);
	int GetChildrenCount();
	IUIElementControl* GetControlOwner();
	IUIElementControl* GetControlParent();
	ttl::string_base<char> const GetDebugId(int) const;
	vec4 GetDebugLineColor();
	IUIEditorElement* GetEditorElement();
	IUIElement* GetElem(ttl::string_base<char> const&, bool);
	mtx34 GetGlobalTransform();
	void GetGlobalTransformForMask(mtx34&);
	IUIElementControl* GetInstanceOwner();
	quat GetLocalRotation() const;
	vec3 const& GetLocalScale() const;
	mtx34 GetLocalTransform();
	float GetMarginBottom() const;
	float GetMarginLeft() const;
	float GetMarginRight() const;
	float GetMarginTop() const;
	char GetMaskChannel() const;
	vec3 GetMousePos() const;
	ttl::string_base<char> GetNFNameById(int);
	IUIScreen* GetOwnerScreen() const;
	IUIElement* GetParent();
	vec3 GetPivot();
	vec3 GetPosForMask();
	ttl::string_base<char> GetRelativePathFrom(IUIElement*);
	vec3 GetRelativePos(unsigned char) const;
	vec3 GetRelativePos() const;
	vec3 GetRelativePosTopLeft() const;
	quat GetRotation() const;
	vec3 GetRotationVec3() const;
	float GetRotationX() const;
	float GetRotationY() const;
	float GetRotationZ() const;
	vec3 const& GetScale() const;
	vec3 GetScaledSizeForMask();
	vec3 GetSizeForMask();
	float GetSizeX() const;
	float GetSizeY() const;
	vec3 GetUnscaledPivot() const;
	vec3 GetUnscaledSize() const;
	float GetUnscaledSizeX() const;
	float GetUnscaledSizeY() const;
	ttl::string_base<char> GetXui();
	void HierarchyAssureValidPos();
	bool InExtents(vec3 const&);
	bool InExtents(float, float);
	bool InExtents(float, float, IUIElementControl*);
	bool IsActuallyVisible() const;
	bool IsAffectedByMaskChannel0() const;
	bool IsAffectedByMaskChannel1() const;
	bool IsHoldAspectRatio();
	bool IsInstanced();
	bool IsRoundPositionX() const;
	bool IsRoundPositionY() const;
	bool IsVisible() const;
	float JumpToNamedFrameElements(ttl::string_base<char> const&, float);
	void MouseToUILocalSpace(float, float, float&, float&);
	void MouseToUIScreenSpace(float, float, float&, float&);
	void Move(vec3 const&);
	void MoveBottom();
	void MoveToIndex(int);
	void MoveTop();
	void PointToGlobal(vec3&);
	void PointToLocal(vec3&);
	void PointToScreenSpace(vec3 const&, vec3&);
	void PositionToParentCenter(bool, bool, bool);
	void ReleaseHierarchy();
	void ResumeAnimateElements(ttl::string_base<char> const&);
	void ResumeAnimateElements(ttl::string_base<char> const&, float);
	void SetAnchor(unsigned char);
	void SetDebugLineOpacity(float);
	void SetEditorElement(IUIEditorElement*);
	void SetHoldAspectRatio(bool);
	void SetLogicSize(vec3 const&);
	void SetLogicSizeX(float);
	void SetLogicSizeY(float);
	void SetMarginBottom(float);
	void SetMarginLeft(float);
	void SetMarginRight(float);
	void SetMarginTop(float);
	void SetMaskChannel(char);
	void SetPivot(vec3 const&);
	void SetPos(vec3 const&);
	void SetRelativePos(vec3 const&);
	void SetRelativePos(vec3 const&, unsigned char);
	void SetRelativePosTopLeft(vec3 const&);
	void SetRotation(float, float, float);
	void SetRotation(quat);
	void SetRotationZ(float);
	void SetRoundPosition(bool);
	void SetRoundPositionX(bool);
	void SetRoundPositionY(bool);
	void SetScale(vec3 const&);
	void SetScale(float);
	void SetSizeX(float);
	void SetSizeY(float);
	void SetUnscaledPivot(vec3 const&);
	void SetUnscaledSizeX(float);
	void SetUnscaledSizeY(float);
	void SetVisible(bool);
	void ShowDebugLine(bool);
	CUIElement* ToCUIElement() const;
	void UpdateChannelsMask();
	ttl::string_base<char> ValidateId(ttl::string_base<char> const&);
	void VectorToGlobal(vec3&);
	void VectorToLocal(vec3&);

	/*
	virtual ~IUIElement();
	virtual bool CanGroup() const;
	virtual bool CanUseClipMasks() const;
	virtual void Delete();
	virtual void GetBoundingBox(vec3&, vec3&);
	virtual IUIElement* GetClipMaskSource();
	virtual CRTTI const* GetEngineRTTI() const;
	virtual int GetNFIdByName(ttl::string_base<char> const&);
	virtual float GetOpacity() const;
	virtual vec3 GetPos() const;
	virtual CRTTI const* GetRTTI() const;
	virtual vec3 GetSize() const;
	virtual void Hide();
	virtual void HideScreen();
	virtual void HideScreen(bool);
	virtual void HideScreenEditor();
	virtual void HideScreenEditor(bool);
	virtual bool IsAARectangle() const;
	virtual bool IsControl() const;
	virtual bool IsImage() const;
	virtual bool IsSmartText() const;
	virtual bool IsText() const;
	virtual void OnAffectingMaskChannelChange();
	virtual void OnAttachChild(IUIElement*);
	virtual void OnChildAttachedChild(IUIElement*);
	virtual void OnChildHide(IUIElement*);
	virtual void OnChildOrderChange(IUIElement*);
	virtual void OnChildResize(IUIElement*);
	virtual void OnChildShow(IUIElement*);
	virtual void OnDebugRender();
	virtual void OnDetachChild(IUIElement*);
	virtual void OnEditorElementDeleted(IUIElement*);
	virtual void OnHide();
	virtual void OnParentHide(IUIElement*);
	virtual void OnParentShow(IUIElement*);
	virtual void OnPostUpdateHierarchy();
	virtual void OnPostUpdateHierarchyEditor();
	virtual void OnRender();
	virtual void OnResize();
	virtual void OnShow();
	virtual void SetEngineObject(gui::CObject*);
	virtual void SetObjectProperties(IUIElement*);
	virtual void SetOpacity(float);
	virtual void SetSize(vec3 const&);
	virtual void SetUnscaledSize(vec3 const&);
	virtual void Show(*);
	virtual void ShowScreen(IUIData*);
	virtual void ShowScreenEditor(IUIData*);
	virtual ttl::string_base<char> toString();
	*/
};