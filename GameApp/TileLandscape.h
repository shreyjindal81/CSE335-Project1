/**
* \file TileLandscape.h
*
* \author Shizuka
*  Class that implements a Landscape tile
*/

#pragma once

#include "Tile.h"


/**
*  A Landscape tile
*/
class CTileLandscape : public CTile
{
public:
    /// Constructor
    ///\param game The game this is a part of
    CTileLandscape(CGame* game);

    ///  Default constructor (disabled)
    CTileLandscape() = delete;

    ///  Copy constructor (disabled)
    CTileLandscape(const CTileLandscape&) = delete;

    /// Destructor
    ~CTileLandscape();

    virtual std::shared_ptr<xmlnode::CXmlNode> XmlSave(const std::shared_ptr<xmlnode::CXmlNode>& node) override;
    virtual void XmlLoad(const std::shared_ptr<xmlnode::CXmlNode>& node);

    /** Accept a visitor
* \param visitor The visitor we accept */
    virtual void Accept(CItemVisitor* visitor) override { visitor->VisitLandscape(this); }
};

