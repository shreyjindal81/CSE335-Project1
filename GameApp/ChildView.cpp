/**
 * \file ChildView.cpp
 *
 * \author Shizuka
 *
 */



// ChildView.cpp : implementation of the CChildView class
//

#include "pch.h"
#include "DoubleBufferDC.h"
#include "GameApp.h"
#include "ChildView.h"
#include "Tile.h"
#include "TileLandscape.h"
#include "TileBuilding.h"
#include "Balloon.h"
#include <sstream>
#include "Tower.h"
#include "XmlLoader.h"
#include "ItemVisitor.h"
#include "RoadVisit.h"
#include "GoButtonVisit.h"
#include "Dart.h"
#include "GoButton.h"
#include "RoadTile.h"
#include "Tower8.h"
#include "TowerRing.h"
#include "RingVisitor.h"
#include "TowerVisit.h"
#include "gdipluseffects.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include "TowerRing.h"
#include "TowerBomb.h"
#include "BombCounter.h"

using namespace Gdiplus;
using namespace std;

/// Frame duration in milliseconds
const int FrameDuration = 30;


/// Initial tile X location
const int InitialX = static_cast<unsigned __int64>(CGame::GridSpacing) * 0;

/// Initial tile Y location
const int InitialY = static_cast<unsigned __int64>(CGame::GridSpacing) * 1;




/**
 * Constructor
 */
CChildView::CChildView()
{
    srand((unsigned int)time(nullptr));

}

/**
 * Destructor
 */
CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
    ON_WM_PAINT()
    ON_WM_ERASEBKGND()
    ON_WM_LBUTTONUP()
    ON_WM_LBUTTONDOWN()
    ON_WM_MOUSEMOVE()
    ON_WM_TIMER()


    ON_COMMAND(ID_LEVELS_LEVEL0, &CChildView::OnLevelsLevel0)
    ON_COMMAND(ID_LEVELS_LEVEL1, &CChildView::OnLevelsLevel1)
    ON_COMMAND(ID_LEVELS_LEVEL2, &CChildView::OnLevelsLevel2)
    ON_COMMAND(ID_LEVELS_LEVEL3, &CChildView::OnLevelsLevel3)
    ON_COMMAND(ID_FILE_SAVEAS32798, &CChildView::OnFileSaveas)
END_MESSAGE_MAP()



/**
* This function is called before the window is created.
* \param cs A structure with the window creation parameters
* \returns TRUE
*/
BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs)
{
    if (!CWnd::PreCreateWindow(cs))
        return FALSE;

    cs.dwExStyle |= WS_EX_CLIENTEDGE;
    cs.style &= ~WS_BORDER;
    cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS,
        ::LoadCursor(NULL, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1), NULL);

    return TRUE;
}

