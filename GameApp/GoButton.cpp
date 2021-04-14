#include "pch.h"
#include "GoButton.h"
#include "Game.h"
#include "Tile.h"

using namespace std;
using namespace Gdiplus;


/** Constructor
* \param game The game this is a member of
*/
CGoButton::CGoButton(CGame* game) : CItem(game)
{
}



/**
*  Destructor
*/
CGoButton::~CGoButton()
{
}