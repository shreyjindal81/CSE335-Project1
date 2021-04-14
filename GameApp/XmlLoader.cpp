/**
 * \file Tower.h
 *
 * \author Shizuka
 * 
 */


#include "pch.h"
#include "XmlLoader.h"
#include "Tile.h"
#include "RoadTile.h"
#include "DefinedRoad.h"
#include "ActualItem.h"
#include "ActualRoad.h"
#include "TileBuilding.h"
#include "TileLandscape.h"
#include "RoadTile.h"
#include "TileGrass.h"
#include <algorithm>

using namespace std;

/// Constructor
CXmlLoader::CXmlLoader(const std::shared_ptr<xmlnode::CXmlNode>& root)
{
    mFirstX = 0;
    mFirstY = 0;
    mStartX = stoi(root->GetAttributeValue(L"start-x", L""));
    mStartY = stoi(root->GetAttributeValue(L"start-y", L""));
    mGridWidth = stoi(root->GetAttributeValue(L"width", L""));
    mGridHeight = stoi(root->GetAttributeValue(L"height", L""));
    for (auto child : root->GetChildren())
    {
        if (child->GetType() == NODE_ELEMENT)
        {
            std::wstring name = child->GetName();
            if (child->GetName() == L"declarations")
            {
                XmlDeclarations(child);
            }
            else if (child->GetName() == L"items")
            {
                XmlItem(child);
            }

        }
    }
}


void CXmlLoader::XmlDeclarations(const std::shared_ptr<xmlnode::CXmlNode>& node)
{
    for (auto child : node->GetChildren())
    {
        if (child->GetType() == NODE_ELEMENT)
        {
            std::wstring name = child->GetName();
            if (child->GetName() == L"road")
            {
                XmlDeclareRoad(child);
            }
            if (child->GetName() == L"open" || child->GetName() == L"house" || child->GetName() == L"trees")
            {
                XmlDeclareTile(child);
            }
        }
    }
}

void CXmlLoader::XmlDeclareRoad(const std::shared_ptr<xmlnode::CXmlNode>& node)
{
    auto definedRoad = make_shared<CDefinedRoad>(node);

    mRoadDeclares[definedRoad->GetId()] = definedRoad;
}

void CXmlLoader::XmlDeclareTile(const std::shared_ptr<xmlnode::CXmlNode>& node)
{
    auto definedTile = make_shared<CDefinedItem>(node);

    mItemDeclares[definedTile->GetId()] = definedTile;
}



void CXmlLoader::XmlItem(const std::shared_ptr<xmlnode::CXmlNode>& node)
{
    for (auto child : node->GetChildren())
    {
        if (child->GetType() == NODE_ELEMENT)
        {
            std::wstring name = child->GetName();
            if (child->GetName() == L"road")
            {
                XmlRoad(child);
            }
            if (child->GetName() == L"open" || child->GetName() == L"house" || child->GetName() == L"trees")
            {
                XmlTile(child);
            }
        }
    }
}

void CXmlLoader::XmlRoad(const std::shared_ptr<xmlnode::CXmlNode>& node)
{
    auto roadId = node->GetAttributeValue(L"id", L"");
    double roadX = stoi(node->GetAttributeValue(L"x", L""));
    double roadY = stoi(node->GetAttributeValue(L"y", L""));
    auto iterator = mRoadDeclares.find(roadId);
    std::wstring roadFile = L"";
    std::wstring roadType = L"";
    if (iterator != mRoadDeclares.end())
    {
        roadFile = iterator->second->GetImage();
        roadType = iterator->second->GetType();
    }
    CActualRoad road(roadFile, roadX, roadY, roadType, roadId);
    mActualRoads.push_back(make_shared<CActualRoad>(road));
}

void CXmlLoader::XmlTile(const std::shared_ptr<xmlnode::CXmlNode>& node)
{
    auto tileId = node->GetAttributeValue(L"id", L"");
    double tileX = stoi(node->GetAttributeValue(L"x", L""));
    double tileY = stoi(node->GetAttributeValue(L"y", L""));
    auto iterator = mItemDeclares.find(tileId);
    std::wstring tileFile = L"";
    if (iterator != mItemDeclares.end())
    {
        tileFile = iterator->second->GetImage();
    }
    CActualItem item(tileFile, tileX, tileY, tileId);
    mActualItems.push_back(make_shared<CActualItem>(item));
}

