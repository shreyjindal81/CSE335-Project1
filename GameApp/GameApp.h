/**
 * \file Tower.h
 *
 * \author Shizuka
 *
 * Class that implments the application of the game
 *
 */



// GameApp.h : main header file for the GameApp application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CGameAppApp:
// See GameApp.cpp for the implementation of this class
//

/// Class the that implements the game application
class CGameAppApp : public CWinApp
{
public:
	CGameAppApp() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()

private:
	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR gdiplusToken = 0;
};

extern CGameAppApp theApp;
