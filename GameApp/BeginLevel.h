/**
 * \file ActualRoad.h
 *
 * \author Shizuka
 *
 * Class that handles begin level popup text
 *
 * Responsible for displaying the popup texts at the beginning and end of each level
 */


#pragma once

/// Class that handles the begin level popup texts
class CBeginLevel
{
public:
    CBeginLevel(); ///< constructor

    ///  Copy constructor (disabled)
    CBeginLevel(const CBeginLevel&) = delete;

    ~CBeginLevel(); ///< destructor


    
    /// Draws the Begin Level Popup text
    ///\param graphics Graphics pointer
    ///\param level The text to draw
    void Draw(Gdiplus::Graphics* graphics, const WCHAR* level);

private:

};

