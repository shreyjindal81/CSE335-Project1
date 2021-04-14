/**
 * \file DefinedItem.h
 *
 * \author Shizuka
 *
 * Class that holds the definitions of the items
 * 
 */
#pragma once
#include "XmlNode.h"

/// Class that holds the definitions of the items
class CDefinedItem
{
public:

	/// constructor
	/// defines item by taking a node
	///\param node XmlNode shared pointer containing declaration/definition of the item
	CDefinedItem(const std::shared_ptr<xmlnode::CXmlNode>& node);

	/// Getter of mId
	///\returns mId Id of the item
	std::wstring GetId() { return mId; }

	/// Getter of mImage
	///\returns mImage Image of the item
	std::wstring GetImage() { return mImage; }

private:
	
	std::wstring mId; ///< stores Id of item
	std::wstring mImage; ///< stores Image tag of item
};

