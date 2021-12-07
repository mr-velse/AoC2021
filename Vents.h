#pragma once
#include <utility>

struct OceanFloor
{
	static const int Dimension = 1000; // ugh

	int Grid[1000][1000];

	void Reset()
	{
		for(int i = 0; i < Dimension; ++i)
			for (int j = 0; j < Dimension; ++j)
				Grid[i][j] = 0;
	}

	void AddLine(int x, int y, int x2, int y2, bool diag = false)
	{
		if (x == x2)
		{
			if(y2 < y)
				std::swap(y, y2);

			for(int i = y; i <= y2; ++i)
				Grid[x][i]++;
		}
		else if (y == y2)
		{
			if(x2 < x)
				std::swap(x, x2);

			for(int i = x; i <= x2; ++i)
				Grid[i][y]++;
		}
		else
		{
			if (diag)
			{
				if(x2 < x)
				{
					std::swap(x, x2);
					std::swap(y, y2);
				}

				const int ydir = y2 > y ? 1 : -1;
				int count = 0;
				for (int i = x; i <= x2; ++i)
				{
					const int ypos = y + (ydir * count);
					Grid[i][ypos]++;
					count++;
				}
			}
		}
	}

	int Overlaps(int atLeast)
	{
		int count = 0;

		for(int i = 0; i < Dimension; ++i)
			for (int j = 0; j < Dimension; ++j)
				if(Grid[i][j] >= atLeast)
					count++;

		return count;
	}
};