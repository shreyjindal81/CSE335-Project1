#include "pch.h"
#include "Tower8.h"
#include "TowerDart.h"
#include <cmath>

using namespace std;

/// overriden update function
///\param elapsed time since last call to update
void CTower8::Update(double elapsed)
{


	if (mPlaced)
	{
		mTimeRelease -= elapsed;
		double TimeBetweenRelease = 5;

		int wid = GetWidth();
		int hit = GetHeight();
		if (mDartList.empty()) { AddDarts(); }
		if (mTimeRelease <= 0) {

			mRelease = true;
			mTimeRelease += TimeBetweenRelease;
			//ReleaseDart();
		}

		if (mRelease)
		{


			mT += 200 * elapsed;

			if (mT > 90)
			{
				mRelease = false;
				mDartList.clear();

				mT = 10;
			}
			else
			{
				for (auto dart : mDartList)
				{

					double a = dart->GetAngle();
					double sn = sin(a);
					double cs = cos(a);

					double x = GetX() + cs * mT;
					double y = GetY() + sn * mT;

					dart->SetLocation(x, y);
				}
			}
		}
	}
}
/// Constructor
CTower8::CTower8(CGame* game) : CTower(game)
{
	mTimeRelease = 5;
	mT = 10;
	AddDarts();
	mRelease = false;
}
/// Destructor
CTower8::~CTower8()
{
}

/// overriden draw Function
///\param graphics
void CTower8::Draw(Gdiplus::Graphics* graphics)
{
	CItem::Draw(graphics);
	if (mRelease)
	{
		for (auto item : mDartList)
		{
			item->Draw(graphics, (cos(item->GetAngle()) * mT), (sin(item->GetAngle()) * mT));

		}
	}
}

/// adds darts in order to start the explosion
void CTower8::AddDarts()
{
	for (double i = 0; i < 8; i++)
	{
		double pi = 2 * acos(0.0);   // this is the value for pi

		double angle = pi * (i / 4);
		// CDart(angle, position(getter x,y) , mGame ) 
		shared_ptr<CTowerDart> dart = make_shared<CTowerDart>(GetGame(), GetX(), GetY(), angle);
		mDartList.push_back(dart);
	}

}

/// delete
///\param dart
void CTower8::DeleteDart(std::shared_ptr<CTowerDart> dart)
{
	auto loc = find(::begin(mDartList), ::end(mDartList), dart);
	if (loc != ::end(mDartList))
	{
		mDartList.erase(loc);
	}
}

/// will pop turns to true when we want to pop
///\param x X location of dart popping balloon
///\param y Y location of dart popping balloon
///\returns a bool value of whether balloon should be popped
bool CTower8::WillPop(double x, double y)
{
	for (auto dart : mDartList)
	{
		if (dart->WillPop(x, y) && mRelease)
		{
			return true;
		}
	}
	return false;
}

