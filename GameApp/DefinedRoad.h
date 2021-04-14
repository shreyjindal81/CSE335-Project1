/**
 * \file DefinedRoad.h
 *
 * \author Shizuka
 *
 * Class that holds the definitions of the road tiles
 *
 */

#pragma once
#include "DefinedItem.h"

/// Class that holds the definitions of the road tiles
class CDefinedRoad : public CDefinedItem
{
public:
	/// Constructor
	/// defines road by taking a node
	///\param node XmlNode shared pointer containing declaration/definition of the road
	CDefinedRoad(const std::shared_ptr<xmlnode::CXmlNode>& node);

	/// Getter of mType
	///\returns mType Type of the road
	std::wstring GetType() { return mType; }
private:
	/// type of road
	std::wstring mType; ///< stores type of road tile
};

