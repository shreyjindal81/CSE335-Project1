/**
 * \file DartBalloonVisitor.h
 *
 * \author Shizuka
 *
 * Visitor class for darts and balloons
 *
 */

#pragma once
#include <memory>
#include <vector>

class CGame;
class CItem;
class CBalloon;
class CDart;


/// Visitor class for darts and balloons
class CDartBalloonVisitor
{
public:
	~CDartBalloonVisitor() {}; ///<destructor

	/// visits balloon and adds its it to its vector of balloons
	///\param b the balloon to be added
	virtual void VisitBalloon(CItem* b) { balloons.push_back(b); }; 

	/// visits dart and adds its it to its vector of darts
	///\param b the dart to be added
	virtual void VisitDart(CDart* b) { darts.push_back(b); };

	/// Getter of balloons
	///\returns balloons vector of all balloons visited
	auto GetBalloons() { return balloons; };

	/// Getter of darts
	///\returns darts vector of all darts visited
	auto GetDarts() { return darts; };

private:
	std::vector <CItem*> balloons; ///< vector of balloons
	std::vector <CDart*> darts; ///< vector of darts
};

