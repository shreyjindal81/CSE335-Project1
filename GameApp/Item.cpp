/**
*
*\file Item.cpp
*
* \ author Shizuka
*/


#include "pch.h"
#include "Item.h"
#include "Game.h"
#include <string>
#include <memory>
using namespace Gdiplus;
using namespace std;

/// the amount of tolerance for registering a hittest on an item
const int InsideTolerance = 64;

/// The directory containing the file images
const std::wstring CItem::ImagesDirectory = L"images/";

/**
 * Destructor
 */
CItem::~CItem()
{
}

/**
 * Draw our item
 * \param graphics The graphics context to draw on
 */
void CItem::Draw(Gdiplus::Graphics* graphics)
{
    double wid = mItemImage->GetWidth();
    double hit = mItemImage->GetHeight();


    graphics->DrawImage(mItemImage.get(),
        float(GetX() - wid / 2), float(GetY() - hit / 2),
        (float)mItemImage->GetWidth()+1, (float)mItemImage->GetHeight()+1);
}

/** Sets image of the item
* \param file containing image
*/
void CItem::SetImage(const std::wstring& file)
{
      //  std::wstring temp = file;
        wstring filename = ImagesDirectory + file;
        mItemImage = unique_ptr<Bitmap>(Bitmap::FromFile(filename.c_str()));
        if (mItemImage->GetLastStatus() != Ok)
        {
            wstring msg(L"Failed to open ");
            msg += filename;
            AfxMessageBox(msg.c_str());
            return;
        }
}

/** Deletes an item from the list of items in the game
* \param item pointer to the item that needs to be deleted
*/
void CItem::DeleteItem(std::shared_ptr<CItem> item)
{

    if (item != nullptr)
    {
        mGame->DeleteItem(item);
        item = nullptr;
    }

    
}

/** Constructor
* \param game the game item is a part of
*/
CItem::CItem(CGame* game) :
    mGame(game)
{
}



/**
 *  Force the tile to a regular grid by forcing the values to be multiples of 32.
 *
 * This version works correctly for negative coordinates.
 */
void CItem::QuantizeLocation()
{
    double spacing = CGame::GridSpacing;
    if (GetX() < 0)
    {
        SetX((int)(((GetX() + spacing / 2) / spacing) * spacing - spacing));
    }
    else
    {
        SetX((int)(((GetX() + spacing / 2) / spacing) * spacing));
    }

    if (GetY() < 0)
    {
        SetY((int)(((GetY() + spacing / 2) / spacing) * spacing - spacing));
    }
    else
    {
        SetY((int)(((GetY() + spacing / 2) / spacing) * spacing));
    }

}


bool CItem::HitTest(double x, double y)
{
    // Simple manhattan distance 
    return (abs(x - GetX()) + abs(y - GetY()) * 2) <= InsideTolerance;
}





/**  Save this item to an XML node
 * \param node The node we are going to be a child of
 * \returns Created XML node
 */
std::shared_ptr<xmlnode::CXmlNode> CItem::XmlSave(const std::shared_ptr<xmlnode::CXmlNode>& node)
{
    auto itemNode = node->AddChild(L"tile");

    itemNode->SetAttribute(L"x", GetX());
    itemNode->SetAttribute(L"y", GetY());
    // itemNode->SetAttribute(L"zoning", (int)mZoning);

    return itemNode;
}


/**
* brief Load the attributes for an item node.
*
* This is the  base class version that loads the attributes
* common to all items. Override this to load custom attributes
* for specific items.
*
* \param node The Xml node we are loading the item from
*/
void CItem::XmlLoad(const std::shared_ptr<xmlnode::CXmlNode>& node)
{
    auto X = node->GetAttributeIntValue(L"x", 0);
    auto Y = node->GetAttributeIntValue(L"y", 0);

    SetX(X);
    SetY(Y);
}
