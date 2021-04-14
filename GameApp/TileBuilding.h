/**
* \file TileBuilding.h
*
* \author Shizuka
*
*  Class that implements a Building tile
*/

#pragma once

#include "Tile.h"

/**
*  A Building tile
*/
class CTileBuilding : public CTile
{
public:
    /// Constructor
    ///\param game The game this is a part of
    CTileBuilding(CGame* game);

    ///  Default constructor (disabled)
    CTileBuilding() = delete;

    ///  Copy constructor (disabled)
    CTileBuilding(const CTileBuilding&) = delete;

    /// Destructor
    ~CTileBuilding();

    virtual std::shared_ptr<xmlnode::CXmlNode> XmlSave(const std::shared_ptr<xmlnode::CXmlNode>& node) override;
    virtual void XmlLoad(const std::shared_ptr<xmlnode::CXmlNode>& node);

    /** Accept a visitor
    * \param visitor The visitor we accept */
    virtual void Accept(CItemVisitor* visitor) override { visitor->VisitBuilding(this); }
};