void CXmlLoader::AddItems(CGame& game)
{
    for (auto item : mActualItems)
    {
        AddItem(game, item);
    }
    this->InitVect();
    for (auto road : mActualRoads)
    {
        AddRoad(game, road);
    }
    this->AddRoad1(game);
}

void CXmlLoader::AddItem(CGame& game, shared_ptr<CActualItem> item)
{
    auto id = item->GetId();
    auto tile = make_shared<CTile>(&game);

    if (id == L"i011" || id == L"i012" || id == L"i013" || id == L"i014" || id == L"i015" || id == L"i016" || id == L"i017") {
        tile = make_shared<CTileBuilding>(&game);
        tile->SetType(L"Building");
    }
    else if (id == L"i018" || id == L"i019" || id == L"i020" || id == L"i021") {
        tile = make_shared<CTileLandscape>(&game);
        tile->SetType(L"Landscape");
    }
    else if (id == L"i007" || id == L"i008") {
        tile = make_shared<CTileGrass>(&game);
        tile->SetType(L"grass");
    }
    tile->SetImage(item->GetFile());
    tile->SetLocation((item->GetX()) * 64, (item->GetY()) * 64);
    game.Add(tile);

}

void CXmlLoader::AddRoad(CGame& game, shared_ptr<CActualRoad> item)
{
    auto tile = make_shared<CRoadTile>(&game);
    int toggle1 = 0;
    std::wstring id = item->GetId();
    double x = 0;
    double y = 0;

    std::wstring id1;
    std::wstring id2;
    if (id == L"i001" || id == L"i002" || id == L"i003" || id == L"i004" || id == L"i005" || id == L"i006") {
        tile = make_shared<CRoadTile>(&game);
        tile->SetType(L"Road");
        tile->SetTypeTile(id);
    }
    mCount++;
    tile->SetImage(item->GetFile());
    tile->SetLocation((item->GetX()) * 64, (item->GetY()) * 64);
    game.Add(tile);

    x = item->GetX();
    y = item->GetY();
    vect[int(item->GetX())][int(item->GetY())] = tile;

    if (mToggleFirst == 0) {
        mPrevTile = tile;
        tile->SetAllocate(1);
        mToggleFirst = 1;
        mFirstX = int(item->GetX());
        mFirstY = int(item->GetY());
    }
}





