#pragma once
#include "pch.h"
#include "Dart.h"
#include "Game.h"




/**
 * Destructor
 */
CDart::~CDart()
{
}

/// Constructor
///\param game
CDart::CDart(CGame* game) : CItem(game)
{
	CItem::SetDrag();
}

/// overriden update function
///\param elapsed time since last call to update
void CDart::Update(double elapsed)
{
	if (mPlaced)
	{
		SetLoc(GetX() + mSpeedX * elapsed,
			GetY() + mSpeedY * elapsed);

		if (mSpeedX > 0 && GetX() >= 1000)
		{
			mSpeedX = -mSpeedX;
			SetMirror(mSpeedX < 0);
		}

		if (mSpeedY > 0 && GetY() >= 970)
		{
			mSpeedY = -mSpeedY;
		}

		if (mSpeedX < 0 && GetX() <= 0)
		{
			mSpeedX = -mSpeedX;
			SetMirror(mSpeedX < 0);
		}

		if (mSpeedY < 0 && GetY() <= 0)
		{
			mSpeedY = -mSpeedY;
		}

		if (mSpeedY > 0 && GetY() >= mCentre + 50)
		{
			mSpeedY = -mSpeedY;
		}

		if (mSpeedY < 0 && GetY() <= mCentre - 50)
		{
			mSpeedY = -mSpeedY;
		}
	}
}

/// overriden draw Function
///\param graphics
void CDart::Draw(Gdiplus::Graphics* graphics)
{
	double wid = mItemImage->GetWidth();
	double hit = mItemImage->GetHeight();
	if (!mPlaced)
	{

		if (mMirror)
		{
			graphics->DrawImage(mItemImage.get(),
				float(GetX() + wid), float(GetY() - hit),
				-(float)mItemImage->GetWidth()*2, (float)mItemImage->GetHeight()*2);
		}
		else
		{
			graphics->DrawImage(mItemImage.get(),
				float(GetX() - wid), float(GetY() - hit),
				(float)mItemImage->GetWidth() * 2, (float)mItemImage->GetHeight() * 2);
		}
	}
	else
	{
		if (mMirror)
		{
			graphics->DrawImage(mItemImage.get(),
				float(GetX() + wid / 2), float(GetY() - hit / 2),
				-(float)mItemImage->GetWidth(), (float)mItemImage->GetHeight());
		}
		else
		{
			graphics->DrawImage(mItemImage.get(),
				float(GetX() - wid / 2), float(GetY() - hit / 2),
				(float)mItemImage->GetWidth(), (float)mItemImage->GetHeight());
		}
	}
}

/// GetTip function gets coordinates of the tip of the dart, stores it in parameter
///\param x coordinate 
///\param y coordinate
void CDart::GetTip(double& x, double& y)
{
	y = GetY();
	if (!mMirror)
		x = GetX() + mItemImage->GetWidth() / 2;
	else
		x = GetX() - mItemImage->GetWidth() / 2;
}


