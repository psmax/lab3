
#include "stdafx.h"

class CCar
{
public:
	CCar();
	~CCar();

	enum /*class*/ Direction
	{
		Back,
		Stand,
		Forward
	};

	bool EngineIsTurnedOn() const;
	int GetSpeed() const;
	int GetGear() const;
	bool TurnOnEngine();
	bool TurnOffEngine();
	bool SetGear(int gear);
	Direction GetDirection() const;
	bool SetSpeed(int speed);
private:
	struct Range
	{
		int Min;
		int Max;
	};
	int maxSpeed = 150;
	int minSpeed = 0;
	int maxGear = 5;
	int revGear = -1;
	int neutralGear = 0;
	int firstGear = 1;
	static Range m_gearSpeedRange[];
	bool m_engineIsTurnedOn;
	int m_speed;
	Direction m_direction;
	int m_gear;
};

