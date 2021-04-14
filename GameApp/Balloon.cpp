/**
 * \file Balloon.cpp
 *
 * \author Shizuka
 *
 */


#include "pch.h"
#include "Item.h"
#include "Balloon.h"
#include "Game.h"
#include "RoadVisit.h"
#include "RoadTile.h"
using namespace std;


CBalloon::CBalloon(CGame* game) : CItem(game)
{
	CRoadVisit visitor2;
	this->Accept(&visitor2);

	auto RoadTile = visitor2.GetRoadTile();
	//SetLocation(RoadTile->GetX() - RoadTile->GetWidth() / 2, RoadTile->GetY());
}



/**
*  Destructor
*/
CBalloon::~CBalloon()
{
}


void CBalloon::Popped(int x)
{
	if (!mPopped) {
		CItem::mScoreboard->AddScore(x);
		mPopped = true;
	}
}

void CBalloon::Passed()
{
	mScoreboard->SubtractScore(1);
}
