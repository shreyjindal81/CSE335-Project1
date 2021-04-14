#pragma once
#include "pch.h"
#include "TowerDart.h"

using namespace Gdiplus;

/// Constant to covert radians to degrees.
const double RtoD = 57.2957795;

/// Constructor
CTowerDart::CTowerDart(CGame* game, double x, double y, double angle) : CItem(game)
{
	CItem::SetImage(L"dart.png");
	CItem::SetDrag(false);

	CItem::SetLocation(x, y);

	mAngle = angle;
}



/**
 * Draw the rotated dart. Rotation is determined by the member
 * variable mAngle, which is the rotation in radians.
 *
 * @param graphics The graphics context to draw on.
 * @param offsetX An X offset added to the position of the dart.
 * @param offsetY A Y offset added to the position of the dart.
 */
void CTowerDart::Draw(Gdiplus::Graphics* graphics, double offsetX, double offsetY)
{
	double wid = GetWidth();
	double hit = GetHeight();
	auto save = graphics->Save();
	graphics->TranslateTransform((REAL)(GetX() + offsetX),
		(REAL)(GetY() + offsetY));
	graphics->RotateTransform((REAL)(mAngle * RtoD));
	//CItem::Draw(graphics);
	graphics->DrawImage(GetImage().get(), float(-wid / 2), float(-hit / 2), float(wid), float(hit));
	graphics->Restore(save);
}

bool CTowerDart::WillPop(double x, double y)
{

	double distance = sqrt(pow((GetX() - x), 2.0) + pow((GetY() - y), 2.0));

	return (distance <= 24);
}




