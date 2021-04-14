#include "pch.h"
#include "TowerRing.h"

#include <math.h>

using namespace Gdiplus;
using namespace std;

/// Initialises a ring tower
///\param game in which tower is to be added
CTowerRing::CTowerRing(CGame* game) : CTower(game)
{
}

/// overridden update function, updates tower
///\param elapsed time since last elapsed
void CTowerRing::Update(double elapsed)
{
	if (mPlaced)
	{
		if (mTimeBetweenRing == 1000)
		{
			mTimeBetweenRing = 5;
		}
		mTimeBetweenRing -= elapsed;
		if (!mRing) {
			if (mTimeBetweenRing <= 0)
			{
				mTimeBetweenRing = mInterval;
				Ring(true);
			}
		}
		if(mRing)
		{
			mTimeAfterRing += elapsed;
			mRadius = mSpeed * mTimeAfterRing;
		}
		if (mRadius >= 100)
		{
			Ring(false);
			mRadius = 0;
			mTimeAfterRing = 0;
		}
	}
}

/// Starts the ring process
///\param ring
void CTowerRing::Ring(bool ring)
{
	mRing = ring;
}

/// Checks if a balloon at a certain will pop due to this tower or not
///\param x coordinate
///\param y coordinate
///\returns true if balloon can be popped, false otherwise
bool CTowerRing::WillPop(double x, double y)
{
	double lowerLim = mRadius - 24;
	double upperLim = mRadius + 24;
	double distance = sqrt(pow((GetX() - x), 2.0) + pow((GetY() - y), 2.0));
	bool condition1 = distance < upperLim;
	bool condition2 = distance > lowerLim;
	return (mRing && condition1 && condition2);
}

/// Overriden draw function to accomodate
///\param graphics
void CTowerRing::Draw(Graphics* graphics)
{

	
	if (mRadius != 0)
	{
		Pen brush(Color(128, 0, 0));
		graphics->DrawEllipse(&brush, float(GetX() - mRadius), float(GetY() - mRadius), float(2*mRadius), float(2*mRadius));
	}

	CTower::Draw(graphics);

}


