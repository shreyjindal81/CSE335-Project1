#include "pch.h"
#include "BeginLevel.h"
#include "Game.h"


using namespace std;
using namespace Gdiplus;


/*
* Constructor
*/
CBeginLevel::CBeginLevel()
{

}

/**
*  Destructor
*/
CBeginLevel::~CBeginLevel()
{
}

void CBeginLevel::Draw(Gdiplus::Graphics* graphics, const WCHAR* level)
{
    std::wstring opo = level;

    if (opo == L"Level 3 Begin") {
        FontFamily fontFamily(L"Viner Hand ITC");

        SolidBrush brown(Color(139, 0 , 0));

        Gdiplus::Font font(&fontFamily, 50);
        graphics->DrawString(L" Happy Halloween!!", -1,
            &font, PointF(70, 250), &brown);
    }

    
    FontFamily fontFamily(L"Arial Black");
    Gdiplus::Font font(&fontFamily, 70);
    
    if (opo == L"Level 3 Begin")
    {
        SolidBrush brown(Color(255, 204, 0));
        graphics->DrawString(level, -1,
            &font, PointF(70, 380), &brown);
    }
    else
    { 
        SolidBrush brown(Color(150, 80, 0)); 
        graphics->DrawString(level, -1,
            &font, PointF(70, 380), &brown);
    }


    if (opo == L"Level 3 Begin") {
        FontFamily fontFamily(L"Script MT Bold");

        SolidBrush brown(Color(255, 255, 255));

        Gdiplus::Font font(&fontFamily, 40);
        graphics->DrawString(L"Save your Pumpkins!!\n   Use the Witches!!", -1,
            &font, PointF(180, 550), &brown);

    }
}