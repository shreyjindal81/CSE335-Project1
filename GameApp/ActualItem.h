/**
 * \file ActualItem.h
 *
 * \author Shizuka
 *
 * Class that represents an Item
 *
 */

#pragma once
#include "XmlNode.h"

 /// Class that represents an item
class CActualItem
{
public:
	/// constructor
	///\param file filename the image of the item
	///\param x x location of the item
	///\param y ylocation of the item
	///\param id id the of the item's image
	CActualItem(std::wstring file, double x, double y, std::wstring id);

	/// Getter of mFile
	///\returns mFile filename of item
	std::wstring GetFile() { return mFile; } 

	/// Getter of mId
	///\returns mId Id of the item
	std::wstring GetId() { return mId; }  

	/// Getter of mX
	///\returns mX x location of the item
	double GetX() { return mX; }

	/// Getter of mY
	///\returns mY y location of the item
	double GetY() { return mY; }
private:
	std::wstring mFile; ///< level filename
	double mX; ///< X location of Item
	double mY; ///< X location of Item
	std::wstring mId; ///< Image id of Item

};

