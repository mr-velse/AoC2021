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

	static unsigned long long CalcDescMaths(int currentT, int days)
	{
		unsigned long long count = 1; // the initial fish
		int daysCount = days;
		if (currentT < daysCount)
		{
			int generations = 0;
			daysCount -= currentT;
			daysCount--;
			//count++;
			generations++;
			int lifeChildren = 1 + (floorf(daysCount / 6.0f)); // all the initial fish's children
			


			while (lifeChildren > 0)
			{

			}


			while (daysCount > -1)
			{
				int lastLifechildren = lifeChildren;
				if (8 < daysCount)
				{
					daysCount -= 8;
					daysCount--;
					//count++; 
					int lifeChildren = (lastLifechildren * (1 + (floorf(daysCount / 6.0f)))); // this child's children for the rest of days
				
					count += lifeChildren;
				//	for (int i = lifeChildren; i > 0; --i)
				//	{
				//		count += i;
				//	}
					generations++;
				}
				else
					break;
			}
		}
		return count;
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