#pragma once
#include <afxwin.h>

class CMFCApplicationApp : public CWinApp {
public:
    virtual BOOL InitInstance();
    virtual int ExitInstance();

    DECLARE_MESSAGE_MAP()
};