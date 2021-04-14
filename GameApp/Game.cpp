/**
 * \file Game.cpp
 *
 * \author Shizuka
 *
 * Class the represents the Game
 *
 */

#include "pch.h"
#include <algorithm>
#include <vector>
#include "Item.h"
#include "Game.h"
#include "Tile.h"
#include "TileLandscape.h"
#include "TileBuilding.h"
#include <iostream>
#include "XmlLoader.h"
#include "Score.h"
#include "Balloon.h"
#include "Dart.h"
#include "DartBalloonVisitor.h"
#include "BombCounter.h"
#include "RoadVisit.h"
#include "RoadTile.h"
#include "BlueBalloon.h"

using namespace std;
using namespace xmlnode;
using namespace Gdiplus;


/// constructor
CGame::CGame()
{
    mScorekeeper = make_shared<CScore>();
}

/// destructor
CGame::~CGame()
{
}

/// Function that gets called when drawn
///\param graphics
///\param width
///\param height
void CGame::OnDraw(Gdiplus::Graphics* graphics, int width, int height)
{
    Gdiplus::SolidBrush brush(Gdiplus::Color::Black);
    graphics->FillRectangle(&brush, 0, 0, width, height);

    //
    // Automatic Scaling
    //
    float scaleX = float(width) / float(Width);
    float scaleY = float(height) / float(Height);
    mScale = min(scaleX, scaleY);

    // Ensure it is centered horizontally
    mXOffset = (float)((width - Width * mScale) / 2);

    // Ensure it is centered vertically
    mYOffset = (float)((height - Height * mScale) / 2 + 32);

    graphics->TranslateTransform(mXOffset, mYOffset);
    graphics->ScaleTransform(mScale, mScale);

    for (auto item : mItems)

    {
        if (item->GetItemToggle() == true)
        {
            item->Draw(graphics);

        }

    }

    CTowerLister visitor;
    std::vector<std::shared_ptr<CItem>> list = Accept(&visitor);
    for (auto tower : list) {
        MoveToFront(tower);
    }
    mScorekeeper->Draw(graphics);
    mBalloonOnScreen = mScorekeeper->GetBalloonCount();
}

/// this function draws the popups at beginning of level
///\param graphics
///\param level
void CGame::BeginPopup(Gdiplus::Graphics* graphics, std::wstring level)
{
    const WCHAR* out = level.c_str();
    mTemp.Draw(graphics, out);

}
/// makes required changes when new level is started
void CGame::NextLvl()
{
    mScorekeeper->SetBalloonCount(0);
    mBalloonOnScreen = 0;
}

/// Adds Item from parameter to the game items list
///\param item
void CGame::Add(std::shared_ptr<CItem> item)
{
    mItems.push_back(item);
    item->SetKeeper(mScorekeeper);
}


/// runs hittest on all items in game
///\param x 
///\param y
///\returns std::shared_ptr<CItem> that was hit on
std::shared_ptr<CItem> CGame::HitTest(double x, double y)
{
    for (auto i = mItems.rbegin(); i != mItems.rend(); i++)
    {
        if ((*i)->HitTest(x, y))
        {
            return *i;
        }
    }

    return  nullptr;
}


/// function that finds the nearest grass from a given point
///\param x
///\param y 
///\returns std::shared_ptr<CItem> 
std::shared_ptr<CItem> CGame::NearestGrass(double x, double y)
{
    double lowDis = 1000;
    std::shared_ptr<CItem> closest = nullptr;
    for (auto i = mItems.rbegin(); i != mItems.rend(); i++)
    {
        if ((*i)->GetType() == L"grass") {
            double dx = x - (*i)->GetX();
            double dy = y - (*i)->GetY();
            auto distance = sqrt(dx * dx + dy * dy);
            if ((distance <= lowDis) && (distance < 50)) {
                lowDis = distance;
                closest = *i;
            }
        }

    }

    return closest;

}


