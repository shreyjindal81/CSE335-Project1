/**
 * \file ActualRoad.h
 *
 * \author Shizuka
 *
 * Class that represents a road tile
 *
 */

#pragma once
#include "ActualItem.h"

 /// Class that represents a road tile
class CActualRoad :
    public CActualItem
{
public:
    /// constructor
    ///\param file filename the image of the road
    ///\param x x location of the road
    ///\param y ylocation of the road
    ///\param type of road
    ///\param id id the of the road's image
    CActualRoad(std::wstring file, double x, double y, std::wstring type, std::wstring id) : CActualItem(file, x, y, id) { mType = type; }; ///< constructor
    
    /// Getter of mType
    ///\returns mType Type of road
    std::wstring GetType() { return mType; } ///<getter of mType
private:
    std::wstring mType; ///< Type of road
};

