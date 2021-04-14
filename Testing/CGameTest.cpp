#include "pch.h"
#include "CppUnitTest.h"
#include <regex>
#include <string>
#include <fstream>
#include <streambuf>

#include <memory.h>

#include "Game.h"
#include "Item.h"
#include "RoadTile.h"
#include "Tile.h"
#include "TileGrass.h"
#include "TileLandscape.h"
#include "TileBuilding.h"
#include "Tower.h"



using namespace std;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Testing
{
    class CTestVisitor : public CItemVisitor
    {
    public:

        virtual void VisitBuilding(CTileBuilding* building) override { mNumBuildings++; }
        virtual void VisitLandscape(CTileLandscape* landscape) override { mNumLandscapes++; }
        virtual void VisitRoad(CRoadTile* road) override { mNumRoad++; }
        virtual void VisitGrass(CTileGrass* grass) override { mNumGrass++; }

        int mNumBuildings = 0;
        int mNumRoad = 0;
        int mNumLandscapes = 0;
        int mNumGrass = 0;
    };
    TEST_CLASS(CGameTest)
    {


    public:
        /**
* Create a path to a place to put temporary files
*/
        wstring TempPath()
        {
            // Create a path to temporary files
            wchar_t path_nts[MAX_PATH];
            GetTempPath(MAX_PATH, path_nts);

            // Convert null terminated string to wstring
            return wstring(path_nts);
        }

        /**
        * Read a file into a wstring and return it.
        * \param filename Name of the file to read
        * \return File contents
        */
        wstring ReadFile(const wstring& filename)
        {
            ifstream t(filename);
            wstring str((istreambuf_iterator<char>(t)),
                istreambuf_iterator<char>());

            return str;
        }



        TEST_METHOD_INITIALIZE(methodName)
        {
            extern wchar_t g_dir[];
            ::SetCurrentDirectory(g_dir);
        }

        TEST_METHOD(TestCGameConstructor)
        {
            CGame game;
        }
        TEST_METHOD(TestCGameVisitor)
        {

            CGame game;

            /// First testing for empty game then add elements
            CTestVisitor visitor;
            game.Accept(&visitor);

            /// Assert 0 since initial value is 0
            Assert::AreEqual(0, visitor.mNumBuildings, L"Visitor number of Buildings");
            Assert::AreEqual(0, visitor.mNumLandscapes, L"Visitor number of Landscapes");
            Assert::AreEqual(0, visitor.mNumGrass, L"Visitor number of Grass");
            Assert::AreEqual(0, visitor.mNumRoad, L"Visitor number of Roads");


            /// Add some tiles of each type
            auto tile1 = std::make_shared<CRoadTile>(&game);
            auto tile2 = std::make_shared<CTileBuilding>(&game);
            auto tile3 = std::make_shared<CTileLandscape>(&game);
            auto tile4 = std::make_shared<CTileGrass>(&game);

            /// Adding 4 of each tiles to the game
            game.Add(tile1);
            game.Add(tile2);
            game.Add(tile3);
            game.Add(tile4);

            /// Test for the added elements
            game.Accept(&visitor);
            Assert::AreEqual(1, visitor.mNumBuildings, L"Visitor number of Buildings");
            Assert::AreEqual(1, visitor.mNumLandscapes, L"Visitor number of Landscapes");
            Assert::AreEqual(1, visitor.mNumGrass, L"Visitor number of Grass");
            Assert::AreEqual(1, visitor.mNumRoad, L"Visitor number of Roads");


        }


        /**  Tests for the GetAdjacent function
 */
        TEST_METHOD(TestCGameAdjacent)
        {
            CGame game;
            int grid = CGame::GridSpacing;

            auto center = std::make_shared<CRoadTile>(&game);
            center->SetLocation(grid * 10, grid * 17);
            game.Add(center);


            auto ul = std::make_shared<CRoadTile>(&game);
            ul->SetLocation(grid * 8, grid * 16);
            game.Add(ul);
            game.SortTiles();

            Assert::IsTrue(game.GetAdjacent(center, -1, -1) == ul, L"Upper left test");
            Assert::IsTrue(game.GetAdjacent(center, 1, -1) == nullptr, L"Upper right null test");

            auto ur = std::make_shared<CRoadTile>(&game);
            ur->SetLocation(grid * 12, grid * 16);
            game.Add(ur);

            auto ll = std::make_shared<CRoadTile>(&game);
            ll->SetLocation(grid * 8, grid * 18);
            game.Add(ll);

            auto lr = std::make_shared<CRoadTile>(&game);
            lr->SetLocation(grid * 12, grid * 18);
            game.Add(lr);

            game.SortTiles();

            Assert::IsTrue(game.GetAdjacent(center, 1, -1) == ur, L"Upper right test");
            Assert::IsTrue(game.GetAdjacent(center, -1, 1) == ll, L"Lower left test");
            Assert::IsTrue(game.GetAdjacent(center, 1, 1) == lr, L"Lower right test");
        }

        TEST_METHOD(TestCGameHitTest)
        {
            // Create a Tile to test
            CGame game;
            CTileLandscape landscapeTile(&game);

            landscapeTile.SetLocation(100, 200);

            // Center of the Tile should be a true
            Assert::IsTrue(landscapeTile.HitTest(100, 200));

            // Left of the Tile
            Assert::IsFalse(landscapeTile.HitTest(10, 200));

            // Right of the Tile
            Assert::IsFalse(landscapeTile.HitTest(200, 200));

            // Above the Tile
            Assert::IsFalse(landscapeTile.HitTest(100, 0));

            // Below the Tile
            Assert::IsFalse(landscapeTile.HitTest(100, 300));

            // Of Tile transparent pixel
            Assert::IsFalse(landscapeTile.HitTest(100 - 125 / 2 + 17, 200 - 117 / 2 + 16));
        }

        TEST_METHOD(TestCGameNearestGrass)
        {
            CGame game;

            auto grassTile = std::make_shared<CTile>(&game);
            grassTile->SetType(L"grass");
            game.Add(grassTile);
            grassTile->SetLocation(100, 200);


            auto grassTile2 = std::make_shared<CTile>(&game);
            grassTile2->SetType(L"grass");
            game.Add(grassTile2);
            grassTile2->SetLocation(300, 500);

            auto grassTile3 = std::make_shared<CTile>(&game);
            grassTile3->SetType(L"grass");
            game.Add(grassTile3);
            grassTile3->SetLocation(200, 700);

            // Case 1: Similar Vicinity
            auto closestGrass1 = game.NearestGrass(120, 190);
            auto closestGrass2 = game.NearestGrass(90, 170);

            /// (120,190) and (90,170) are closeset to (100,200) Grass Tile
            /// First Verify that neither of them are nullptr
            Assert::IsFalse(closestGrass1 == nullptr || closestGrass2 == nullptr);

            /// Test x and y coordinates - should be same
            Assert::AreEqual(closestGrass1->GetX(), closestGrass2->GetX());
            Assert::AreEqual(closestGrass1->GetY(), closestGrass2->GetY());

            /// Case 2: No GrassTiles nearby should return a nullptr
            auto closestGrass3 = game.NearestGrass(0, 0);
            Assert::IsTrue(closestGrass3 == nullptr);

            /// Case 3: Farther Apart Different Closest Tiles
            /// 
            auto closestGrass4 = game.NearestGrass(290, 490);
            auto closestGrass5 = game.NearestGrass(180, 720);

            /// First Verify that neither of them are nullptr
            Assert::IsFalse(closestGrass4 == nullptr || closestGrass5 == nullptr);

            /// Test x and y coordinates - shouldn't be the same
            Assert::AreNotEqual(closestGrass4->GetX(), closestGrass5->GetX());
            Assert::AreNotEqual(closestGrass4->GetY(), closestGrass5->GetY());
        }

        TEST_METHOD(TestCGameSave)
        {
            // Create a path to temporary files
            wstring path = TempPath();

            // Create an aquarium
            CGame aquarium;

            //
            // First test, saving an empty aquarium
            //
            wstring file1 = path + L"test1.aqua";
            aquarium.Save(file1);

            //TestEmpty(file1);
        }


    };
}