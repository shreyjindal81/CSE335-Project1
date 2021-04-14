/**
 * \file Tile.h
 *
 * \author Shizuka
 *
 * Base class for any tile in our game
 */

#pragma once

#include <string>
#include <memory>
#include "XmlNode.h"
#include "Item.h"

/**
 * Base class for any tile in our city
 */
class CTile : public CItem
{
public:

    /// How much we offset drawing the tile to the left of the center
    const static int OffsetLeft = 64;

    /// How much we offset drawing the tile above the center
    const static int OffsetDown = 32;


/** The directory were the images are stored */
    static const std::wstring ImagesDirectory;

    /** The grid spacing in the city */
    static const int GridSpacing = 64;

    ///  Default constructor (disabled)
    CTile() = delete;

    ///  Copy constructor (disabled)
    CTile(const CTile&) = delete;


    ///  Destructor
    virtual ~CTile();


    /**  Get the file name for this tile image
     * \returns Filename or blank if none */
    std::wstring GetFile() { return mFile; }


    ///  Handle updates for animation
    /// \param elapsed The time since the last update
    virtual void Update(double elapsed) {}   


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
    std::shared_ptr<CItem> GetAdjacent(int dx, int dy);

    virtual void SetImage(const std::wstring& file);

    /// Setter of mTileSetRoadToggle
    ///\param b Sets the value of mTileSetRoadToggle to b
    void SetToggle(bool b) { mTileSetRoadToggle = b; }

    /// Constructor
    ///\param game The game this part of
    CTile(CGame* game);

    /// Accept a visitor
    ///\param visitor The visitor we accept
    virtual void Accept(CItemVisitor* visitor)  {};

private:

    /// The file for this item
    std::wstring mFile;

    /// Toggle for the Road Tile
    bool mTileSetRoadToggle = false;

};