/**
* This function is called to draw in the window.
*
* This function is called in response to a drawing message
* whenever we need to redraw the window on the screen.
* It is responsible for painting the window.
*/
void CChildView::OnPaint()
{
    CPaintDC paintDC(this);     // device context for painting
    CDoubleBufferDC dc(&paintDC); // device context for painting


    Graphics graphics(dc.m_hDC);

    graphics.Clear(Color(0, 0, 0));

    if (mFirstDraw)
    {
        mFirstDraw = false;
        SetTimer(1, FrameDuration, nullptr);

        /*
        * Initialize the elapsed time system
        */
        LARGE_INTEGER time, freq;
        QueryPerformanceCounter(&time);
        QueryPerformanceFrequency(&freq);

        mLastTime = time.QuadPart;
        mTimeFreq = double(freq.QuadPart);

        LoadLevel1();

    }

    /*
    * Compute the elapsed time since the last draw
    */
    LARGE_INTEGER time;
    QueryPerformanceCounter(&time);
    long long diff = time.QuadPart - mLastTime;
    double elapsed = double(diff) / mTimeFreq;
    mLastTime = time.QuadPart;
    if (/*mLvl1Elapsed > 270*/ true) {

        CGoButtonVisit visitor;
        mGame.Accept(&visitor);
        auto go = visitor.GetGo();



        if (mGo) {

            go->SetItemToggle(false);

            mGame.Update(elapsed);
        }
    }




    // Get the size of the window
    CRect rect;
    GetClientRect(&rect);
    /*
     * Actually Draw the game
     */
    mGame.OnDraw(&graphics, rect.Width(), rect.Height());

    CGoButtonVisit visitor;
    mGame.Accept(&visitor);
    auto go = visitor.GetGo();

    if ((mGame.GetBalloonOnScreen() >= 30 || mOnClicklvl0 == true) && mCurrentLvl == 0) {
        mGame.SetBalloonOnScreen(30);

        auto x = mGame.GetBalloonOnScreen();
        LoadLevel0();
        AddGoButton(L"button-go.png", static_cast<unsigned __int64>(CGame::GridSpacing) * 17, static_cast<unsigned __int64>(CGame::GridSpacing) * 12);
        CGoButtonVisit visitor;
        mGame.Accept(&visitor);
        auto go = visitor.GetGo();
        go->SetItemToggle(false);

        mLvl0Elapsed += elapsed;

        if (mLvl0Elapsed < 3) {

            mGame.BeginPopup(&graphics, L"Level 0 Begin");
            if (mLoadToggle0 == 0) {
                LoadLevel0();
                mLoadToggle0 = 1;
            }
        }
        if (mLvl0Elapsed > 3) {
            mGame.NextLvl();
            mCurrentLvl = 1;
            go->SetItemToggle(true) ;

        }
    }

    if ((mGame.GetBalloonOnScreen() >= 30 || mOnClicklvl0 == false) && mLvl1Elapsed < 3 && mCurrentLvl == 1) {
        mLvl1Elapsed += elapsed;
        if (mOnClicklvl0 && mLvl1Elapsed < 1) {
            mGame.BeginPopup(&graphics, L"Level Complete");
        }
        else {
            mGame.BeginPopup(&graphics, L"Level 1 Begin");
            if (mOnClicklvl0) {
                LoadLevel1();
                mOnClicklvl0 = false;
            }
        }
        go->SetItemToggle(false);

    }
    else if ((mLvl1Elapsed > 3)  && mCurrentLvl == 1) {
        CGoButtonVisit visitor;
        mGame.Accept(&visitor);
        auto go = visitor.GetGo();
        if (go != nullptr) { go->SetItemToggle(true) ; }
        mCurrentLvl = 2;
        mGame.NextLvl();
        mOnClicklvl2 = false;
        mOnClicklvl3 = false;

    }


    if ((mGame.GetBalloonOnScreen() >= 30 || mOnClicklvl2 == true) && mCurrentLvl == 2) {
        mGame.SetBalloonOnScreen(30);


        auto x = mGame.GetBalloonOnScreen();
        LoadLevel2();
        AddGoButton(L"button-go.png", static_cast<unsigned __int64>(CGame::GridSpacing) * 17, static_cast<unsigned __int64>(CGame::GridSpacing) * 12);
        CGoButtonVisit visitor;
        mGame.Accept(&visitor);
        auto go = visitor.GetGo();
        go->SetItemToggle(false);

        mLvl2Elapsed += elapsed;
        if (mLvl2Elapsed < 1 && !mOnClicklvl2) {
            mGame.BeginPopup(&graphics, L"Level Complete");
        }
        else if (mLvl2Elapsed < 3 ) {
            mGame.BeginPopup(&graphics, L"Level 2 Begin");
            if (mLoadToggle2 == 0) {
                LoadLevel2();
                mLoadToggle2 = 1;
            }
        }
        if (mLvl2Elapsed > 3) {
            mGame.NextLvl();
            mCurrentLvl = 3;
            go->SetItemToggle(true) ;
            mOnClicklvl2 = false;

        }
    }

    if ((mGame.GetBalloonOnScreen() >= 30 || mOnClicklvl3 == true) && mCurrentLvl == 3) {
        mGame.SetBalloonOnScreen(30);
        LoadLevel3();
        AddGoButton(L"button-goS.png", static_cast<unsigned __int64>(CGame::GridSpacing) * 17, static_cast<unsigned __int64>(CGame::GridSpacing) * 12);
        CGoButtonVisit visitor;
        mGame.Accept(&visitor);
        auto go = visitor.GetGo();
        go->SetItemToggle(false);

        mLvl3Elapsed += elapsed;
        if (mLvl3Elapsed < 1 && !mOnClicklvl3) {
            mGame.BeginPopup(&graphics, L"Level Complete");

        }
        else if (mLvl3Elapsed < 3 ) {
            mGame.BeginPopup(&graphics, L"Level 3 Begin");
            if (mLoadToggle3 == 0) {
                LoadLevel3();
                mLoadToggle3 = 1;
            }

        }
        if (mLvl3Elapsed > 3) {
            mGame.NextLvl();
            mCurrentLvl = 4;
            go->SetItemToggle(true) ;
            mOnClicklvl3 = false;

        }
    }
    if (mGame.GetBalloonOnScreen() >= 30 && mCurrentLvl == 4) {


        mGame.BeginPopup(&graphics, L"Game Over");
        go->SetItemToggle(false);


    }
    void Tint();

}


