/**
 * \file Tile.cpp
 *
 * \author Shizuka
 */

#include "pch.h"
#include "Tile.h"
#include "Game.h"

using namespace std;
using namespace Gdiplus;



/// The directory containing the file images
const std::wstring CTile::ImagesDirectory = L"images/";


/**
 *  Distance from center for inside of tiles.
 *
 * Our tiles are a diamond that is 64 pixels tall and 128 pixels
 * wide. So, if we take the distance from the center vertically and
 * double it, it would be as if we had a 64 by 64 diamond. The
 * "Manhattan distance" from the center would be no more than 64
 * in that case.
 */
const int InsideTolerance = 64;


CTile::CTile(CGame* game) : CItem(game)
{
    if (mTileSetRoadToggle == true) {
        SetRoadToggle(true);
    }
}


/**
*  Destructor
*/
CTile::~CTile()
{
}

/**
 *  Set the image file to draw
 * \param file The base filename. Blank files are allowed
 */
void CTile::SetImage(const std::wstring& file)
{
    this->CItem::SetImage(file);
    mFile = file;
}


/**
 *  Get any adjacent tile.
 *
 * Given a tile in the city, this determines if there is another
 * tile adjacent to it. The parameters dx, dy determine which direction
 * to look.
 *
 * The values for specific adjacencies (dx, dy, and direction):
 *    - -1 -1 Upper left
 *    - 1 -1 Upper right
 *    - -1 1 Lower left
 *    - 1 1 Lower right
 *
 * \param dx Left/right determination, -1=left, 1=right
 * \param dy Up/Down determination, -1=up, 1=down
 * \returns Adjacent tile or nullptr if none.
 */
std::shared_ptr<CItem> CTile::GetAdjacent(int dx, int dy)
{
    return GetGame()->GetAdjacent(this, dx, dy);
}
