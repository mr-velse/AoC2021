#pragma once

#include <math.h>

struct Lantern
{
	int Timer = 0;

	Lantern(int t)
	{
		Timer = t;
	}

	bool Tick()
	{
		Timer--;

		if (Timer < 0)
		{
			Timer = 6;
			return true;
		}
		return false;
	}

	unsigned long long CalcDescendents(int days) const
	{
		unsigned long long descCount = 0;

		int dayCount = days;
		int subTimer = Timer;
		for (int i = 0; i < days; ++i)
		{
			subTimer--;
			dayCount--;
			if (subTimer < 0)
			{
				descCount++;
				descCount += CalcChild(dayCount);
				subTimer = 6;
			}
		}

		return descCount;
	}

	unsigned long long CalcChild(int days) const
	{
		unsigned long long descCount = 0;
		int subTimer = 8;

		int dayCount = days;
		for (int i = 0; i < days; ++i)
		{
			subTimer--;
			dayCount--;
			if (subTimer < 0)
			{
				descCount++;
				descCount += CalcChild(dayCount);
				subTimer = 6;
			}
		}
		return descCount;
	}
};