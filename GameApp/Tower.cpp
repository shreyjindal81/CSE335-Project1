#include "pch.h"
#include "Tower.h"
#include "Game.h"
#include "Tile.h"

using namespace std;
using namespace Gdiplus;


/**
*  Destructor
*/
CTower::CTower(CGame* game) : CItem(game)
{
	CItem::SetDrag();
}



/**
*  Destructor
*/
CTower::~CTower()
{
}

