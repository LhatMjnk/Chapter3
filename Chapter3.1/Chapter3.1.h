
// Chapter3.1.h : main header file for the Chapter3.1 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CChapter31App:
// See Chapter3.1.cpp for the implementation of this class
//

class CChapter31App : public CWinApp
{
public:
	CChapter31App() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CChapter31App theApp;
