/**
 * \file RoadTile.h
 *
 * \author Shizuka
 *
 * Class that represents the Road tiles in the game
 *
 */

#pragma once
#include "Tile.h"
#include "Game.h"
#include "Balloon.h"
#include <memory>
#include <utility>
#include "BlueBalloon.h"
/**
*  A Road tile
*/
class CRoadTile : public CTile
{
public:
    /// Constructor
    ///\param game Game of which this is part of
    CRoadTile(CGame* game);

    ///  Default constructor (disabled)
    CRoadTile() = delete;

    ///  Copy constructor (disabled)s
    CRoadTile(const CRoadTile&) = delete;

    ~CRoadTile(); ///< destructor

    /// function to erase a ballon on the tile
    ///\param balloon Balloon to be erased
    void EraseBalloon(std::shared_ptr<CBalloon> balloon); 

    void PlaceBalloonEW(std::shared_ptr<CBalloon> balloon);
    void PlaceBalloonNS(std::shared_ptr<CBalloon> balloon);
    void PlaceBalloonSE(std::shared_ptr<CBalloon> balloon);
    void PlaceBalloonSW(std::shared_ptr<CBalloon> balloon);
    void PlaceBalloonNE(std::shared_ptr<CBalloon> balloon);
    void PlaceBalloonNW(std::shared_ptr<CBalloon> balloon);

    
    /// Accept a visitor
    ///\param visitor The visitor we accept
    virtual void Accept(CItemVisitor* visitor) override { visitor->VisitRoad(this); }

    /// Setter of mAdjacentTile
    ///\param tile the value mAdjacetentTile is set to
    void SetAdjacentRoadTile(std::shared_ptr<CRoadTile> tile) { mAdjacentRoadTile = tile; }

    /// Setter of mTypeTile
    ///\param Type the value mTypeTile is set to
    void SetTypeTile(std::wstring Type) { mTypeTile = Type; }

    /// Adds balloon to mBalloons vector that holds all balloons
    ///\param Balloon The balloon added to the vector
    void AddBalloon(std::shared_ptr<CBalloon> Balloon) { mBalloons.push_back(Balloon); } 

    /// Getter of mTypeTile
    ///\returns mTypeTile Type of the tile
    std::wstring GetTypeTile() { return mTypeTile; } ///< getter for mTypeTile

    /// Getter of mTypeTile
    ///\returns mTypeTile Type of the tile
    std::wstring Getid() { return mTypeTile; }

    /// updates the animation of balloons on road tiles
    ///\param elapsed time counter 
    virtual void Update(double elapsed);

    /// Setter of mAllocate
    ///\param x the value mAllocate is set to
    void SetAllocate(int x) { mAllocate = x; }

    /// Getter of mAllocate
    ///\returns mAllocate value of mAllocate
    int Getallocate() { return mAllocate; }

    /// Getter of mAdjecentRoadTile
    ///\returns mAllocate Adjecent RoadTile
    std::shared_ptr<CRoadTile> GetRoadTileAdj() { return mAdjacentRoadTile; } ///< getter for mAdjacentRoadTile

    ///Adds a pumpkin with name blue balloon
    ///\param Balloon that is a pumpkin
    void AddBlueBalloon(std::shared_ptr<CBlueBalloon> Balloon) { mBalloons.push_back(Balloon); }

private:

    std::shared_ptr<CRoadTile> mAdjacentRoadTile = nullptr; ///< pointer that stores adjacent road tile
    std::wstring mTypeTile = L"i001"; ///< stores type of road tile
    int mAllocate = 0; ///< stores allocate value


    std::vector<std::shared_ptr<CBalloon> > mBalloons; ///< stores all red balloons
};