/**
 * \file BlueBalloon.h
 *
 * \author Shizuka
 * 
 * Class that represents a Blue Balloon in level 3
 *
 */

#pragma once

#include "Balloon.h"
#include <vector>
#include "Score.h"
/**This class is derived from CBalloon and instead of popping 
* this balloon, user objective is to protect it.
*/
class CBlueBalloon : public CBalloon
{
public:
    /// constructor
    ///\param game of which balloon will be a part of
    CBlueBalloon(CGame* game) : CBalloon(game) {};

    ///  Default constructor (disabled)
    CBlueBalloon() = delete;

    ///  Copy constructor (disabled)
    CBlueBalloon(const CBlueBalloon&) = delete;

    virtual void Popped(); ///< function that handles score after balloon is popped
    virtual void Passed(); ///< function that handles score after balloon passes

    /// empty destructor
    ~CBlueBalloon() {}
};


