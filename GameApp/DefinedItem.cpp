/**
 * \file DefinedItem.cpp
 *
 * \author Shizuka
 *
 */
#include "pch.h"
#include "DefinedItem.h"


CDefinedItem::CDefinedItem(const std::shared_ptr<xmlnode::CXmlNode>& node)
{
	mId = node->GetAttributeValue(L"id", L"");
	mImage = node->GetAttributeValue(L"image", L"");
}

