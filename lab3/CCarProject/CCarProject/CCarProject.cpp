// CCarProject.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <boost/range/algorithm/transform.hpp>
#include <boost/phoenix.hpp>
#include "CCar.h"

using namespace std;

int StringToInt(const char *str, bool &err)
{
	char * pLastChar = NULL;
	int param = strtol(str, &pLastChar, 10);
	err = ((*str == '\0') || (*pLastChar != '\0'));
	return param;
}

void PrintInfo(CCar &const car)
{
	int speed = car.GetSpeed();
	int gear = car.GetGear();

	if (car.EngineIsTurnedOn())
	{
		cout << "Engine turned on\n";
	}
	else
	{
		cout << "Engine turned off\n";
	}

	if (car.GetDirection() == CCar::Stand)
	{
		cout << "The car is standing\n";
	}
	else if (car.GetDirection() == CCar::Forward)
	{
		cout << "The car goes forward\n";
	}
	else
	{
		cout << "The car goes back\n";
	}

	cout << "Current speed : " << speed << endl;
	cout << "Current gear : " << gear << endl;
}

void ChooseCommand(string &const command, CCar & car)
{
	if (command == "EngineOn")
	{
		if (car.TurnOnEngine())
		{
			cout << "Done\n";
		}
		else
		{
			cout << "You can't turn on engine : already turned on\n";
		}
		return;
	}

	if (command == "EngineOff")
	{
		if (car.TurnOffEngine())
		{
			cout << "Done\n";
		}
		else
		{
			if (car.GetSpeed())
			{
				cout << "You can't turn off engine : car is moving\n";
			}
			if (car.GetGear())
			{
				cout << "You can't turn off engine : gear must be 0\n";
			}
			if (!car.EngineIsTurnedOn())
			{
				cout << "You can't turn off engine : already turned off\n";
			}
		}
		return;
	}

	if (command.substr(0, 8) == "SetGear ")
	{
		bool err;
		int gear = StringToInt(command.substr(8).c_str(), err);
		if (err)
		{
			cout << "Wrong input : expected SetGear <int>\n";
			return;
		}
		if (car.SetGear(gear))
		{
			cout << "Done\n";
		}
		else
		{
			cout << "Change gear is unavailable\n";
		}
		return;
	}

	if (command.substr(0, 9) == "SetSpeed ")
	{
		bool err;
		int speed = StringToInt(command.substr(9).c_str(), err);
		if (err)
		{
			cout << "Wrong input : expected SetSpeed <int>\n";
			return;
		}
		if (car.SetSpeed(speed))
		{
			cout << "Done\n";
		}
		else
		{
			cout << "Change speed is unavailable\n";
		}
		return;
	}

	cout << "Wrong command\n";
}

int main(int argc, char* argv[])
{
	CCar car;
	string command;
	cout << "Available commands:EngineOn, EngineOff, SetSpeed <speed>, SetGear <gear>.\n";
	cout << "Enter command: ";
	while (getline(cin, command))
	{
		ChooseCommand(command, car);
		PrintInfo(car);
		cout << "Enter command: ";
	}
	
	return 0;
}