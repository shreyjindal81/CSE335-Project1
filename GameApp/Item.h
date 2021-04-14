/**
 * \file Item.h
 *
 * \author Shizuka
 *
 * Class that represents the Items in the game
 *
 */

#pragma once

#include <string>
#include <memory>
#include "XmlNode.h"
#include "ItemVisitor.h"
#include "TowerLister.h"
#include "Score.h"
#include "BombCounter.h"
#include "Game.h"
#include "DartBalloonVisitor.h"
#include "RingVisitor.h"
#include "TowerVisit.h"

class CGame;

/**
 * Base class for any item in our Game.
 */
class CItem
{
public:
    /// Default constructor (disabled)
    CItem() = delete;

    /// Copy constructor (disabled)
    CItem(const CItem&) = delete;

    virtual ~CItem(); ///< destructor

    /** The X location of the item
     * \returns X location in pixels */
    virtual double GetX() const { return mX; } ///< getter for mX

    /** The Y location of the item
    * \returns Y location in pixels */
    virtual double GetY() const { return mY; } ///< getter for mY

    /** getter for drag
    * \returns mDrag */
    bool GetDrag() const { return mDrag; } 

    /** getter for type
    * \returns mType */
    virtual std::wstring GetType() const { return mType; } 

    /** Set the item location
     * \param x X location
     * \param y Y location */
    virtual void SetLocation(double x, double y) { mX = x; mY = y; }

    virtual void Draw(Gdiplus::Graphics* graphics);

    /// Get the game this item is in
    /// \returns game pointer
    virtual CGame* GetGame() { return mGame; } ///< getter for mGame

    /// <summary>
    /// setter
    /// </summary>
    /// <param name="x"></param>
    virtual void SetX(int x) { mX = x; } ///< setter of mX

    /// setter of mY
    /// \param y
    virtual void SetY(int y) { mY = y; } 

    virtual void SetImage(const std::wstring& file); 

    /// <summary>
    /// drag setter shifter
    /// </summary>
    void SetDrag() { mDrag = true; }; ///< setter of drag to default true

    /// <summary>
    /// set drag
    /// </summary>
    /// <param name="set"></param>
    void SetDrag(bool set) { mDrag = set; }; ///< setter of drag


    /// <summary>
    /// set type
    /// </summary>
    /// <param name="type"></param>
    virtual void SetType(std::wstring type) { mType = type; } ///< setter of mType

    /** virtual function to fix items in position
    */
    virtual void SetPlaced(bool) {};

    /**
    * The directory where the images are stored 
    */
    static const std::wstring ImagesDirectory;

    /** Handle updates for animation
    * 
    * \param elapsed The time since the last update
    * 
    */
    virtual void Update(double elapsed) {};

    /// <summary>
    /// quantize
    /// </summary>
    void QuantizeLocation();

    /// <summary>
    /// hittest  from item
    /// </summary>
    /// <param name="x"></param>
    /// <param name="y"></param>
    /// <returns></returns>
    virtual bool CItem::HitTest(double x, double y);

    virtual std::shared_ptr<xmlnode::CXmlNode> XmlSave(const std::shared_ptr<xmlnode::CXmlNode>& node);
    
    virtual void XmlLoad(const std::shared_ptr<xmlnode::CXmlNode>& node);


    /** Get the width of the item
    * \returns width of image */
    virtual int GetWidth() const { return mItemImage->GetWidth(); }

    /** Get the height of the item
    * \returns height of image */
    virtual int GetHeight() const { return mItemImage->GetHeight(); }

    /** Set toggle for road
    * \param b to be set */
    void SetRoadToggle(bool b) { mSetRoadToggle = b; } ///< setter for mSetRoadToggle

    /** Get the toggle for road
    * \returns mSetRoadToggle */
    bool GetRoadToggle() { return mSetRoadToggle; } ///< getter for mSetRoadToggle

    /**
    * Accept a visitor
    * \param visitor The visitor we accept 
    */
    virtual void Accept(CItemVisitor* visitor) = 0;

    /**
    * Accept a visitor
    * \param visitor The visitor we accept
    * \returns false
    */
    virtual bool Accept(CTowerLister* visitor) { return false; }

    /**
    * Accept a visitor
    * \param visitor The visitor we accept
    * \returns false
    */
    virtual bool Accept(CBombCounter* visitor) { return false; }

    /**
    * Accept a visitor
    * \param visitor The visitor we accept
    * \returns false
    */
    virtual bool Accept(CRingVisitor* visitor) { return false; }

    /**
    * Accept a visitor
    * \param visitor The visitor we accept
    * \returns false
    */
    virtual bool Accept(CTowerVisit* visitor) { return false; }

    /**
    * Accept a visitor
    * \param visitor The visitor we accept
    * \returns 0
    */
    virtual int Accept(CDartBalloonVisitor* visitor) { return 0; }


    /// <summary>
    /// set keeper function
    /// </summary>
    /// <param name="x"></param>
    virtual void SetKeeper(std::shared_ptr<CScore> x) { mScoreboard = x; }; ///< setter for mScoreBoard

    /** getter for item image
    * \returns mItemImage
    */
    virtual std::shared_ptr<Gdiplus::Bitmap> GetImage() { return mItemImage; } ///< getter of mItemImage

    /** virtual function for getting tip of dart
    *\param x
    *\param y
    */
    virtual void GetTip(double& x, double& y) {};

    /** virtual function for getting time after bomb tower blasts
    * \returns 0
    */
    virtual double GetTimeAfterExplode() { return 0; } 

    /** virtual function for popping a balloon and updating score
    */
    virtual void Popped(int) {}; 

    /** virtual function to update score when balloon passes unpopped
    */
    virtual void Passed() {};  

    /** virtual function to set index
    */
    virtual void SetIndex(int) {};

    /** virtual function to check if item will pop a particular coordinate
    * \returns false
    */
    virtual bool WillPop(double, double) { return false; }

    virtual void DeleteItem(std::shared_ptr<CItem> item);

    /** Getter for item toggle
    * \returns mItemToggle
    */
    bool GetItemToggle() { return mItemToggle; }

    /** Setter for item toggle
    * \param val to be set
    */
    void SetItemToggle(bool val) { mItemToggle = val; }

protected:
    CItem(CGame* game); ///< constructor
    std::shared_ptr<CScore> mScoreboard; ///< pointer variable tp CScore that represents the scoreboard
    std::shared_ptr<Gdiplus::Bitmap> mItemImage; ///< pointer variable that stores the item image filename

private:


    /// The game this item is contained in
    CGame* mGame; ///< pointer t the game the item is contained in

    bool mItemToggle = true; ///< item toggle

    bool mSetRoadToggle = false; ///< road toggle
    
    bool mDrag = false; ///< tells if item is draggable or not

    // Item location in the game
    double mX = 0;     ///< X location for the center of the item
    double mY = 0;     ///< Y location for the center of the item

    std::wstring mType = L""; ///< stores type of item

};

