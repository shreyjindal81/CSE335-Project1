#include "pch.h"
#include "RoadVisit.h"
#include "RoadTile.h"
#include <memory>


void CRoadVisit::VisitRoad(CRoadTile* road)
{
	if (road->GetX()/64 == 0) {
		mX = (int)road->GetX();
		mY = (int)road->GetY();
		mToggle = 1;
		mTile = road;
	}

}
