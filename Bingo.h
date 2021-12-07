#pragma once

struct Grid
{
	static const int Dimension = 5; // square

	int Grid[Dimension][Dimension];

	bool Marked[Dimension][Dimension];

	bool complete = false;

	void WipeMarks()
	{
		for (int i = 0; i < Dimension; ++i)
		{
			for (int j = 0; j < Dimension; ++j)
			{
				Marked[i][j] = false;
			}
		}
		complete = false;
	}

	void Reset()
	{
		for (int i = 0; i < Dimension; ++i)
		{
			for (int j = 0; j < Dimension; ++j)
			{
				Grid[i][j] = 0;
				Marked[i][j] = false;
			}
		}
		complete = false;
	}

	int Answer(int lastMarked)
	{
		int total = 0;
		for (int i = 0; i < Dimension; ++i)
		{
			for (int j = 0; j < Dimension; ++j)
			{
				if (Marked[i][j] == false)
				{
					total += Grid[i][j];
				}
			}
		}
		return lastMarked * total;
	}

	bool Mark(int number)
	{
		for (int i = 0; i < Dimension; ++i)
		{
			for (int j = 0; j < Dimension; ++j)
			{
				if (Grid[i][j] == number)
				{
					Marked[i][j] = true;
					return true;
				}
			}
		}
		return false;
	}

	bool Check()
	{
		bool failed = false;
		for (int i = 0; i < Dimension; ++i) // rows
		{
			for (int j = 0; j < Dimension; ++j)
			{
				if (Marked[i][j] == false)
				{
					failed = true;
					break;
				}
			}
			if (!failed)
			{
				complete = true;
				return true;
			}

			failed = false;
		}
		failed = false;
		for (int j = 0; j < Dimension; ++j) // rows
		{
			for (int i = 0; i < Dimension; ++i)
			{
				if (Marked[i][j] == false)
				{
					failed = true;
					break;
				}
			}
			if (!failed)
			{
				complete = true;
				return true;
			}

			failed = false;
		}
		return false;
	}
};