void CXmlLoader::AddRoad1(CGame& game) {
    int toggle = 0;
    int i = mFirstX;
    int j = mFirstY;
    for (int k = 0; k < 256; k++) {

        if (vect[i][j] != nullptr) {
            auto original = vect[i][j];
            auto id1 = original->Getid();
            auto x = vect[i][j]->GetX() / 64;
            auto y = vect[i][j]->GetY() / 64;
            if (x == 13 && y == 5) {

                y = vect[i][j]->GetY() / 64;
            }
            if (id1 == L"i001") {
                if (i - 1 > 0 && vect[static_cast<unsigned __int64>(i)- 1][j] != nullptr && vect[static_cast<unsigned __int64>(i)- 1][j]->Getid() != L"i002" && vect[static_cast<unsigned __int64>(i)- 1][j]->Getid() != L"i006" && vect[static_cast<unsigned __int64>(i)- 1][j]->Getid() != L"i004" && vect[static_cast<unsigned __int64>(i)- 1][j]->Getallocate() == 0 && vect[static_cast<unsigned __int64>(i)- 1][j]->GetRoadTileAdj() != vect[i][j]) {
                    original->SetAdjacentRoadTile(vect[static_cast<unsigned __int64>(i)- 1][j]);
                    vect[static_cast<unsigned __int64>(i)- 1][j]->SetAllocate(1);
                    i = i - 1;

                }
                else if (i + 1 < 255 && vect[static_cast<unsigned __int64>(i)+ 1][j] != nullptr && vect[static_cast<unsigned __int64>(i)+ 1][j]->Getid() != L"i002" && vect[static_cast<unsigned __int64>(i)+ 1][j]->Getid() != L"i005" && vect[static_cast<unsigned __int64>(i)+ 1][j]->Getid() != L"i003" && vect[static_cast<unsigned __int64>(i)+ 1][j]->Getallocate() == 0 && vect[static_cast<unsigned __int64>(i)+ 1][j]->GetRoadTileAdj() != vect[i][j]) {

                    original->SetAdjacentRoadTile(vect[static_cast<unsigned __int64>(i)+ 1][j]);
                    vect[static_cast<unsigned __int64>(i)+ 1][j]->SetAllocate(1);
                    i = i + 1;
                }
            }
            else if (id1 == L"i002") {
                if (j - 1 > 0 && vect[i][static_cast<unsigned __int64>(j)- 1] != nullptr && vect[i][static_cast<unsigned __int64>(j)- 1]->Getid() != L"i001" && vect[i][static_cast<unsigned __int64>(j)- 1]->Getid() != L"i005" && vect[i][static_cast<unsigned __int64>(j)- 1]->Getid() != L"i006" && vect[i][static_cast<unsigned __int64>(j)- 1]->Getallocate() == 0 && vect[i][static_cast<unsigned __int64>(j)- 1]->GetRoadTileAdj() != vect[i][j]) {
                    original->SetAdjacentRoadTile(vect[i][static_cast<unsigned __int64>(j)- 1]);
                    vect[i][static_cast<unsigned __int64>(j)- 1]->SetAllocate(1);
                    j = j - 1;
                }

                else  if (j + 1 < 255 && vect[i][static_cast<unsigned __int64>(j)+ 1] != nullptr && vect[i][static_cast<unsigned __int64>(j)+ 1]->Getid() != L"i001" && vect[i][static_cast<unsigned __int64>(j)+ 1]->Getid() != L"i003" && vect[i][static_cast<unsigned __int64>(j)+ 1]->Getid() != L"i004" && vect[i][static_cast<unsigned __int64>(j)+ 1]->Getallocate() == 0 && vect[i][static_cast<unsigned __int64>(j)+ 1]->GetRoadTileAdj() != vect[i][j]) {

                    original->SetAdjacentRoadTile(vect[i][static_cast<unsigned __int64>(j)+ 1]);
                    vect[i][static_cast<unsigned __int64>(j)+ 1]->SetAllocate(1);
                    j = j + 1;
                }

            }
            else if (id1 == L"i003") {
                if (i + 1 < 255 && vect[static_cast<unsigned __int64>(i)+ 1][j] != nullptr && vect[static_cast<unsigned __int64>(i)+ 1][j]->Getid() != L"i002" && vect[static_cast<unsigned __int64>(i)+ 1][j]->Getid() != L"i005" && vect[static_cast<unsigned __int64>(i)+ 1][j]->Getallocate() == 0 && vect[static_cast<unsigned __int64>(i)+ 1][j]->GetRoadTileAdj() != vect[i][j]) {

                    original->SetAdjacentRoadTile(vect[static_cast<unsigned __int64>(i)+ 1][j]);
                    vect[static_cast<unsigned __int64>(i)+ 1][j]->SetAllocate(1);
                    i = i + 1;
                }
                else if (j + 1 < 255 && vect[i][static_cast<unsigned __int64>(j)+ 1] != nullptr && vect[i][static_cast<unsigned __int64>(j)+ 1]->Getid() != L"i001" && vect[i][static_cast<unsigned __int64>(j)+ 1]->Getid() != L"i004" && vect[i][static_cast<unsigned __int64>(j)+ 1]->Getallocate() == 0 && vect[i][static_cast<unsigned __int64>(j)+ 1]->GetRoadTileAdj() != vect[i][j]) {

                    original->SetAdjacentRoadTile(vect[i][static_cast<unsigned __int64>(j)+ 1]);
                    vect[i][static_cast<unsigned __int64>(j)+ 1]->SetAllocate(1);
                    j = j + 1;
                }
            }
            else if (id1 == L"i004") {
                if (i - 1 > 0 && vect[static_cast<unsigned __int64>(i)- 1][j] != nullptr && vect[static_cast<unsigned __int64>(i)- 1][j]->Getid() != L"i002" && vect[static_cast<unsigned __int64>(i)- 1][j]->Getid() != L"i006" && vect[static_cast<unsigned __int64>(i)- 1][j]->Getallocate() == 0 && vect[static_cast<unsigned __int64>(i)- 1][j]->GetRoadTileAdj() != vect[i][j]) {
                    original->SetAdjacentRoadTile(vect[static_cast<unsigned __int64>(i)- 1][j]);
                    vect[static_cast<unsigned __int64>(i)- 1][j]->SetAllocate(1);
                    i = i - 1;
                }
                else if (j + 1 < 255 && vect[i][static_cast<unsigned __int64>(j)+ 1] != nullptr && vect[i][static_cast<unsigned __int64>(j)+ 1]->Getid() != L"i001" && vect[i][static_cast<unsigned __int64>(j)+ 1]->Getid() != L"i003" && vect[i][static_cast<unsigned __int64>(j)+ 1]->Getallocate() == 0 && vect[i][static_cast<unsigned __int64>(j)+ 1]->GetRoadTileAdj() != vect[i][j]) {

                    original->SetAdjacentRoadTile(vect[i][static_cast<unsigned __int64>(j)+ 1]);
                    vect[i][static_cast<unsigned __int64>(j)+ 1]->SetAllocate(1);
                    j = j + 1;
                }
            }
            else if (id1 == L"i005") {
                if (j - 1 > 0 && vect[i][static_cast<unsigned __int64>(j)- 1] != nullptr && vect[i][static_cast<unsigned __int64>(j)- 1]->Getid() != L"i001" && vect[i][static_cast<unsigned __int64>(j)- 1]->Getid() != L"i006" && vect[i][static_cast<unsigned __int64>(j)- 1]->Getallocate() == 0 && vect[i][static_cast<unsigned __int64>(j)- 1]->GetRoadTileAdj() != vect[i][j]) {
                    original->SetAdjacentRoadTile(vect[i][static_cast<unsigned __int64>(j)- 1]);
                    vect[i][static_cast<unsigned __int64>(j)- 1]->SetAllocate(1);
                    j = j - 1;
                }
                else if (i + 1 < 255 && vect[static_cast<unsigned __int64>(i)+ 1][j] != nullptr && vect[static_cast<unsigned __int64>(i)+ 1][j]->Getid() != L"i002" && vect[static_cast<unsigned __int64>(i)+ 1][j]->Getid() != L"i003" && vect[static_cast<unsigned __int64>(i)+ 1][j]->Getallocate() == 0 && vect[static_cast<unsigned __int64>(i)+ 1][j]->GetRoadTileAdj() != vect[i][j]) {

                    original->SetAdjacentRoadTile(vect[static_cast<unsigned __int64>(i)+ 1][j]);
                    vect[static_cast<unsigned __int64>(i)+ 1][j]->SetAllocate(1);
                    i = i + 1;
                }
            }
            else if (id1 == L"i006") {
                if (i - 1 > 0 && vect[static_cast<unsigned __int64>(i)- 1][j] != nullptr && vect[static_cast<unsigned __int64>(i)- 1][j]->Getid() != L"i002" && vect[static_cast<unsigned __int64>(i)- 1][j]->Getid() != L"i004" && vect[static_cast<unsigned __int64>(i)- 1][j]->Getallocate() == 0 && vect[static_cast<unsigned __int64>(i)- 1][j]->GetRoadTileAdj() != vect[i][j]) {
                    original->SetAdjacentRoadTile(vect[static_cast<unsigned __int64>(i)- 1][j]);
                    vect[static_cast<unsigned __int64>(i)- 1][j]->SetAllocate(1);
                    i = i - 1;
                }
                else  if (j - 1 > 0 && vect[i][static_cast<unsigned __int64>(j)- 1] != nullptr && vect[i][static_cast<unsigned __int64>(j)- 1]->Getid() != L"i005" && vect[i][static_cast<unsigned __int64>(j)- 1]->Getid() != L"i001" && vect[i][static_cast<unsigned __int64>(j)- 1]->Getallocate() == 0 && vect[i][static_cast<unsigned __int64>(j)- 1]->GetRoadTileAdj() != vect[i][j]) {
                    original->SetAdjacentRoadTile(vect[i][static_cast<unsigned __int64>(j)- 1]);
                    vect[i][static_cast<unsigned __int64>(j)- 1]->SetAllocate(1);
                    j = j - 1;
                }
            }


        }


    }

}


void CXmlLoader::InitVect() {
    for (int i = 0; i < 256; i++) {
        std::vector<std::shared_ptr<CRoadTile>> v;
        for (int j = 0; j < 256; j++) {
            v.push_back(nullptr);

        }
        vect.push_back(v);
    }
}

