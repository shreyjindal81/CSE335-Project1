#include "pch.h"
#include "RoadTile.h"
#include "Balloon.h"
#include <algorithm>
#include <iostream>
#include "RoadVisit.h"
#include "ChildView.h"

using namespace std;

/*
* Constructor
*/
CRoadTile::CRoadTile(CGame* game) : CTile(game)
{
    SetToggle(true);
}



/**
*  Destructor
*/
CRoadTile::~CRoadTile()
{
}

void CRoadTile::EraseBalloon(std::shared_ptr<CBalloon> balloon) {

    auto loc = find(::begin(mBalloons), ::end(mBalloons), balloon);
    if (loc != ::end(mBalloons))
    {
        mBalloons.erase(loc);
    }

}

void CRoadTile::Update(double elapsed)
{
    std::vector<std::shared_ptr<CBalloon> > BalloonsToErase;
    for (auto balloon : mBalloons) {
        if (balloon->GetPopped()) {
            BalloonsToErase.push_back(balloon);
            continue;
        }
        if (balloon->GetT() >= 1) {
            if (mTypeTile == L"i004") {
                if ((mAdjacentRoadTile->GetTypeTile() == L"i001") || (mAdjacentRoadTile->GetTypeTile() == L"i005")) {
                    if (mAdjacentRoadTile->GetX() - this->GetX() < 0) {
                        balloon->SetIsForward(false);
                    }
                }
                if (mAdjacentRoadTile->GetTypeTile() == L"i006") {
                    if (mAdjacentRoadTile->GetX() - this->GetX() == 0) {
                        balloon->SetIsForward(false);
                    }
                }

                if ((mAdjacentRoadTile->GetTypeTile() == L"i005")) {
                    if ((mAdjacentRoadTile->GetY() - this->GetY() > 0) && (mAdjacentRoadTile->GetX() - this->GetX() == 0)) {
                        balloon->SetIsForward(false);
                    }
                }
            }
            if (mTypeTile == L"i005") {
                if ((mAdjacentRoadTile->GetTypeTile() == L"i003")) {
                    if (mAdjacentRoadTile->GetX() - this->GetX() == 0) {
                        balloon->SetIsForward(true);
                    }
                }
                if ((mAdjacentRoadTile->GetTypeTile() == L"i004")) {
                    if (mAdjacentRoadTile->GetX() - this->GetX() == 0) {
                        balloon->SetIsForward(true);
                    }
                }
                if ((mAdjacentRoadTile->GetTypeTile() == L"i002")) {
                    if (mAdjacentRoadTile->GetX() - this->GetX() == 0) {
                        balloon->SetIsForward(true);
                    }
                }

            }



            if (mAdjacentRoadTile != nullptr) {

                if ((mAdjacentRoadTile->GetTypeTile() == L"i001") || (mAdjacentRoadTile->GetTypeTile() == L"i002") || (mAdjacentRoadTile->GetTypeTile() == L"i004") || (mAdjacentRoadTile->GetTypeTile() == L"i003")) {
                    balloon->SetT(balloon->GetT() - 1);
                }
                else {
                    balloon->SetT(balloon->GetT() - 0.5);
                }
                mAdjacentRoadTile->AddBalloon(balloon);

            }
            else
            {

                balloon->Passed();
                balloon->SetItemToggle(false);

            }
            BalloonsToErase.push_back(balloon);
            continue;

        }

        else {

            if (mTypeTile == L"i001") {
                this->PlaceBalloonEW(balloon);

            }
            else if (mTypeTile == L"i002") {
                if (mAdjacentRoadTile->GetTypeTile() == L"i002") {
                    if (mAdjacentRoadTile->GetY() - this->GetY() < 0) {
                        balloon->SetIsForward(true);
                    }
                    else {
                        balloon->SetIsForward(false);

                    }
                }
                this->PlaceBalloonNS(balloon);

            }
            else if (mTypeTile == L"i003") {

                if ((mAdjacentRoadTile->GetTypeTile() == L"i002")) {
                    if (mAdjacentRoadTile->GetX() - this->GetX() == 0) {
                        balloon->SetIsForward(false);
                    }
                }
                this->PlaceBalloonSE(balloon);

            }
            else if (mTypeTile == L"i004") {


                if ((mAdjacentRoadTile->GetTypeTile() == L"i002")) {
                    if (mAdjacentRoadTile->GetY() - this->GetY() > 0) {
                        balloon->SetIsForward(false);
                    }
                }

                if ((mAdjacentRoadTile->GetTypeTile() == L"i005")) {
                    if (mAdjacentRoadTile->GetY() - this->GetY() > 0) {
                        balloon->SetIsForward(false);
                    }
                }

                if ((mAdjacentRoadTile->GetTypeTile() == L"i006")) {
                    if (mAdjacentRoadTile->GetX() - this->GetX() == 0) {
                        balloon->SetIsForward(false);
                    }
                }



                this->PlaceBalloonSW(balloon);

            }
            else if (mTypeTile == L"i005") {

                if ((mAdjacentRoadTile->GetTypeTile() == L"i001")) {
                    if (mAdjacentRoadTile->GetX() - this->GetX() > 0) {
                        balloon->SetIsForward(true);
                    }
                }
                if ((mAdjacentRoadTile->GetTypeTile() == L"i006")) {
                    if (mAdjacentRoadTile->GetX() - this->GetX() > 0) {
                        balloon->SetIsForward(true);
                    }
                }

                if ((mAdjacentRoadTile->GetTypeTile() == L"i004")) {
                    if (mAdjacentRoadTile->GetX() - this->GetX() > 0) {
                        balloon->SetIsForward(true);
                    }
                }

                this->PlaceBalloonNE(balloon);

            }
            else if (mTypeTile == L"i006") {
                if (mAdjacentRoadTile->GetTypeTile() == L"i001") {
                    if (mAdjacentRoadTile->GetX() - this->GetX() < 0) {
                        balloon->SetIsForward(false);
                    }
                }
                this->PlaceBalloonNW(balloon);


            }

            balloon->SetT(balloon->GetT() + 2 * (elapsed));
        }

    }
    for (unsigned int i = 0; i < BalloonsToErase.size(); i++) {
        EraseBalloon(BalloonsToErase[i]);
    }



}

