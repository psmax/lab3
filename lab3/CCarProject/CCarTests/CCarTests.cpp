// CCarTests.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"

#include "../CCarProject/CCar.h"

struct CarFixture
{
	CCar car;
};

BOOST_FIXTURE_TEST_SUITE(car, CarFixture)

	BOOST_AUTO_TEST_CASE(Turned_Off_By_Default)
	{
		BOOST_CHECK(!car.EngineIsTurnedOn());
	}
	
	BOOST_AUTO_TEST_CASE(Can_Be_Turned_On)
	{
		BOOST_CHECK(car.TurnOnEngine());
		BOOST_CHECK(car.EngineIsTurnedOn());
	}

	struct TurnedOnCarFixture : CarFixture
	{
		TurnedOnCarFixture()
		{
			BOOST_REQUIRE(car.TurnOnEngine());
		}
	};
	
	BOOST_FIXTURE_TEST_SUITE(After_Being_TurnedOn, TurnedOnCarFixture)
		
		BOOST_AUTO_TEST_CASE(Have_Gear_Speed_And_Direction_By_Default)
		{
			BOOST_CHECK_EQUAL(car.GetGear(), 0);
			BOOST_CHECK_EQUAL(car.GetSpeed(), 0);
			BOOST_CHECK_EQUAL(car.GetDirection(), CCar::Stand);
		}
		BOOST_AUTO_TEST_CASE(Can_Be_Turned_Off)
		{
			BOOST_CHECK(car.TurnOffEngine());
			BOOST_CHECK(!car.EngineIsTurnedOn());
		}
		struct TurnedOffCarFixture : Can_Be_Turned_Off
		{
			TurnedOffCarFixture()
			{
				BOOST_REQUIRE(car.TurnOffEngine());
			}
		};

		BOOST_FIXTURE_TEST_SUITE(After_Turned_Off, TurnedOffCarFixture)

			BOOST_AUTO_TEST_CASE(Cant_Be_Turned_Off_Twice)
			{
				car.SetSpeed(0);
				car.SetGear(0);

				BOOST_CHECK(!car.TurnOffEngine());
			}
			BOOST_AUTO_TEST_CASE(Neutral_Gear_Sets_When_Engine_Turned_Off)
			{
				BOOST_CHECK(car.SetGear(0));
			}
		BOOST_AUTO_TEST_SUITE_END()

		BOOST_AUTO_TEST_CASE(Cant_Be_Turned_On_Twice)
		{
			BOOST_CHECK(!car.TurnOnEngine());
			BOOST_CHECK(car.EngineIsTurnedOn());
		}
		BOOST_AUTO_TEST_CASE(Can_Change_Gear_And_Speed)
		{
			BOOST_CHECK(car.SetGear(-1));
			BOOST_CHECK_EQUAL(car.GetGear(), -1);
			BOOST_CHECK(car.SetSpeed(10));
			BOOST_CHECK_EQUAL(car.GetSpeed(), 10);
			BOOST_CHECK(!car.SetSpeed(21));
			BOOST_CHECK_EQUAL(car.GetSpeed(), 10);

			BOOST_CHECK(car.SetGear(0));
			BOOST_CHECK_EQUAL(car.GetGear(), 0);
			BOOST_CHECK(car.SetSpeed(10));
			BOOST_CHECK(car.SetSpeed(0));
			BOOST_CHECK_EQUAL(car.GetSpeed(), 0);

			BOOST_CHECK(car.SetGear(1));
			BOOST_CHECK_EQUAL(car.GetGear(), 1);
			BOOST_CHECK(!car.SetSpeed(31));
			BOOST_CHECK_EQUAL(car.GetSpeed(), 0);
			BOOST_CHECK(car.SetSpeed(20));
			BOOST_CHECK_EQUAL(car.GetSpeed(), 20);

			BOOST_CHECK(car.SetGear(2));
			BOOST_CHECK_EQUAL(car.GetGear(), 2);
			BOOST_CHECK(!car.SetSpeed(51));
			BOOST_CHECK_EQUAL(car.GetSpeed(), 20);
			BOOST_CHECK(car.SetSpeed(40));
			BOOST_CHECK_EQUAL(car.GetSpeed(), 40);

			BOOST_CHECK(car.SetGear(3));
			BOOST_CHECK_EQUAL(car.GetGear(), 3);
			BOOST_CHECK(!car.SetSpeed(61));
			BOOST_CHECK_EQUAL(car.GetSpeed(), 40);
			BOOST_CHECK(car.SetSpeed(50));
			BOOST_CHECK_EQUAL(car.GetSpeed(), 50);

			BOOST_CHECK(car.SetGear(4));
			BOOST_CHECK_EQUAL(car.GetGear(), 4);
			BOOST_CHECK(!car.SetSpeed(91));
			BOOST_CHECK_EQUAL(car.GetSpeed(), 50);
			BOOST_CHECK(car.SetSpeed(70));
			BOOST_CHECK_EQUAL(car.GetSpeed(), 70);

			BOOST_CHECK(car.SetGear(5));
			BOOST_CHECK_EQUAL(car.GetGear(), 5);
			BOOST_CHECK(!car.SetSpeed(151));
			BOOST_CHECK_EQUAL(car.GetSpeed(), 70);
			BOOST_CHECK(car.SetSpeed(100));
			BOOST_CHECK_EQUAL(car.GetSpeed(), 100);

			BOOST_CHECK(!car.SetGear(6));
			BOOST_CHECK_EQUAL(car.GetGear(), 5);
			BOOST_CHECK(!car.SetGear(-2));
			BOOST_CHECK_EQUAL(car.GetGear(), 5);
		}
		
		BOOST_AUTO_TEST_SUITE(After_Changing_Gear_And_Speed)
			
			BOOST_AUTO_TEST_CASE(Can_Move_Backwards)
			{
				BOOST_CHECK(car.SetGear(-1));
				BOOST_CHECK_EQUAL(car.GetGear(), -1);
				BOOST_CHECK(car.SetSpeed(20));
				BOOST_CHECK_EQUAL(car.GetSpeed(), 20);
				BOOST_CHECK(!car.SetSpeed(21));
				BOOST_CHECK_EQUAL(car.GetSpeed(), 20);
				BOOST_CHECK(car.GetDirection() == CCar::Back);
			}
			BOOST_AUTO_TEST_CASE(Can_Move_Forward)
			{
				BOOST_CHECK(car.SetGear(1));
				BOOST_CHECK_EQUAL(car.GetGear(), 1);
				BOOST_CHECK(car.SetSpeed(30));
				BOOST_CHECK_EQUAL(car.GetSpeed(), 30);
				BOOST_CHECK(car.GetDirection() == CCar::Forward);

				BOOST_CHECK(car.SetGear(3));
				BOOST_CHECK_EQUAL(car.GetGear(), 3);
				BOOST_CHECK(car.SetSpeed(60));
				BOOST_CHECK_EQUAL(car.GetSpeed(), 60);
				BOOST_CHECK(car.GetDirection() == CCar::Forward);
			}
			struct MovingCar : TurnedOnCarFixture
			{
				MovingCar()
				{
					BOOST_REQUIRE(car.EngineIsTurnedOn());
				}
			};
				
			BOOST_FIXTURE_TEST_SUITE(After_Being_Move, MovingCar)

				BOOST_AUTO_TEST_CASE(Cant_Be_Turned_Off_While_Not_NeutralGear)
					{
						car.TurnOnEngine();
						car.SetGear(1);
						BOOST_CHECK(!car.TurnOffEngine());
					}
				BOOST_AUTO_TEST_CASE(Cant_Be_Turned_Off_While_Move)
					{
						car.TurnOnEngine();
						car.SetGear(1);
						BOOST_CHECK(!car.TurnOffEngine());

						car.SetSpeed(16);
						BOOST_CHECK(!car.TurnOffEngine());

						car.SetSpeed(0);
						car.SetGear(-1);
						car.SetSpeed(5);
						BOOST_CHECK(!car.TurnOffEngine());
					}
			BOOST_AUTO_TEST_SUITE_END()
		BOOST_AUTO_TEST_SUITE_END()
	BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
/**/