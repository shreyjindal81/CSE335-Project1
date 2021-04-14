/**
 * \file GoButton.h
 *
 * \author Shizuka
 *
 * Class that represents the Go Button in the game
 *
 */

#pragma once
#include "Game.h"
#include "Item.h"
#include "Tile.h"

/**
*  The Go Button that begins a level
*/
class CGoButton: public CItem
{
public:
    CGoButton(CGame* game); ///< constructor

    ///  Default constructor (disabled)
    CGoButton() = delete;

    ///  Copy constructor (disabled)
    CGoButton(const CGoButton&) = delete;

    ~CGoButton(); ///< destructor


    /** Accept a visitor
    * \param visitor The visitor we accept
    */
    virtual void Accept(CItemVisitor* visitor) { visitor->VisitGo(this); };

};