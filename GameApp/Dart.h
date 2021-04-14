/**
 * \file Dart.h
 *
 * \author Shizuka
 *
 * Class that represents a Dart
 *
 */

#pragma once
#include "pch.h"
#include "Item.h"

/**
*  Class that represents the dart that runs on the gameboard
*/
class CDart : public CItem
{
public:
	virtual ~CDart(); 

	CDart(CGame* game);  

	CDart() = delete; ///< default constructor deleted

	CDart(const CDart&) = delete; ///< shallow copy deleted

	/// Accepts CItemVisitor visitor
	///\param visitor being accepted 
	virtual void Accept(CItemVisitor* visitor) {};  

	/// Accepts CTowerLister visitor
	///\param visitor being accepted
	///\returns true if item is a dart 
	virtual bool Accept(CTowerLister* visitor) { return true; } 

	virtual void Update(double elapsed) override;

	void Draw(Gdiplus::Graphics* graphics); 
	
	/// Sets mean location for the dart
	///\param x coordinate
	///\param y coordinate
	virtual void SetLocation(double x, double y) { mCentre = y; CItem::SetLocation(x, y); }; ///< location setter with motion centre

	/// Sets immidiate location for the dart
	///\param x coordinate
	///\param y coordinate
	virtual void SetLoc(double x, double y) { CItem::SetLocation(x, y); }; 

	virtual void GetTip(double& x, double& y) ; 

	/// Sets the mirror value for the dart
	///\param boolValue
	virtual void SetMirror(bool boolValue) { mMirror = boolValue; };  

	/// Accepts CDArtBalloon visitor
	///\param visitor being accepted
	///\returns 1 if item is a dart 
	virtual int Accept(CDartBalloonVisitor* visitor) { return 1; }

	/// Sets the Placed value for the dart
	///\param boolValue
	virtual void SetPlaced(bool boolValue) { mPlaced = boolValue; }; 

	/// gets the mCentre value for the dart
	///\returns double mCentre 
	virtual double GetCentre() { return mCentre; };  

private:
	double mCentre{}; ///< centre for vertical motion of dart
	int mSpeedX = 50; ///< horizontal speed component
	int mSpeedY = 50; ///< vertical speed component
	bool mMirror = false; ///< check for dart direction
	bool mPlaced = false; ///< checks if dart has been placed on board
};