/**
*  Erase the background prior to drawing.
*
* We return true so this does nothing. This prevents the flicker
* of a repaint of white before actual drawing.
*
* \param pDC A device context to draw on
* \returns TRUE
*/
BOOL CChildView::OnEraseBkgnd(CDC* pDC)
{
    // This disabled the default background erase
    return TRUE;
}



/**  Called when there is a left mouse button press
* \param nFlags Flags associated with the mouse button press
* \param point Where the button was pressed
*/
void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
    // creating virtual x and y
    double oX = (point.x - mGame.GetMXOffset()) / mGame.GetMScale();
    double oY = (point.y - mGame.GetMYOffset()) / mGame.GetMScale();

    double ux = (static_cast<unsigned __int64>(CGame::GridSpacing) * 17);//- mGame.GetMXOffset()) / mGame.GetMScale();
    double uy = (static_cast<unsigned __int64>(CGame::GridSpacing) * 12);// -mGame.GetMYOffset()) / mGame.GetMScale();

    CGoButtonVisit visitor;
    mGame.Accept(&visitor);

    auto go = visitor.GetGo();
    if (go != nullptr) {
        auto x = ux;// -(go->GetWidth() / 2 - mGame.GetMXOffset()) / mGame.GetMScale();
        auto y = ux + (go->GetWidth() / 2 - mGame.GetMXOffset()) / mGame.GetMScale();
        if (oX > ux - go->GetWidth() / 2 && oX < ux + go->GetWidth() / 2 && oY > uy - go->GetHeight() / 2 && oY < uy + go->GetHeight() / 2) {
            mGo = true;
            go->SetItemToggle(false);
            mGame.MakeStationary();
        }
    }
    if (mGame.HitTest(oX, oY) != nullptr)
    {

        if (mGame.HitTest(oX, oY)->GetDrag()) {
            if (go != nullptr)
            {
                if (go->GetItemToggle() == true) { mGrabbedItem = mGame.HitTest(oX, oY); }
            }


        }
        else {
            mGrabbedItem = nullptr;
        }

        if (mGrabbedItem != nullptr)
        {
            mGame.MoveToFront(mGrabbedItem);
            Invalidate();
            mInitialGrabbedItemX = mGrabbedItem->GetX();
            mInitialGrabbedItemY = mGrabbedItem->GetY();
            mGrabbedItem->SetPlaced(false);

        }
    }


}

