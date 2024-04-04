#include "pch.h"
#include "CppUnitTest.h"
#include "../LB_10.4.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
        TEST_METHOD(InputCompanyTest)
        {
           
            Company company;
            std::istringstream input("TestCompany\n2\nToyota 20000\nHonda 25000\n");
            std::cin.rdbuf(input.rdbuf()); 
            inputCompany(company);
            Assert::AreEqual(company.name, std::string("TestCompany"));
            Assert::AreEqual((int)company.cars.size(), 2); 
            Assert::AreEqual(company.cars[0].brand, std::string("Toyota"));
            Assert::AreEqual(company.cars[0].price, 20000.0);
            Assert::AreEqual(company.cars[1].brand, std::string("Honda"));
            Assert::AreEqual(company.cars[1].price, 25000.0);
        }

        TEST_METHOD(PrintCompanyTest)
        {
            
            Logger::WriteMessage("Testing printCompany function...");
            Company company;
            company.name = "TestCompany";
            company.cars.push_back({ "Toyota", 20000 });
            company.cars.push_back({ "Honda", 25000 });
            printCompany(company);
           
        }
	};
}
