#include <sstream>
#include "pch.h"
#include "Score.h"
#include "Game.h"


using namespace std;
using namespace Gdiplus;


/*
* Constructor
*/
CScore::CScore()
{
	
}



/*
*
*  Destructor
*/
CScore::~CScore()
{
}

void CScore::Draw(Gdiplus::Graphics* graphics)
{
	FontFamily fontFamily(L"Arial");
	Gdiplus::Font font(&fontFamily, 40);

	SolidBrush yellow(Color(255, 255, 0));
	graphics->DrawString(L"Score", -1,
		&font, PointF(CGame::GridSpacing * 15.5, CGame::GridSpacing * 7), &yellow);
	std::wstring value = to_wstring(mScore);
	const WCHAR* out = value.c_str();

	graphics->DrawString( out, -1,
		&font, PointF(1068, 520), &yellow);
}