/**  Called when the left mouse button is released
* \param nFlags Flags associated with the mouse button release
* \param point Where the button was pressed
*/
void CChildView::OnLButtonUp(UINT nFlags, CPoint point)
{
    if (mGrabbedItem != nullptr)
    {
        // creating virtual x and y
        double oX = (point.x - mGame.GetMXOffset()) / mGame.GetMScale();
        double oY = (point.y - mGame.GetMYOffset()) / mGame.GetMScale();

        auto currentTile = mGame.NearestGrass(oX, oY);
        if (currentTile != nullptr)
        {
            mGrabbedItem->SetLocation(currentTile->GetX(), currentTile->GetY());
            mGame.SortTiles();
            mGame.MoveToFront(mGrabbedItem);
            CBombCounter visitor;
            if (mGrabbedItem->Accept(&visitor)) {
                mGrabbedItem->SetIndex(mGame.Accept(&visitor));
            }
            CTowerVisit visitor2;
            mGrabbedItem->SetPlaced(true);
            mGrabbedItem = nullptr;
        }
        else {
            mGrabbedItem->SetLocation(mInitialGrabbedItemX, mInitialGrabbedItemY);
            mGame.SortTiles();
            mGrabbedItem = nullptr;
        }

    }
}


/**  Called when the mouse is moved
* \param nFlags Flags associated with the mouse movement
* \param point Where the button was pressed
*/
void CChildView::OnMouseMove(UINT nFlags, CPoint point)
{
    // creating virtual x and y
    double oX = (point.x - mGame.GetMXOffset()) / mGame.GetMScale();
    double oY = (point.y - mGame.GetMYOffset()) / mGame.GetMScale();

    // See if an item is currently being moved by the mouse
    if (mGrabbedItem != nullptr)
    {
        // If an item is being moved, we only continue to 
        // move it while the left button is down.
        if (nFlags & MK_LBUTTON)
        {
            mGrabbedItem->SetLocation(oX, oY);
        }


        // Force the screen to redraw
        Invalidate();
    }

}


/**
*  Handle timer events
* \param nIDEvent The timer event ID
*/
void CChildView::OnTimer(UINT_PTR nIDEvent)
{
    Invalidate();
    CWnd::OnTimer(nIDEvent);
}

/**
*  Add a CTileLandscaping tile to the drawing.
* \param file The file for the landscape image
*/
void CChildView::AddLandscape(const std::wstring& file)
{
    auto tile = make_shared<CTileLandscape>(&mGame);

    tile->SetImage(file);
    tile->SetLocation(InitialX, InitialY);
    mGame.Add(tile);

    Invalidate();
}


/**
*  Add a CTileBuilding tile to the drawing.
* \param file The file for the Building image
*/
void CChildView::AddBuilding(const std::wstring& file)
{
    auto tile = make_shared<CTileBuilding>(&mGame);

    tile->SetImage(file);
    tile->SetLocation(InitialX, InitialY);
    mGame.Add(tile);

    Invalidate();
}


/**
*  Add a CTowerRing tile to the drawing.
* \param file The file for the Ring Tower image
* \param x x location of Ring Tower
* \param y y location of Ring Tower
*/
void CChildView::AddTowerRing(const std::wstring& file, double x, double y)
{
    auto tile = make_shared<CTowerRing>(&mGame);

    tile->SetImage(file);
    tile->SetLocation(x, y);
    mGame.Add(tile);

    Invalidate();
}



/**
*  Add a CTower8 tile to the drawing.
* \param file The file for the Tower8 image
* \param x x location of Tower8
* \param y y location of Tower8
*/
void CChildView::AddTower8(const std::wstring& file, double x, double y)
{
    auto tile = make_shared<CTower8>(&mGame);

    tile->SetImage(file);
    tile->SetLocation(x, y);
    mGame.Add(tile);

    Invalidate();
}


/**
*  Add a CTowerBomb tile to the drawing.
* \param file The file for the Bomb Tower image
* \param x x location of Bomb Tower
* \param y y location of Bomb Tower
*/
void CChildView::AddTowerBomb(const std::wstring& file, double x, double y)
{
    auto tile = make_shared<CTowerBomb>(&mGame);

    tile->SetImage(file);
    tile->SetLocation(x, y);
    mGame.Add(tile);

    Invalidate();
}


/**
*  Add a CTileBuilding tile to the drawing.
* \param file The file for the Road image
*/
void CChildView::AddRoad(const std::wstring& file)
{
    auto tile = make_shared<CTileBuilding>(&mGame);

    tile->SetImage(file);
    tile->SetLocation(InitialX, InitialY);
    mGame.Add(tile);

    Invalidate();
}



