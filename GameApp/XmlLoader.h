/**
 * \file XmlLoader.h
 *
 * \author Shizuka
 *
 * Class that implements the XML Loader
 *
 */


#pragma once
#include "XmlNode.h"
#include "DefinedItem.h"
#include "Game.h"
#include <memory>
#include <map>
#include <vector>
#include <utility>
#include "ActualItem.h"
#include "DefinedRoad.h"
#include "ActualRoad.h"
#include <iostream>

using namespace std;

/// Class that implements the XML Loader
class CXmlLoader
{
public:
	/// Constructor
	///\param node CXmlNode shared pointer that holds the definitions
	CXmlLoader(const std::shared_ptr<xmlnode::CXmlNode>& node);

	/// Creates definitions for roads and tiles of the map by calling its supporting functions
	///\param node CXmlNode shared pointer that holds the definitions
	void XmlDeclarations(const std::shared_ptr<xmlnode::CXmlNode>& node);

	/// Creates definitions for road tiles
	///\param node CXmlNode shared pointer that holds the definition to the road
	void XmlDeclareRoad(const std::shared_ptr<xmlnode::CXmlNode>& node);

	/// Creates definitions for road tiles
	///\param node CXmlNode shared pointer that holds the definition to the road
	void XmlDeclareTile(const std::shared_ptr<xmlnode::CXmlNode>& node);

	/// Getter of mStartX
	///\returns mStartX The starting x position
	
	/// Getter of mStartY
	///\returns mStartY The starting y position
	double GetStartY() { return mStartY; }

	/// Getter of mGridHeight
	///\returns mGridHeight The height of the grid
	double GetGridHeight() { return mGridHeight; }

	/// Getter of mGridWidth
	///\returns mGridWidth The width of the grid
	double GetGridWidth() { return mGridWidth; }

	/// Gets attributes of all things to be added to the game segregates into neccessary classes using supporting functions
	///\param node CXmlNode shared pointer that holds the definition to the road
	void XmlItem(const std::shared_ptr<xmlnode::CXmlNode>& node);

	/// Gets the attributes of road tiles and adds it into the necssary classes and sets its attributes
	///\param node CXmlNode shared pointer that holds the definition to the road
	void XmlRoad(const std::shared_ptr<xmlnode::CXmlNode>& node);

	/// Gets the attributes of non-road tiles and adds it into the necssary classes and sets its attributes
	///\param node CXmlNode shared pointer that holds the definition to the non-road tile
	void XmlTile(const std::shared_ptr<xmlnode::CXmlNode>& node);

	/// Adds items to game from the xml file
	///\param game The game in which items are to be added
	void AddItems(CGame& game);

	/// Adds an item to game from the xml file
	///\param game The game in which the item is to be added
	///\param item The CActualItem shared pointer of the item
	void AddItem(CGame& game, std::shared_ptr<CActualItem> item);

	/// Adds aa road tile to game from the xml file
	///\param game The game in which the road is to be added
	///\param item The CActualItem shared pointer of the road
	void AddRoad(CGame& game, std::shared_ptr<CActualRoad> item);

	/// Adds a road to game from the xml file and sets adjacent roads
	///\param game The game in which the road is to be added
	void AddRoad1(CGame& game);

	/// Stores the items in a vector of vectors
	void InitVect();


private:
	std::map<std::wstring, std::shared_ptr<CDefinedItem>> mItemDeclares; ///< map of declared items with name and pointer
	std::map<std::wstring, std::shared_ptr<CDefinedRoad>> mRoadDeclares; ///< map of declared roads with name and pointer

	double mStartX = 0; ///< Starting x location for items
	double mStartY = 0; ///< Starting y location for items

	double mGridHeight = 0; ///< grid height of game
	double mGridWidth = 0; ///< grid width of game

	std::vector<std::shared_ptr<CActualItem>> mActualItems; ///<vector of CActualItem pointers to all items
	std::vector<std::shared_ptr<CActualRoad>> mActualRoads; ///<vector of CActualRoad pointers to all roads

	std::shared_ptr<CRoadTile> mPrevTile; ///< CRoadTile shared pointer to previous tiles

	std::vector<std::vector<std::shared_ptr<CRoadTile>>> vect; ///<vetor of CRoadTile pointers to road tiles
	std::vector<std::shared_ptr<CRoadTile>> mPrev; ///< vetor of CRoadTile pointers to previous road tiles
	std::vector<std::shared_ptr<CRoadTile>> mCurr; ///< vetor of CRoadTile pointers to current road tiles

	int mFirstX{}; ///< First X location
	int mFirstY{}; ///< First Y location

	int mToggleFirst = 0; ///< first toggle value

	int mCount = 0; ///< counter variable
};
