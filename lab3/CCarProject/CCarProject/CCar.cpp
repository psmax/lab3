#include "stdafx.h"
#include "CCar.h"


CCar::Range CCar::m_gearSpeedRange[] = { { 0, 20 },
												{ 0, 150 },
												{ 0, 30 },
												{ 20, 50 },
												{ 30, 60 },
												{ 40, 90 },
												{ 50, 150 } };

CCar::CCar()
	:m_engineIsTurnedOn(false)
	, m_speed(0)
	, m_gear(0)
	, m_direction(Stand)
{
}

bool CCar::EngineIsTurnedOn()const
{
	return m_engineIsTurnedOn;
}

bool CCar::TurnOnEngine()
{
	if (!m_engineIsTurnedOn)
	{
		m_engineIsTurnedOn = true;
		m_speed = minSpeed;
		m_gear = neutralGear;
		m_direction = Stand;
		return m_engineIsTurnedOn;
	}
	return false;
}

bool CCar::TurnOffEngine()
{
	if (m_engineIsTurnedOn)
	{
		if (m_direction == Stand && m_gear == neutralGear 
			&& m_speed == minSpeed)
		{
			m_engineIsTurnedOn = false;
			return true;
		}
	}
	return false;
}

int CCar::GetGear() const
{
	return m_gear;
}

int CCar::GetSpeed() const
{
	return m_speed;
}

CCar::Direction CCar::GetDirection() const
{
	return m_direction;
}

bool CCar::SetGear(int gear)
{
	if (gear < revGear || gear > maxGear)
	{
		return false;
	}

	if (!m_engineIsTurnedOn)
	{
		if (gear == neutralGear)
		{
			m_gear = neutralGear;
			return true;
		}
		return false;
	}

	if (gear == m_gear)
	{
		return true;
	}

	if (gear == firstGear && m_direction == Back)
	{
		return false;
	}

	if ((gear == revGear && m_gear == neutralGear && m_speed == minSpeed) 
		|| (gear == revGear && m_gear == firstGear && m_speed == minSpeed))
	{
		m_gear = revGear;
		return true;
	}
	else if (gear == revGear)
	{
		return false;
	}

	if (m_speed >= m_gearSpeedRange[gear + 1].Min
		&& m_speed <= m_gearSpeedRange[gear + 1].Max)
	{
		m_gear = gear;
		return true;
	}

	return false;
}



bool CCar::SetSpeed(int speed)
{
	if (!m_engineIsTurnedOn)
	{
		return false;
	}

	if (speed < minSpeed || speed > maxSpeed)
	{
		return false;
	}

	if (m_gear == neutralGear && speed > m_speed)
	{
		return false;
	}

	if (speed >= m_gearSpeedRange[m_gear + 1].Min 
		&& speed <= m_gearSpeedRange[m_gear + 1].Max)
	{
		if (speed == minSpeed)
		{
			m_direction = Stand;
		}
		if (m_speed == minSpeed && speed > minSpeed)
		{
			if (m_gear > revGear)
			{
				m_direction = Forward;
			}
			else
			{
				m_direction = Back;
			}
		}
		m_speed = speed;
		return true;
	}

	return false;
}

CCar::~CCar()
{
}

