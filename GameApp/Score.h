/**
 * \file Score.h
 *
 * \author Shizuka
 *
 * Class that represents the Score in the game
 * 
 * class keeps track of the score as the game progresses, updates it and displays it
 *
 */

#pragma once

/**
*  The Scorecard that computes and displays current score
*/
class CScore
{
public:
    /// Constructor
    CScore();

    ///  Copy constructor (disabled)
    CScore(const CScore&) = delete;

    /// Destructor
    ~CScore();

    /// Adds Score to member mScore attributes
    ///\param x The score to be added
    void AddScore(int x) { mScore += x; mBalloonCount++; };

    /// Subtracts score from member mScore attribute
    ///\param x The score to be added
    void SubtractScore(int x) { mScore -= x; mBalloonCount++; };

    /// Getter of mScore
    ///\returns mScore Current score of the game
    auto GetScore() { return mScore; };

    /// Draws the Score on the game window
    ///\param graphics Graphics pointer
    void Draw(Gdiplus::Graphics* graphics);

    /// Setter of mBalloonCount
    ///\param x The value mBalloonCount is set to
    void SetBalloonCount(int x) { mBalloonCount = x; }

    /// Getter of mBalloonCount
    ///\returns mBalloonCount Current Balloon count of the game
    int GetBalloonCount() { return mBalloonCount; }

    /// Resets mScore and mBalloonCount to 0 each
    void ResetScore() { mScore = 0; mBalloonCount = 0; }
private:

    int mScore = 0; ///< stores current score of the game
    int mBalloonCount = 0; ///< stores current Balloon count in the game
};