/// brings the item passed to the front of the list
///\param item
void CGame::MoveToFront(std::shared_ptr<CItem> item)
{

    auto loc = find(::begin(mItems), ::end(mItems), item);
    if (loc != ::end(mItems))
    {
        mItems.erase(loc);
    }

    mItems.push_back(item);
}

/// function that deleted the passed object
///\ param item
void CGame::DeleteItem(std::shared_ptr<CItem> item)
{
    auto loc = find(::begin(mItems), ::end(mItems), item);
    if (loc != ::end(mItems))
    {
        mItems.erase(loc);
    }
}

/// function that calls the time based changes to items
///\param elapsed time 
void CGame::Update(double elapsed)
{
    std::vector <std::shared_ptr <CItem>> balloons;
    std::vector <std::shared_ptr <CItem>> darts;
    std::vector <std::shared_ptr <CItem>> towers;
    CDartBalloonVisitor visitor;
    CTowerVisit counter;
    for (auto item : mItems)
    {
        item->Update(elapsed);
        if (item->Accept(&visitor) == 2)
        {
            balloons.push_back(item);
        }

        if (item->Accept(&visitor) == 1)
        {
            darts.push_back(item);
        }
        if (item->Accept(&counter))
        {
            towers.push_back(item);
        }
    }
    for (auto tower : towers)
    {
        for (auto balloon : balloons)
        {
            if (tower->WillPop(balloon->GetX(), balloon->GetY()))
            {
                CBombCounter visitorBomb;
                if (tower->Accept(&visitorBomb)) {
                    balloon->Popped(2);
                }
                CRingVisitor visitorRing;
                if (tower->Accept(&visitorRing)) {
                    balloon->Popped(3);
                }
                else {
                    balloon->Popped(10);
                }
                DeleteItem(balloon);
            }
        }

        if (tower->GetTimeAfterExplode() >= 0.25)
        {
            DeleteItem(tower);
        }
    }
    for (auto dart : darts)
    {
        double x; double y;
        dart->GetTip(x, y);
        for (auto balloon : balloons)
        {
            if (balloon->HitTest(x, y))
            {
                balloon->Popped(7);
                DeleteItem(balloon);
            }
        }

    }

    CRoadVisit visitor2;
    this->Accept(&visitor2);


    auto RoadTile = visitor2.GetRoadTile();


    mtBalloon += (1.6) * (0.2);

    if (mtBalloon >= 1 && mBalloonIntroduced < 30) {


        if (mLevel3 != true) {
            auto tile = make_shared<CBalloon>(this);
            tile->SetImage(L"red-balloon.png");
            RoadTile->AddBalloon(tile);
            tile->SetLocation(RoadTile->GetX() - RoadTile->GetWidth() / 2, RoadTile->GetY());
            mItems.push_back(tile);
            tile->SetKeeper(mScorekeeper);
            mtBalloon = 0;
            mBalloonIntroduced++;
        }
        else {
            if (mBalloonIntroduced == 12 || mBalloonIntroduced == 21 || mBalloonIntroduced == 27 || mBalloonIntroduced == 20 || mBalloonIntroduced == 2 || mBalloonIntroduced == 19) {
                auto tile = make_shared<CBlueBalloon>(this);
                tile->SetImage(L"blue-balloon.png");

                RoadTile->AddBlueBalloon(tile);
                tile->SetLocation(RoadTile->GetX() - RoadTile->GetWidth() / 2, RoadTile->GetY());
                mItems.push_back(tile);
                tile->SetKeeper(mScorekeeper);
                mtBalloon = 0;
                mBalloonIntroduced++;
            }
            else {

                auto tile = make_shared<CBalloon>(this);
                tile->SetImage(L"black-balloon.png");
                RoadTile->AddBalloon(tile);
                tile->SetLocation(RoadTile->GetX() - RoadTile->GetWidth() / 2, RoadTile->GetY());
                mItems.push_back(tile);
                tile->SetKeeper(mScorekeeper);
                mtBalloon = 0;
                mBalloonIntroduced++;
            }

        }


    }
}




