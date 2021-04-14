#include "pch.h"
#include <memory>
#include "CppUnitTest.h"
#include "Dart.h"
#include "Game.h"
#include "Item.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Testing
{
	TEST_CLASS(CDartTest)
	{
	public:

		TEST_METHOD_INITIALIZE(methodName)
		{
			extern wchar_t g_dir[];
			::SetCurrentDirectory(g_dir);
		}
		
		TEST_METHOD(TestSetLocation)
		{
			CGame game;
			auto dart = std::make_shared<CDart>(&game);
			dart->SetLocation(28, 28);
			game.Add(dart);
			Assert::IsTrue(dart->GetCentre() == 28);
		}

		TEST_METHOD(TestGetTip)
		{
			CGame game;
			auto dart = std::make_shared<CDart>(&game);
			dart->SetImage(L"ddd.png");
			dart->SetLocation(28, 28);
			double x, y;
			dart->GetTip(x, y);
			Assert::IsTrue(y == 28 && x == 56);
		}



	};
}