/**
 * \file GoButtonVisit.h
 *
 * \author Shizuka
 *
 * Visitor class for the Go BUtton
 *
 */

#pragma once
#include "ItemVisitor.h"

 /**
 *  Visitor class for the Go Button
 */
class CGoButtonVisit :
    public CItemVisitor
{
public:
    /// Getter of mgo
    ///\returns mgo class pointer of CGoButton
    CGoButton* GetGo() { return mgo; }
private:
    /// Visitor Setter that sets mgo to go
    ///\param go the value mgo is set to
    void VisitGo(CGoButton* go) { mgo = go; }

    CGoButton* mgo; ///< CGoButton class pointer
};

