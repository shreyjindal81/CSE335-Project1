/**
 * \file TowerBomb.h
 *
 * \author Shizuka
 *
 */
#pragma once
#include "Tower.h"
#include "BombCounter.h"

 /**
 * CTowerRing represents the class of bomb tower towers. The bombs blast one-by-one 
 * every 3 seconds.
 */
class CTowerBomb : public CTower
{
public:

    CTowerBomb(CGame* game);

    /// Accepts bomb counter visitor
    ///\param visitor being accepted
    ///\returns true if tower is inside game area
    virtual bool Accept(CBombCounter* visitor) override { return GetX() < 1056; }

    virtual void Update(double elapsed) override;

    void Blast();

    virtual void Draw(Gdiplus::Graphics* graphics);

    /// destructor
    virtual ~CTowerBomb() {};

    virtual void SetIndex(int) override;

    virtual bool WillPop(double, double) override;

    /// getter from time after explode
    ///\returns mTimeAfterExplode
    virtual double GetTimeAfterExplode() override { return mTimeAfterExplode; }
private:
    /// Time left until bomb will explode
    double mTimeInExplode;
    /// Time between blasts
    double mTimeBetweenExplodes;
    /// checks if tower is blasting or not
    bool mBlast;
    ///  Time after explosion has started
    double mTimeAfterExplode;


};

