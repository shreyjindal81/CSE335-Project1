#include "pch.h"
#include "TowerBomb.h"
#include <math.h>

using namespace Gdiplus;
using namespace std;

/// Offset value
double BlastOffset = 100;

/// Constructor
///\param game
CTowerBomb::CTowerBomb(CGame* game) : CTower(game)
{
	mTimeInExplode = 1000;
	mTimeBetweenExplodes = mTimeInExplode;
	mTimeAfterExplode = 0;
	mBlast = false;
}

/// overriden update function
///\param elapsed time since last call to update
void CTowerBomb::Update(double elapsed)
{
	if (GetIndex() != 0)
	{
		if (mTimeInExplode == 1000)
		{
			mTimeInExplode = GetIndex() * 3;
		}
		if (!mBlast) {
			mTimeInExplode -= elapsed;
			if (mTimeInExplode <= 0)
			{
				mTimeInExplode = mTimeBetweenExplodes;
				Blast();
			}
		}
		else
		{
			mTimeAfterExplode += elapsed;
		}
	}
}

/// sets mBlast to true in order to start the explosion
void CTowerBomb::Blast()
{
	mBlast = true;
}

/// overriden draw Function
///\param graphics
void CTowerBomb::Draw(Graphics* graphics)
{
	if (mBlast)
	{
		if (mTimeAfterExplode < 0.25)
		{
			SolidBrush brush(Color(128, 0, 0));
			graphics->FillEllipse(&brush, (int)GetX()- (int)BlastOffset, (int)GetY()-(int)BlastOffset, 200, 200);
		}
	}
	else
	{
		CTower::Draw(graphics);
	}
}

/// Sets the index 
///\param index the new index number
void CTowerBomb::SetIndex(int index)
{
	CTower::SetIndex(index);

}

/// Checks if a balloon at a certain will pop due to this tower or not
///\param x coordinate
///\param y coordinate
///\returns true if balloon can be popped, false otherwise
bool CTowerBomb::WillPop(double x, double y)
{
	double distance = 1000;
	bool condition = sqrt(pow((GetX() - x), 2.0) + pow((GetY() - y), 2.0)) < 100;
	return (mBlast && condition);
}