/**
*  Add a CDart tile to the drawing.
* \param file The file for the dart image
*/
void CChildView::AddDart(const std::wstring& file)
{
    auto dart = make_shared<CDart>(&mGame);

    dart->SetImage(file);
    dart->SetLocation(InitialX, InitialY);
    mGame.Add(dart);

    Invalidate();
}


/**
*  Add a CDart tile to the drawing.
* \param file The file for the special dart image
* \param x x location of special dart
* \param y y location of special dart
*/
void CChildView::AddSpecialDart(const std::wstring& file, int x, double y)
{
    auto dart = make_shared<CDart>(&mGame);

    dart->SetImage(file);
    dart->SetLocation(x, y);
    mGame.Add(dart);

    Invalidate();
}


/**
*  Add a CGoButton tile to the drawing.
* \param file The file for the Go Button image
* \param x x location of Go Button
* \param y y location of Go Button
*/
void CChildView::AddGoButton(const std::wstring& file, double x, double y)
{
    auto go = make_shared<CGoButton>(&mGame);

    go->SetImage(file);
    go->SetLocation(x, y);
    mGame.Add(go);

    Invalidate();
}


/**
 * Load Level 0 menu option handler
 */
void CChildView::OnLevelsLevel0()
{
    mLvl0Elapsed = 0;

    mLvl1Elapsed = 0;
    mLvl2Elapsed = 0;
    mLvl3Elapsed = 0;
    mCurrentLvl = 0;
    mGame.NextLvl();
    mOnClicklvl0 = true;
    mOnClicklvl3 = false;
    mOnClicklvl2 = false;

}


/**
 * Load Level 1 menu option handler
 */
void CChildView::OnLevelsLevel1()
{
    mLvl1Elapsed = 0;
    mLvl2Elapsed = 0;
    mLvl3Elapsed = 0;
    mFirstDraw = true;
    mCurrentLvl = 1;
    mGame.NextLvl();
    mOnClicklvl2 = false;
    mOnClicklvl3 = false;
    mOnClicklvl0 = false;

}


/**
 * Load Level 2 menu option handler
 */
void CChildView::OnLevelsLevel2()
{
    mLvl1Elapsed = 1000;
    mLvl2Elapsed = 0;
    mLvl3Elapsed = 0;
    mOnClicklvl2 = true;
    mGame.NextLvl();
    mCurrentLvl = 2;
    mOnClicklvl3 = false;
    mOnClicklvl0 = false;
}


/**
 * Load Level 3 menu option handler
 */
void CChildView::OnLevelsLevel3()
{
    mLvl1Elapsed = 1000;
    mLvl2Elapsed = 1000;
    mLvl3Elapsed = 0;
    mGame.NextLvl();
    mOnClicklvl3 = true;
    mOnClicklvl2 = false;

    mCurrentLvl = 3;
}



/**
 * Load Level 1 in the game
 */
void CChildView::LoadLevel1()
{
    mGo = false;
    mGame.SetLevel3Toggle(false);

    mGame.Clear();
    std::wstring filename = L"level1.xml";
    mGame.XmlLoad(filename);
    std::shared_ptr<CXmlLoader> loader = mGame.GetLoad();

    loader->AddItems(mGame);
    for (int i = 0; i < 15; i++)
    {
        AddTower8(L"tower8.png", static_cast<unsigned __int64>(CGame::GridSpacing) * 17, static_cast<unsigned __int64>(CGame::GridSpacing) * 2);
        AddTowerBomb(L"tower-bomb.png", static_cast<unsigned __int64>(CGame::GridSpacing) * 17, static_cast<unsigned __int64>(CGame::GridSpacing) * 4);
        AddTowerRing(L"tower-rings.png", static_cast<unsigned __int64>(CGame::GridSpacing) * 17, static_cast<unsigned __int64>(CGame::GridSpacing) * 6);
    }
    AddGoButton(L"button-go.png", static_cast<unsigned __int64>(CGame::GridSpacing) * 17, static_cast<unsigned __int64>(CGame::GridSpacing) * 12);
    CGoButtonVisit visitor;
    mGame.Accept(&visitor);
    auto go = visitor.GetGo();
    go->SetItemToggle(false);

}

