/**
 * \file RoadVisit.h
 *
 * \author Shizuka
 *
 * Class (visitor) that visits the roads
 *
 */

#pragma once
#include "ItemVisitor.h"
#include <memory>

/// Visitor class that visits roads for necessary functions
class CRoadVisit :
    public CItemVisitor
{
public:
    /// Getter of mX
    ///\returns mX X location of Road Tile
    int Getx() { return mX; }
    
    /// Getter of mY
    ///\returns mY Y location of Road Tile
    int Gety() { return mY; }
    
    /// Getter of mTile
    ///\returns mTile Tile of the road
    CRoadTile* GetRoadTile() { return mTile; }
private:
    /// Visitor Setter
    ///\param road Attributes of which is set to class member attributes
    void VisitRoad(CRoadTile* road);

    
    /// Pointer object of CRoadTile class
    CRoadTile* mTile = nullptr;
    
    int mToggle = 0; ///< Toggle variable of the Road Tile

    int mX = 0; ///< X location of the Road Tile

    int mY = 0; ///< Y location of the Road Tile
};

