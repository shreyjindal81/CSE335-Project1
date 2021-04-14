/**
 * \file DefinedRoad.cpp
 *
 * \author Shizuka
 *
 */

#include "pch.h"
#include "DefinedRoad.h"

CDefinedRoad::CDefinedRoad(const std::shared_ptr<xmlnode::CXmlNode>& node) : CDefinedItem(node)
{
	mType = node->GetAttributeValue(L"type", L"");
}
