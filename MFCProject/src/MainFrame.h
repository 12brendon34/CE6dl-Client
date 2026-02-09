//
// Created by Brendon on 2/7/2026.
//

#pragma once
#include "ChildView.h"

class CMainFrame : public CFrameWnd {
public:
    virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
    CChildView    m_wndView;
protected:
    //DECLARE_DYNAMIC(CMainFrame)
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnSetFocus(CWnd *pOldWnd);
	DECLARE_MESSAGE_MAP();
};