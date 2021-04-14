/**
 * \file Tower.h
 *
 * \author Shizuka
 *
 * Class that represents the towers
 *
 */

#pragma once
#include "Game.h"
#include "Item.h"
#include "Tile.h"




/// Class that represents the towers in the game i.e. Dart, Ring and Bomb.
class CTower : public CItem
{
public:
    /// Constructor
    ///\param game The game this is a member of
    CTower(CGame* game);

    ///  Default constructor (disabled)
    CTower() = delete;

    ///  Copy constructor (disabled)
    CTower(const CTower&) = delete;

    virtual ~CTower();


    /** Accept a visitor
    * \param visitor The visitor we accept */
    virtual void Accept(CItemVisitor* visitor) {};

    /// <summary>
    /// accept function
    /// </summary>
    /// <param name="visitor"></param>
    /// <returns>bool</returns>
    virtual bool Accept(CTowerLister* visitor) { return true; }

    /// <summary>
    /// inddex setter
    /// </summary>
    /// <param name="index"></param>
    virtual void SetIndex(int index) override { mIndex = index; }

    /// <summary>
    /// index getter
    /// </summary>
    /// <returns></returns>
    virtual int GetIndex() { return mIndex; }

    /// <summary>
    /// accept function for tower
    /// </summary>
    /// <param name="visitor"></param>
    /// <returns></returns>
    virtual bool Accept(CTowerVisit* visitor) { return true; }
private:

    /// <summary>
    /// memeber variable.
    /// </summary>
    int mIndex = 0;
};