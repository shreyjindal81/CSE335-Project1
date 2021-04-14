/**
 * \file Tower.h
 *
 * \author Shizuka
 *
 * Class that represents the Dart Towers
 *
 */

#pragma once

#include "Dart.h"
#include "Tower8.h"
#include "Game.h"
#include "Item.h"
#include <memory>

/// Class the represents the Dart towers in the game
class CTowerDart : public CItem
{
public:

	/// Constructor
	///\param game The game this is a member of
	///\param x x location of Dart Tower
	///\param y y location of Dart Tower
	///\param angle Angle of the darts
	CTowerDart(CGame* game, double x, double y, double angle);

	/// Accept a visitor
	///\param visitor The visitor we accept
	virtual void Accept(CItemVisitor* visitor) override {};

	/// Destructor
	~CTowerDart() {}

	/// Sets mRelease to true
	void Release() { mRelease = true; }


	void CTowerDart::Draw(Gdiplus::Graphics* graphics, double offsetX, double offsetY);

	/// Getter of mAngle
	///\returns mAngle The nagle of a dart
	double GetAngle() { return mAngle; }

	/// Checks if any balloon's location is in pop range of the tip of the dart
	///\returns trueth value of whther balloon should be popped
	virtual bool WillPop(double, double) override;
private:

	CGame* mGame; ///<Classpointer object to CGame
	double mAngle; ///< angle of the darts
	bool mRelease; ///< true or false of releasing darts

};

