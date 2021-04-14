/**
 * \file TowerRing.h
 *
 * \author Shizuka
 *
 */
#pragma once
#include "Tower.h"
/**
* CTowerRing represents the class of ring towers. This tower fires a periodic expanding ring
* every 5 seconds till a radius of 100 pixels. If a balloon is within 24 pixels of the ring,
* it is popped.
*/
class CTowerRing :
    public CTower
{
public:
    ///  Default constructor (disabled)
    CTowerRing() = delete;

    ///  Copy constructor (disabled)
    CTowerRing(const CTowerRing&) = delete;

    CTowerRing(CGame* game);

    /// Accepts ring visitor
    ///\param visitor being accepted
    ///\returns true if tower is inside game area
    virtual bool Accept(CRingVisitor* visitor) override { return GetX() < 1056; }

    /// destructor
    virtual ~CTowerRing() {};

    virtual void Update(double elapsed) override;

    void Ring(bool);

    virtual bool WillPop(double, double) override ;

    virtual void Draw(Gdiplus::Graphics* graphics);

    /// Setter for mPlaced
    ///\param placed new value for mPlaced
    ///\returns mPlaced
    virtual void SetPlaced(bool placed) { mPlaced = placed; }

private:
    /// speed of ring
    double mSpeed = 200;
    /// Time between ring, initialised to 1000
    double mTimeBetweenRing = 1000;
    /// Time interval between 2 rings, initialised at 1000
    double mInterval = 1000;
    /// tells if ring is in action or not, false by default
    bool mRing = false;
    /// tells if tower is in play area, false by default
    bool mPlaced = false;
    /// keep track of time elapsed since ring
    double mTimeAfterRing = 0;
    /// Current radius of ring, 0 when inactive
    double mRadius = 0;
};
