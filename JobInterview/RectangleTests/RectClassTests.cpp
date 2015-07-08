#include "stdafx.h"
#include "CppUnitTest.h"
#include "Rect.h"
#include <stdexcept>

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace RectangleTests
{		
    TEST_CLASS(RectClassTests)
    {
    public:
        TEST_METHOD(BadWidthTest)
        {
            Assert::ExpectException<invalid_argument>([&]
            {
                Rect(-1.0f, 2.0f, Point2D{ 0.0f, 0.0f });
            });
        }

        TEST_METHOD(BadHeightTest)
        {
            Assert::ExpectException<invalid_argument>([&]
            {
                Rect(1.0f, 0.0f, Point2D{ 0.0f, 0.0f });
            });
        }

        // Rect Collision Tests
        TEST_METHOD(Rect_NoCollision)
        {
            Rect r1 = Rect(2.0f, 1.0f, Point2D{ 0.0f, 0.0f });
            Rect r2 = Rect(2.0f, 1.0f, Point2D{ 3.0f, 0.0f });
            Assert::IsFalse(r1.AxisAlignedCollision(r2));
        }

        TEST_METHOD(Rect_LeftUpperCornerCollision)
        {
            Rect r1 = Rect(2.0f, 1.0f, Point2D{ 0.0f, 0.0f });
            Rect r2 = Rect(2.0f, 1.0f, Point2D{ -1.0f, 0.5f });
            Assert::IsTrue(r1.AxisAlignedCollision(r2));
        }

        TEST_METHOD(Rect_RightUpperCornerCollision)
        {
            Rect r1 = Rect(2.0f, 1.0f, Point2D{ 0.0f, 0.0f });
            Rect r2 = Rect(2.0f, 1.0f, Point2D{ 1.0f, 0.5f });
            Assert::IsTrue(r1.AxisAlignedCollision(r2));
        }

        TEST_METHOD(Rect_LeftLowerCornerCollision)
        {
            Rect r1 = Rect(2.0f, 1.0f, Point2D{ 0.0f, 0.0f });
            Rect r2 = Rect(2.0f, 1.0f, Point2D{ -1.0f, -0.5f });
            Assert::IsTrue(r1.AxisAlignedCollision(r2));
        }

        TEST_METHOD(Rect_RightLowerCornerCollision)
        {
            Rect r1 = Rect(2.0f, 1.0f, Point2D{ 0.0f, 0.0f });
            Rect r2 = Rect(2.0f, 1.0f, Point2D{ 1.0f, -0.5f });
            Assert::IsTrue(r1.AxisAlignedCollision(r2));
        }

        TEST_METHOD(Rect_SmallRectInsideLargerRect)
        {
            Rect r1 = Rect(2.0f, 1.0f, Point2D{ 0.0f, 0.0f });
            Rect r2 = Rect(1.0f, 0.5f, Point2D{ 0.5f, -0.25f });
            Assert::IsTrue(r1.AxisAlignedCollision(r2));
        }

        TEST_METHOD(Rect_OverlappingTopBorder)
        {
            Rect r1 = Rect(2.0f, 1.0f, Point2D{ 0.0f, 0.0f });
            Rect r2 = Rect(2.0f, 1.0f, Point2D{ 0.0f, 1.0f });
            Assert::IsTrue(r1.AxisAlignedCollision(r2));
        }

        TEST_METHOD(Rect_OverlappingLeftBorder)
        {
            Rect r1 = Rect(2.0f, 1.0f, Point2D{ 0.0f, 0.0f });
            Rect r2 = Rect(2.0f, 1.0f, Point2D{ -2.0f, 0.0f });
            Assert::IsTrue(r1.AxisAlignedCollision(r2));
        }

        // Point Collision Tests
        TEST_METHOD(Point_InsideBorder)
        {
            Rect r1 = Rect(2.0f, 1.0f, Point2D{ 0.0f, 0.0f });
            Assert::IsTrue(r1.AxisAlignedCollision(Point2D{ 1.0f, -0.5f }));
        }

        TEST_METHOD(Rect_NoCollision1)
        {
            Rect r1 = Rect(2.0f, 1.0f, Point2D{ 0.0f, 0.0f });
            Assert::IsFalse(r1.AxisAlignedCollision(Point2D{ 3.0f, 0.5f }));
        }

        TEST_METHOD(Rect_NoCollision2)
        {
            Rect r1 = Rect(2.0f, 1.0f, Point2D{ 0.0f, 0.0f });
            Assert::IsFalse(r1.AxisAlignedCollision(Point2D{ -1.0f, 0.5f }));
        }

        TEST_METHOD(Point_OverlappingTopBorder)
        {
            Rect r1 = Rect(2.0f, 1.0f, Point2D{ 0.0f, 0.0f });
            Assert::IsTrue(r1.AxisAlignedCollision(Point2D{ 1.0f, 0.0f }));
        }

        TEST_METHOD(Point_OverlappingLeftBorder)
        {
            Rect r1 = Rect(2.0f, 1.0f, Point2D{ 0.0f, 0.0f });
            Assert::IsTrue(r1.AxisAlignedCollision(Point2D{ 0.0f, -0.5f }));
        }
    };
}