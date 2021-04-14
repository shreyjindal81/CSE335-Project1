/**
 * \file ChildView.h
 *
 * \author Shizuka
 *
 * Class that implements the child window our program draws in.
 *
 * The window is a child of the main frame, which holds this window, the menu bar, and the status bar.
 */


 // ChildView.h : interface of the CChildView class
 //
 // CChildView window


#pragma once
#include "Game.h"



/// The window is a child of the main frame, which holds this window, the menu bar, and the status bar.
class CChildView : public CWnd
{
public:
	/// constructor
	CChildView();

protected:
	/**
	* This function is called before the window is created.
	* \param cs A structure with the window creation parameters
	* \returns TRUE
	*/
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

public:
	virtual ~CChildView(); ///< destructor


protected:

	/**
	* This function is called to draw in the window.
	*
	* This function is called in response to a drawing message
	* whenever we need to redraw the window on the screen.
	* It is responsible for painting the window.
	*/
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
private:


	void AddBuilding(const std::wstring& file);
	void AddLandscape(const std::wstring& file);
	void AddTowerRing(const std::wstring& file, double x, double y);
	void AddTower8(const std::wstring& file, double x, double y);
	void AddTowerBomb(const std::wstring& file, double x, double y);
	void AddRoad(const std::wstring& file);
	void AddDart(const std::wstring& file);
	void AddSpecialDart(const std::wstring& file, int x, double y);
	void AddGoButton(const std::wstring& file, double x, double y);

	/// The Game
	CGame mGame;

	double mInitialGrabbedItemX = 0; ///< default x location of grabbed item
	double mInitialGrabbedItemY = 0; ///< starting y location of grabbed item


	bool mFirstDraw = true; ///< boolean variable to check if it's the first time drawing the game
	bool mGo = false; ///< boolean variable that stores whether a level has started
	long long mLastTime = 0;    ///< Last time we read the timer
	double mTimeFreq = 0;       ///< Rate the timer updates



	std::shared_ptr<CItem> mGrabbedItem; ///< a shared pointer to the grabbed item


	double mLvl1Elapsed = 0;  ///< Counter variable to store time elapsed in level 1
	double mLvl2Elapsed = 0;  ///< Counter variable to store time elapsed in level 2
	double mLvl3Elapsed = 0;  ///< Counter variable to store time elapsed in level 3
	double mLvl0Elapsed = 0;  ///< Counter variable to store time elapsed in level 0


	bool mOnClicklvl3 = false;  ///< Variable to check if the mfc option for level 3 is clicked
	bool mOnClicklvl2 = false;  ///< Variable to check if the mfc option for level 2 is clicked
	bool mOnClicklvl0 = false;  ///< Variable to check if the mfc option for level 0 is clicked


	int mLoadToggle3 = 0;  	///< It holds 1 for the duration of the level 3 begin popup, 0 otherwise
	int mLoadToggle2 = 0;  	///< It holds 1 for the duration of the level 2 begin popup, 0 otherwise
	int mLoadToggle1 = 0;  	///< It holds 1 for the duration of the level 1 begin popup, 0 otherwise
	int mLoadToggle0 = 0;  	///< It holds 1 for the duration of the level 0 begin popup, 0 otherwise

	int mCurrentLvl = 1; ///< stores current level number

public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnLevelsLevel0();
	afx_msg void OnLevelsLevel1();
	afx_msg void OnLevelsLevel2();
	afx_msg void OnLevelsLevel3();
	void LoadLevel1();
	void LoadLevel2();
	void LoadLevel3();
	void LoadLevel0();
	afx_msg void OnFileSaveas();
};

