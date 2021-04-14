/**
 * \file  Tower8.h
 *
 * \author Shizuka
 *
 * Class that represents Tower8
 *
 */
#pragma once
#include "Tower.h"

#include <memory>
#include <vector>

class CTowerDart;  ///upcall

class CTower8 : public CTower
{
public:
    ///  Default constructor (disabled)
    CTower8() = delete;

    ///  Copy constructor (disabled)
    CTower8(const CTower8&) = delete;

    ///update function
    virtual void Update(double elapsed) override;


    /// Constructor
    ///\param game The game this is the part of
    CTower8(CGame* game);

    /// destructor
    ~CTower8();

    virtual void Draw(Gdiplus::Graphics* graphics) override;


    /// Setter for mPlaced
    ///\param placed The value mPlaced is to be set to
    virtual void SetPlaced(bool placed) { mPlaced = placed; }
    
    /// <summary>
    /// darts added
    /// </summary>
    virtual void AddDarts();

    /// Deletes dart
    ///\ param dart The dart to be deleted
    void DeleteDart(std::shared_ptr<CTowerDart> dart);

    virtual bool WillPop(double, double) override;

private:


    /// list of darts
    std::vector<std::shared_ptr<CTowerDart>> mDartList;
    /// variable
    double mTimeRelease;
    /// variable
    double mT;
    /// variable
    bool mRelease;
    /// variable
    bool mPlaced = false;
};


