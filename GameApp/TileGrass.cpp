#include "pch.h"
#include "TileGrass.h"

using namespace std;
using namespace Gdiplus;

/**
*  Constructor
*/
CTileGrass::CTileGrass(CGame* game) : CTile(game)
{
}

/**
*  Destructor
*/
CTileGrass::~CTileGrass()
{
}

/**  Save this item to an XML node
* \param node The node we are going to be a child of
* \returns Allocated node
*/
std::shared_ptr<xmlnode::CXmlNode> CTileGrass::XmlSave(const std::shared_ptr<xmlnode::CXmlNode>& node)
{
    auto itemNode = CTile::XmlSave(node);

    itemNode->SetAttribute(L"type", L"grass");
    itemNode->SetAttribute(L"file", GetFile());

    return itemNode;
}


/**
* brief Load the attributes for an item node.
* \param node The Xml node we are loading the item from
*/
void CTileGrass::XmlLoad(const std::shared_ptr<xmlnode::CXmlNode>& node)
{
    CTile::XmlLoad(node);
    SetImage(node->GetAttributeValue(L"file", L""));
}