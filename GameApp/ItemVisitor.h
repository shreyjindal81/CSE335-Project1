/**
 * \file ItemVisitor.h
 *
 * \author Shizuka
 *
 * Visitor class to the items in the game
 *
 */

#pragma once

class CTileBuilding;
class CTileLandscape;
class CRoadTile;
class CTileGrass;
class CTile;
class CGoButton;


/// Visitor class to the items in the game
class CItemVisitor
{
public:
    virtual ~CItemVisitor() {} ///< destructor

    /** Visit a CTileBuilding object
     * \param building Building we are visiting */
    virtual void VisitBuilding(CTileBuilding* building) {}

    /** Visit a CTileLandscape object
    * \param landscape Landscape tile we are visiting */
    virtual void VisitLandscape(CTileLandscape* landscape) {}

    /** Visit a CTileRoad object
    * \param road Road we are visiting */
    virtual void VisitRoad(CRoadTile* road)  {}

    /** Visit a CTileGrass object
    * \param grass Grass are visiting */
    virtual void VisitGrass(CTileGrass* grass) {}

    /** Visit a CGoButton object
    * \param go go button we are visiting */
    virtual void VisitGo(CGoButton* go) {}

};

