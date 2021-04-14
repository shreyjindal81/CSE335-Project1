/**
 * \file Balloon.h
 *
 * \author Shizuka
 *
 * Class that represents a balloon
 *
 */

#pragma once

#include "Item.h"
#include <vector>
#include <memory>
#include "Score.h"

/// Class that represents a balloon
class CBalloon : public CItem
{
public:
    /// Constructor
    ///\param game Game of which this is part of
    CBalloon(CGame* game); 

    ///  Default constructor (disabled)
    CBalloon() = delete;

    ///  Copy constructor (disabled)s
    CBalloon(const CBalloon&) = delete;

    virtual ~CBalloon() override; ///< destructor

    /// Getter of mT
    ///\returns mT time counter
    virtual double GetT() { return mT; }

    /// Getter of mIsForward
    ///\returns mIsForward direction of balloon with respect to the tile
    virtual bool IsForward() { return mIsForward; }

    /// Setter of mIsForward
    ///\param current what mIsForward is to be set to
    virtual void SetIsForward(bool current) { mIsForward = current; } 

    /// Accept a visitor
    ///\param visitor The visitor we accept
    virtual void Accept(CItemVisitor* visitor) {};

    /// Accept a visitor
    ///\param visitor The visitor we accept
    ///\returns true
    virtual bool Accept(CTowerLister* visitor) override { return true; }

    
    /// Update function for animation
    ///\param elapsed The elapsed time
    virtual void Update(double elapsed) override {};

    /// Setter of mT
    ///\param t what mT is to be set to
    virtual void SetT(double t) { mT = t; }

    virtual void Popped(int) override; ///< function that handles score after balloon is popped
    virtual void Passed() override; ///< function that handles score after balloon passed

    /// Getter of mPopped
    ///\returns mPopped variable that stores if balloon is popped
    virtual bool GetPopped() { return mPopped; }

    
    /// Accept a visitor
    ///\param visitor The visitor we accept
    ///\returns 2
    virtual int Accept(CDartBalloonVisitor* visitor) override { return 2; }


private:
    bool mPopped = false; ///< boolean variable that stores if balloon is popped

    double mT = 0; ///< stores time

    bool mIsForward = true; ///< stores if it is going forward with respect to tile


};


