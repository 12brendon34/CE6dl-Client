//
// Created by Brendon on 2/7/2026.
//

#include "MFCApplication.h"
#include "MainFrame.h"
#include "Resource.h"

BEGIN_MESSAGE_MAP(CMFCApplicationApp, CWinApp)
END_MESSAGE_MAP()
CMFCApplicationApp theApp;

BOOL CMFCApplicationApp::InitInstance() {

    CWinApp::InitInstance();
    EnableTaskbarInteraction(FALSE);

    CFrameWnd* pFrame = new CMainFrame;
    if (!pFrame)
        return FALSE;

    m_pMainWnd = pFrame;
    // create and load the frame with its resources
    pFrame->LoadFrame(IDR_MAINFRAME, WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, nullptr, nullptr);

    pFrame->ShowWindow(SW_SHOW);
    pFrame->UpdateWindow();
    return TRUE;
}

int CMFCApplicationApp::ExitInstance()
{
    //TODO: handle additional resources you may have added
    return CWinApp::ExitInstance();
}