#include "stdafx.h"
#include "CppUnitTest.h"
#include "Factor.h"

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace FactorTests
{		
    TEST_CLASS(FactorTests)
    {
    public:
        
        TEST_METHOD(SimpleFactorTest)
        {
            list<unsigned long long> foundFactors = Factor::CreateFactors(860000000);
            
            list<unsigned long long>::iterator it = foundFactors.begin();
            Assert::IsTrue(foundFactors.size() >= 1500);
            Assert::AreEqual((unsigned long long)1, *(it));
            advance(it, 1);
            Assert::AreEqual((unsigned long long)2, *(it));
            advance(it, 1);
            Assert::AreEqual((unsigned long long)3, *(it));
            advance(it, 1);
            Assert::AreEqual((unsigned long long)4, *(it));
            advance(it, 1);
            Assert::AreEqual((unsigned long long)5, *(it));
            advance(it, 1000);
            Assert::AreEqual((unsigned long long)53084160, *(it));
            advance(it, 495);
            Assert::AreEqual((unsigned long long)859963392, *(it));
        }

    };
}