/**
 * Place the balloon on the North/West tile, where
 * forward motion is assumed to be from a North entrance
 * to a West exit.
 * @param balloon The balloon we are placing.
 */
void CRoadTile::PlaceBalloonEW(std::shared_ptr<CBalloon> balloon)
{
    // Current t value for this balloon
    auto t = balloon->GetT();

    // Initially set to the center of the file in each dimension
    auto y = GetY() + GetHeight() / 2 - 32;
    auto x = GetX() + GetWidth() / 2 - 32;

    if (!balloon->IsForward())
    {
        t = 0.5 - t;
    }


    if (t <= 1)
    {
        // First half of path
        // Moving vertically down
        x = GetX() + t * GetWidth();
    }

    balloon->SetLocation(x, y);
}
/**
 * Place the balloon on the North/West tile, where
 * forward motion is assumed to be from a North entrance
 * to a West exit.
 * @param balloon The balloon we are placing.
 */
void CRoadTile::PlaceBalloonNS(std::shared_ptr<CBalloon> balloon)
{
    // Current t value for this balloon
    auto t = balloon->GetT();

    // Initially set to the center of the file in each dimension
    auto y = GetY() + GetHeight() / 2 - 32;
    auto x = GetX() + GetWidth() / 2 - 32;

    if (!balloon->IsForward())
    {
        t = 0.5 - t;
    }

    if (t <= 1)
    {
        // First half of path
        // Moving vertically down
        y = GetY() + (0.5 - t) * GetHeight();
    }


    balloon->SetLocation(x, y);
}

/**
 * Place the balloon on the North/West tile, where
 * forward motion is assumed to be from a North entrance
 * to a West exit.
 * @param balloon The balloon we are placing.
 */
void CRoadTile::PlaceBalloonSE(std::shared_ptr<CBalloon> balloon)
{
    // Current t value for this balloon
    auto t = balloon->GetT();

    // Initially set to the center of the file in each dimension
    auto y = GetY() + GetHeight() / 2 - 32;
    auto x = GetX() + GetWidth() / 2 - 32;

    if (!balloon->IsForward())
    {
        t = 0.5 - t;
    }

    if (t < 0.5)
    {
        // First half of path
        // Moving vertically down
        y = GetY() + (0.5 - t) * GetHeight();
    }
    else
    {
        // Second half of path
        // Moving horizontally right
        x = GetX() - (0.5 - t) * GetWidth();
    }

    balloon->SetLocation(x, y);
}
/**
 * Place the balloon on the North/West tile, where
 * forward motion is assumed to be from a North entrance
 * to a West exit.
 * @param balloon The balloon we are placing.
 */

void CRoadTile::PlaceBalloonSW(std::shared_ptr<CBalloon> balloon)
{
    // Current t value for this balloon
    auto t = balloon->GetT();

    // Initially set to the center of the file in each dimension
    auto y = GetY() + GetHeight() / 2 - 32;
    auto x = GetX() + GetWidth() / 2 - 32;

    if (!balloon->IsForward())
    {
        t = 0.5 - t;
    }

    if (t < 0.5)
    {
        // First half of path
        // Moving vertically down
        y = GetY() + (0.5 - t) * GetHeight();
    }
    else
    {
        // Second half of path
        // Moving horizontally left
        x = GetX() + (0.5 - t) * GetWidth();
    }

    balloon->SetLocation(x, y);
}

/**
 * Place the balloon on the North/West tile, where
 * forward motion is assumed to be from a North entrance
 * to a West exit.
 * @param balloon The balloon we are placing.
 */
void CRoadTile::PlaceBalloonNE(std::shared_ptr<CBalloon> balloon)
{
    // Current t value for this balloon
    auto t = balloon->GetT();

    // Initially set to the center of the file in each dimension
    auto y = GetY() + GetHeight() / 2 - 32;
    auto x = GetX() + GetWidth() / 2 - 32;

    if (!balloon->IsForward())
    {
        t = 0.5 - t;
    }

    if (balloon->IsForward())
    {

    }

    if (t < 0.5)
    {
        // First half of path
        // Moving vertically down
        y = GetY() + (t)*GetHeight();
    }
    else

    {

        x = GetX() + (t - 0.5) * GetWidth();

    }

    balloon->SetLocation(x, y);
}
/**
 * Place the balloon on the North/West tile, where
 * forward motion is assumed to be from a North entrance
 * to a West exit.
 * @param balloon The balloon we are placing.
 */
void CRoadTile::PlaceBalloonNW(std::shared_ptr<CBalloon> balloon)
{
    // Current t value for this balloon
    auto t = balloon->GetT();

    // Initially set to the center of the file in each dimension
    auto y = GetY() + GetHeight() / 2 - 32;
    auto x = GetX() + GetWidth() / 2 - 32;

    if (!balloon->IsForward())
    {
        t = 0.5 - t;
    }

    if (t < 0.5)
    {
        // First half of path
        // Moving vertically down
        x = GetX() + (t)*GetWidth();

    }
    else
    {
        // Second half of path
        // Moving horizontally left
        y = GetY() + (0.5 - t) * GetHeight();
    }

    balloon->SetLocation(x, y);
}