/**  Load the city from a .XML file.
*
* Opens the XML file and reads the nodes, creating items as appropriate.
*
* \param filename The filename of the file to load the level from.
*/
void CGame::XmlLoad(std::wstring& filename)
{
    try
    {
        shared_ptr<CXmlNode> root = xmlnode::CXmlNode::OpenDocument(filename);
        mXmlLoader = make_shared<CXmlLoader>(root);
    }
    catch (CXmlNode::Exception ex)
    {
        cout << ex.Message().c_str() << endl;
    }

}




/**
*  Clear the item data.
*
* Deletes all known items in game.
*/
void CGame::Clear()
{
    mBalloonIntroduced = 0;
    mItems.clear();
}

/// sorts the tiles of the game 
void CGame::SortTiles()
{
    // sort using a lambda expression 
    sort(::begin(mItems), ::end(mItems),
        [](const shared_ptr<CItem>& a, const shared_ptr<CItem>& b) {
        if (a->GetY() < b->GetY())
            return true;

        if (a->GetY() > b->GetY())
            return false;

        return a->GetX() > b->GetX();
    });

    BuildAdjacencies();
}


/**
 *  Build support for fast adjacency testing.
 *
 * This builds a map of the grid locations of every tile, so we can
 * just look them up.
 */
void CGame::BuildAdjacencies()
{
    mAdjacency.clear();
    for (auto tile : mItems)
    {
        mAdjacency[pair<double, double>(tile->GetX() / GridSpacing,
            tile->GetY() / GridSpacing)] = tile;
    }
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
 * \param tile Tile to test
 * \param dx Left/right determination, -1=left, 1=right
 * \param dy Up/Down determination, -1=up, 1=down
 * \returns Adjacent tile or nullptr if none.
 */
std::shared_ptr<CItem> CGame::GetAdjacent(std::shared_ptr<CItem> tile, int dx, int dy)
{
    return GetAdjacent(tile.get(), dx, dy);
}

/**
 *  Get any adjacent tile.
 *
 * Identical to the other version, except this version accepts a
 * regular pointer instead of a shared_ptr. This allows the function
 * to be called from CItem, which only knows itself as a pointer.
 *
 * \param tile Tile to test
 * \param dx Left/right determination, -1=left, 1=right
 * \param dy Up/Down determination, -1=up, 1=down
 * \returns Adjacent tile or nullptr if none.
 */
std::shared_ptr<CItem> CGame::GetAdjacent(CItem* tile, int dx, int dy)
{
    double atX = tile->GetX() / GridSpacing + static_cast<unsigned __int64>(dx) * 2;
    double atY = tile->GetY() / GridSpacing + dy;

    auto adj = mAdjacency.find(pair<double, double>(atX, atY));
    if (adj != mAdjacency.end())
    {
        // We found it
        return adj->second;
    }

    return nullptr;
}

/** Accept a visitor for the collection
 * \param visitor The visitor for the collection
 */
void CGame::Accept(CItemVisitor* visitor)
{
    for (auto tile : mItems)
    {
        tile->Accept(visitor);
    }
}

///Accept a visitor for the collection
///\param visitor The visitor for the collection
///\returns int number of bombs
int CGame::Accept(CBombCounter* visitor)
{
    int numBombs = 0;
    for (auto tile : mItems)
    {
        if (tile->Accept(visitor)) {
            numBombs++;
        }
    }
    return numBombs;
}

///makes all items stationary, no longer dragable
void CGame::MakeStationary()
{
    for (auto item : mItems)
        item->SetDrag(false);
}


/** Accept a visitor for the collection
 * \param visitor The visitor for the collection
 * \returns list of all towers.
 */
std::vector<std::shared_ptr<CItem>> CGame::Accept(CTowerLister* visitor)
{
    std::vector<std::shared_ptr<CItem>> list;
    for (auto item : mItems)
    {
        if (item->Accept(visitor)) {
            list.push_back(item);
        }
    }
    return list;
}


void CGame::Save(const std::wstring& filename)
{   
}