/**
 * Load Level 2 in the game
 */
void CChildView::LoadLevel2()
{
    mGo = false;
    mGame.SetLevel3Toggle(false);

    mGame.Clear();
    std::wstring filename = L"level2.xml";
    mGame.XmlLoad(filename);
    std::shared_ptr<CXmlLoader> loader = mGame.GetLoad();
    loader->AddItems(mGame);
    for (int i = 0; i < 15; i++)
    {
        AddTower8(L"tower8.png", static_cast<unsigned __int64>(CGame::GridSpacing) * 17, static_cast<unsigned __int64>(CGame::GridSpacing) * 2);
        AddTowerBomb(L"tower-bomb.png", static_cast<unsigned __int64>(CGame::GridSpacing) * 17, static_cast<unsigned __int64>(CGame::GridSpacing) * 4);
        AddTowerRing(L"tower-rings.png", static_cast<unsigned __int64>(CGame::GridSpacing) * 17, static_cast<unsigned __int64>(CGame::GridSpacing) * 6);
    }


}

/**
 * Load Level 3 in the game
 */
void CChildView::LoadLevel3()
{
    mGo = false;
    mGame.SetLevel3Toggle(true);

    mGame.Clear();
    std::wstring filename = L"level3.xml";
    mGame.XmlLoad(filename);
    std::shared_ptr<CXmlLoader> loader = mGame.GetLoad();
    loader->AddItems(mGame);
    for (int i = 0; i < 2; i++)
    {
        AddTower8(L"tower8S.png", static_cast<unsigned __int64>(CGame::GridSpacing) * 17, static_cast<unsigned __int64>(CGame::GridSpacing) * 2);
        AddTowerBomb(L"tower-bombS.png", static_cast<unsigned __int64>(CGame::GridSpacing) * 17, static_cast<unsigned __int64>(CGame::GridSpacing) * 4);
        AddTowerRing(L"tower-ringsS.png", static_cast<unsigned __int64>(CGame::GridSpacing) * 17, static_cast<unsigned __int64>(CGame::GridSpacing) * 6);
        AddSpecialDart(L"ddd.png", static_cast<unsigned __int64>(CGame::GridSpacing) * 17, static_cast<unsigned __int64>(CGame::GridSpacing) * 0.5);
    }
}

/**
 * Load Level 0 in the game
 */
void CChildView::LoadLevel0()
{
    mGo = false;
    mGame.SetLevel3Toggle(false);

    mGame.Clear();
    std::wstring filename = L"level0.xml";
    mGame.XmlLoad(filename);
    std::shared_ptr<CXmlLoader> loader = mGame.GetLoad();
    loader->AddItems(mGame);
    for (int i = 0; i < 15; i++)
    {
        AddTower8(L"tower8.png", static_cast<unsigned __int64>(CGame::GridSpacing) * 17, static_cast<unsigned __int64>(CGame::GridSpacing) * 2);
        AddTowerBomb(L"tower-bomb.png", static_cast<unsigned __int64>(CGame::GridSpacing) * 17, static_cast<unsigned __int64>(CGame::GridSpacing) * 4);
        AddTowerRing(L"tower-rings.png", static_cast<unsigned __int64>(CGame::GridSpacing) * 17, static_cast<unsigned __int64>(CGame::GridSpacing) * 6);
    }
    
}


/**
 * Handler for the File/Save As menu option
 */
void CChildView::OnFileSaveas()
{
    CFileDialog dlg(false,  // false = Save dialog box
        L".game",           // Default file extension
        nullptr,            // Default file name (none)
        OFN_OVERWRITEPROMPT,      // Flags (warn it overwriting file)
        L"Game Files (*.game)|*.game|All Files (*.*)|*.*||"); // Filter

    if (dlg.DoModal() != IDOK)
        return;

    wstring filename = dlg.GetPathName();
    mGame.Save(filename);
}
