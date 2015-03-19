
// Game.h : main header file for the Game application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CGameApp:
// See Game.cpp for the implementation of this class
//

class CGameApp : public CWinApp
{
public:
	CGameApp();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CGameApp theApp;
