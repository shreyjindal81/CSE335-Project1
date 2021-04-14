/**
 * \file TileGrass.h
 *
 * \author Shizuka
 *
 * Class that represents the grass tiles
 *
 */

#pragma once
#include "Tile.h"

/// Class the represents the grass tiles
class CTileGrass :
    public CTile
{
public:
    /// Constructor
    ///\param game The game this is a part of
    CTileGrass(CGame* game);

    ///  Default constructor (disabled)
    CTileGrass() = delete;

    ///  Copy constructor (disabled)
    CTileGrass(const CTileGrass&) = delete;

    /// Destructor
    ~CTileGrass();

    virtual std::shared_ptr<xmlnode::CXmlNode> XmlSave(const std::shared_ptr<xmlnode::CXmlNode>& node) override;
    virtual void XmlLoad(const std::shared_ptr<xmlnode::CXmlNode>& node);

    /** Accept a visitor
    * \param visitor The visitor we accept */
    virtual void Accept(CItemVisitor* visitor) override { visitor->VisitGrass(this); }
};

