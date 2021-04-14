/**
 * \file BlueBalloon.cpp
 *
 * \author Shizuka
 *
 */
#include "pch.h"
#include "BlueBalloon.h"
#include "Item.h"
#include "Game.h"
#include "RoadVisit.h"
#include "RoadTile.h"

using namespace std;

/// subtracts score if user pops the balloon
void CBlueBalloon::Popped()
{
	mScoreboard->SubtractScore(20);

}
/// Adds 50 bonus point for every blue balloon that is not popped
void CBlueBalloon::Passed()
{
	//The Blue Ballooon implemented in our level 3
	//Adds 50 points to the score if it passes unpopped
	//This is to make users think more and prevent overuse of towers
	mScoreboard->AddScore(50);
}
