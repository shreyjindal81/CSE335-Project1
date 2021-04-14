/**
 * \file Game.h
 *
 * \author Shizuka
 * 
 * Class that the represents the Game
 *
 */

#pragma once

#include <memory>
#include <vector>
#include <map>
#include <utility>
#include <string>
#include "ItemVisitor.h"
#include "Score.h"
#include "TowerLister.h"
#include "BombCounter.h" 
#include "BeginLevel.h"


class CItem;

class CXmlLoader;

/// Class that the represents the Game
class CGame
{
public:
    CGame();
    virtual ~CGame();

    /// The spacing between grid locations
    static const int GridSpacing = 64;  


    void Add(std::shared_ptr<CItem> item);
    std::shared_ptr<CItem> HitTest(double x, double y); 
    
    /// function that finds the nearest grass from a given point
    ///\param x
    ///\param y 
    ///\returns std::shared_ptr<CItem> 
    std::shared_ptr<CItem> NearestGrass(double x, double y);
    void MoveToFront(std::shared_ptr<CItem> item);

    ///function that deleted the passed object
    ///\param item 
    void DeleteItem(std::shared_ptr<CItem> item);

    void OnDraw(Gdiplus::Graphics* graphics, int width, int height);
    void BeginPopup(Gdiplus::Graphics* graphics, std::wstring lvlName);

    void NextLvl();

    //void Save(const std::wstring& filename);
    void XmlLoad(std::wstring& filename);
    void Clear();

    void Update(double elapsed);
    void SortTiles();

    /// getter for mXOffset
    ///\returns mXOffset
    float GetMXOffset() { return mXOffset; } 
    /// getter for mYOffset
    ///\returns mYOffset
    float GetMYOffset() { return mYOffset; } 
    /// getter for mScale
    ///\returns mScale
    float GetMScale() { return mScale; } 

    /// getter for mXmlLoader
    ///\returns mXmlLoader
    std::shared_ptr<CXmlLoader> GetLoad() { return mXmlLoader; } 

    std::shared_ptr<CItem> GetAdjacent(std::shared_ptr<CItem> tile, int dx, int dy);
    std::shared_ptr<CItem> GetAdjacent(CItem* tile, int dx, int dy);

    /*
    * Accept a visitor
    * \param visitor The visitor we accept
    */
    std::vector<std::shared_ptr<CItem>> Accept(CTowerLister* visitor);
    /*
    * Accept a visitor
    * \param visitor The visitor we accept
    */
    void Accept(CItemVisitor* visitor);


    int Accept(CBombCounter* visitor);

    /// getter for mItems
    ///\returns mItems
    std::vector<std::shared_ptr<CItem> > GetItemList() { return mItems; } 

    virtual void MakeStationary();

    /**
    * Save the game as a .game XML file.
    *
    * Open an XML file and stream the aquarium data to it.
    *
    * \param filename The filename of the file to save the aquarium to
    */
    void Save(const std::wstring& filename);

    /// getter for mBalloonOnScreen
    ///\returns mBalloonOnScreen
    int GetBalloonOnScreen() { return mBalloonOnScreen; } 

    /// setter for mBalloonOnScreen
    ///\param numBalloons
    void SetBalloonOnScreen(int numBalloons) { mBalloonOnScreen = numBalloons; }

    /// sets the mLevel3 toggle
    ///\param value bool value
    void SetLevel3Toggle(bool value) { mLevel3 = value; }

private:
    void BuildAdjacencies();

    std::shared_ptr<CXmlLoader> mXmlLoader; ///< pointer to XmlLoader class


    std::vector<std::shared_ptr<CItem> > mItems; ///< vector that stores pointers to all items of the game

    std::map<std::pair<double, double>, std::shared_ptr<CItem> > mAdjacency; ///< map for adjaecncy lookup support


    const static int Width = 1224; ///< game area width in virtual pixels

    const static int Height = 1024; ///< game area height in virtual pixels

    float mScale = 0; ///< scaling factor for virtual pixel
    float mXOffset = 0; ///< offset for x axis v.p
    float mYOffset = 0; ///< offset for y axis v.p

    double mtBalloon = 0; ///< track of balloon journey per tile
    int mBalloonIntroduced = 0; ///< number of Red  Balloons introduced

    int mBlueBalloonIntroduced = 0; ///< number of Blue Balloons introduced

    int mBalloonOnScreen = 0; ///< stores balloons on sreen
    std::shared_ptr<CScore> mScorekeeper; ///< pointer varible to class CScore
    CBeginLevel mTemp; ///< object of CBeginLevel class

    /// Toggle for level 3 special effects
    bool mLevel3 = false;

};


