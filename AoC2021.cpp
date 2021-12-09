// AoC2021.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <array>
#include <list>
#include <algorithm>
#include <set>

#include "Inputs.h"
#include "Bingo.h"
#include "Vents.h"
#include "LanternFish.h"

void PuzzleTwo()
{
	int window = 0;
	int increases = 0;
	int last = -1;

	int index = 0;
	for (int depth : Depths)
	{
		window += depth;
		if (index > 2)		
		{
			window -= Depths[index - 3];

			if (window > last)
			{
				increases++;
			}
		}
		last = window;

		index++;
	}

	std::cout << "Number of increases: " << increases << "\n";
}

void PuzzleThree()
{
	int x = 0;
	int depth = 0;

	std::ifstream exprFile("Movements.txt");
	std::string singleExpr;
	while (std::getline(exprFile, singleExpr)) // Gets a full line from the file
	{
		int space = singleExpr.find(" ");
		if(space != std::string::npos)
		{
			std::string numberStr = singleExpr.substr(space + 1);
			int number = std::stoi(numberStr);

			if (singleExpr.find("forward") != std::string::npos)
			{
				x += number;
			}
			else if (singleExpr.find("down") != std::string::npos)
			{
				depth += number;
			}
			if (singleExpr.find("up") != std::string::npos)
			{
				depth -= number;
			}
		}
	}

	const int answer = depth * x;
	std::cout << "Depth x Horizontal Position: " << answer << "\n";
}

void PuzzleFour()
{
	int x = 0;
	int depth = 0;
	int aim = 0;

	std::ifstream exprFile("Movements.txt");
	std::string singleExpr;
	while (std::getline(exprFile, singleExpr)) // Gets a full line from the file
	{
		int space = singleExpr.find(" ");
		if (space != std::string::npos)
		{
			std::string numberStr = singleExpr.substr(space + 1);
			int number = std::stoi(numberStr);

			if (singleExpr.find("forward") != std::string::npos)
			{
				x += number;
				depth += (number * aim);
			}
			else if (singleExpr.find("down") != std::string::npos)
			{
				aim += number;
			}
			if (singleExpr.find("up") != std::string::npos)
			{
				aim -= number;
			}
		}
	}

	const int answer = depth * x;
	std::cout << "Depth x Horizontal Position: " << answer << "\n";
}

void DayThree()
{
	std::ifstream exprFile("DayThree.txt");
	std::string singleExpr;
	std::vector<int> MostCommon;
	std::vector<std::string> oxygen;
	std::vector<std::string> c02;
	bool setup = false;
	int count = 0;
	while (std::getline(exprFile, singleExpr)) // Gets a full line from the file
	{
		oxygen.push_back(singleExpr);
		c02.push_back(singleExpr);
		if (!setup)
		{
			for (int i = 0; i < singleExpr.length(); ++i)
			{
				MostCommon.push_back(0);
			}
			setup = true;
		}

		for (int i = 0; i < singleExpr.length(); ++i)
		{
			if (singleExpr.at(i) == '1')
			{
				MostCommon[i]++;
			}
		}
		++count;
	}

	unsigned int gamma = 0;
	unsigned int epsilonmask = 0;

	const int offset = MostCommon.size() - 1;
	for (int i = 0; i < MostCommon.size(); ++i)
	{
		const int zeroes = count - MostCommon.at(i);
		if ( MostCommon.at(i) > zeroes)
		{
			const unsigned int toadd = (1 << (offset - i));
			gamma += toadd;
		}
		epsilonmask += (1 << i);
	}
	unsigned int epsilon = ~gamma;
	epsilon &= epsilonmask;

	const unsigned int answer = gamma * epsilon;
	std::cout << "Puzzle Five: " << answer << "\n";

	for (int i = 0; i < MostCommon.size(); ++i)
	{
		const int ones = MostCommon.at(i);
		const int zeroes = oxygen.size() - ones;
		for (std::vector<std::string>::iterator it = oxygen.begin(); it != oxygen.end(); )
		{
			bool removed = false;
			if(oxygen.size() != 1)
			{
				if ((*it).at(i) == '1')
				{
					if (ones < zeroes)
					{
						it = oxygen.erase(it);
						removed = true;
					}
				}
				if (!removed && (*it).at(i) == '0')
				{
					if (ones >= zeroes)
					{
						it = oxygen.erase(it);
						removed = true;
					}
				}
			}
			if(!removed)
			{
				it++;
			}
		}

		for (int m = 0; m < MostCommon.size(); ++m)
		{
			MostCommon[m] = 0;
		}
		for (int j = 0; j < oxygen.size(); ++j)
		{
			std::string oxyline = oxygen[j];
			for (int k = 0; k < oxyline.length(); ++k)
			{
				if (oxyline.at(k) == '1')
				{
					MostCommon[k]++;
				}
			}
		}
	}

	for (int i = 0; i < MostCommon.size(); ++i)
	{
		for (int m = 0; m < MostCommon.size(); ++m)
		{
			MostCommon[m] = 0;
		}
		for (int j = 0; j < c02.size(); ++j)
		{
			std::string c02line = c02[j];
			for (int k = 0; k < c02line.length(); ++k)
			{
				if (c02line.at(k) == '1')
				{
					MostCommon[k]++;
				}
			}
		}

		const int ones = MostCommon.at(i);
		const int zeroes = c02.size() - ones;
		for (std::vector<std::string>::iterator it = c02.begin(); it != c02.end();)
		{
			bool removed = false;
			if(c02.size() != 1)
			{
				if ((*it).at(i) == '1')
				{
					if (ones >= zeroes)
					{
						it = c02.erase(it);
						removed = true;
					}
				}
				if (!removed && (*it).at(i) == '0')
				{
					if (ones < zeroes)
					{
						it = c02.erase(it);
						removed = true;
					}
				}
			}
			if(!removed)
			{
				it++;
			}
		}
	}

	long oxynum = 0;
	long c02num = 0;
	if (oxygen.size() == 1)
	{
		std::string str = oxygen.at(0);
		oxynum = std::stol(str, 0, 2);
	}
	if (c02.size() == 1)
	{
		std::string str = c02.at(0);
		c02num = std::stol(str, 0, 2);
	}

	const unsigned long long answer2 = oxynum * c02num;
	std::cout << "Puzzle Six: " << answer2 << "\n";
}

void DayFour()
{
	std::ifstream exprFile("DayFour.txt");
	std::string singleExpr;
	std::vector<int> sequence;
	std::vector<Grid> grids;

	bool firstline = true;

	int row = 0;
	int col = 0;
	while (std::getline(exprFile, singleExpr)) // Gets a full line from the file
	{
		if (firstline)
		{
			firstline = false;
			const int length = singleExpr.length();
			int currentNum = 0;
			for (int i = 0; i < length; ++i)
			{
				char c = singleExpr[i];
				if (c == ',')
				{
					sequence.push_back(currentNum);
					currentNum = 0;
				}
				else
				{
					currentNum *= 10;
					currentNum += std::atoi(&c);
				}
			}
			sequence.push_back(currentNum); // last one has no comma!
		}
		else
		{
			if (singleExpr.empty())
			{
				Grid theGrid;
				theGrid.Reset();
				grids.push_back(theGrid);
				row = 0;
				col = 0;
			}
			else
			{
				Grid& theGrid = grids.back();
				const int length = singleExpr.length();
				int currentNum = 0;
				bool canPush = false;
				for (int i = 0; i < length; ++i)
				{
					char c = singleExpr[i];
					if (c == ' ' && canPush)
					{
						theGrid.Grid[row][col] = currentNum;
						currentNum = 0;
						canPush = false;
						col++;
					}
					else
					{
						canPush = true;
						currentNum *= 10;
						currentNum += std::atoi(&c);
					}
				}
				theGrid.Grid[row][col] = currentNum;
				col = 0;
				row++;
			}
		}
	}

	// parse done, let's play
	bool done = false;
	for (int i = 0; i < sequence.size(); ++i)
	{
		for (int j = 0; j < grids.size(); ++j)
		{
			if (grids[j].Mark(sequence.at(i)))
			{
				if (grids[j].Check())
				{
					int answer = grids[j].Answer(sequence.at(i));
					done = true;
					std::cout << "Puzzle Seven: " << answer << "\n";
					break;
				}
			}			
		}
		if(done)
			break;
	}

	for (int j = 0; j < grids.size(); ++j)
	{
		grids[j].WipeMarks();
	}

	int numComplete = 0;
	for (int i = 0; i < sequence.size(); ++i)
	{
		for (int j = 0; j < grids.size(); ++j)
		{
			if(grids[j].complete)
				continue;

			if (grids[j].Mark(sequence.at(i)))
			{
				if (grids[j].Check())
				{
					numComplete++;
					if (numComplete == sequence.size())
					{
						int answer = grids[j].Answer(sequence.at(i));
						std::cout << "Puzzle Eight: " << answer << "\n";
						return;
					}
				}
			}
		}
	}
}

void DayFive()
{
	std::ifstream exprFile("DayFive.txt");
	std::string singleExpr;

	OceanFloor* ocean = new OceanFloor;
	ocean->Reset();
	OceanFloor* ocean2 = new OceanFloor;
	ocean2->Reset();

	while (std::getline(exprFile, singleExpr)) // Gets a full line from the file
	{
		int x1, x2, y1, y2; x1 = x2 = y1 = y2 = 0;

		x1 = std::stoi(singleExpr);

		int firstComma = singleExpr.find(',');
		if (firstComma != std::string::npos)
		{
			y1 = std::stoi(singleExpr.substr(firstComma + 1));
		}
		int lastSpace = singleExpr.rfind(' ');
		if (lastSpace != std::string::npos)
		{
			x2 = std::stoi(singleExpr.substr(lastSpace + 1));
		}
		int lastComma = singleExpr.rfind(',');
		if (lastComma != std::string::npos)
		{
			y2 = std::stoi(singleExpr.substr(lastComma + 1));
		}

		ocean->AddLine(x1, y1, x2, y2);
		ocean2->AddLine(x1, y1, x2, y2, true);
	}

	int overlaps = ocean->Overlaps(2);
	std::cout << "Puzzle Nine: " << overlaps << "\n";
	overlaps = ocean2->Overlaps(2);
	std::cout << "Puzzle Ten: " << overlaps << "\n";

	delete ocean;
	delete ocean2;
}

void DaySix()
{
	std::ifstream exprFile("DaySix.txt");
	std::string singleExpr;

	std::vector<Lantern>* fishies;
	fishies = new std::vector<Lantern>();
	fishies->reserve(4000000);

	while (std::getline(exprFile, singleExpr)) // Gets a full line from the file
	{
		for (int i = 0; i < singleExpr.length(); ++i)
		{
			char c = singleExpr.at(i);
			if (c != ',')
			{
				fishies->push_back(Lantern(std::atoi(&c)));
			}
		}
	}

	// simulate
	unsigned long long count = fishies->size();
	unsigned long long answers[6];

	for (int i = 0; i < 6; ++i)
	{
		Lantern* l = new Lantern(i);
		answers[i] = l->CalcDescendents(80);
		//answers[i] = Lantern::CalcDescMaths(i, 80);
		delete l;
	}
	for (std::vector<Lantern>::iterator it = fishies->begin(); it != fishies->end(); ++it)
	{
		Lantern& l = *it;
		count += answers[l.Timer];
	}
	std::cout << "Puzzle Eleven: " << count << "\n";

	count = fishies->size();
	for (int i = 0; i < 6; ++i)
	{
		Lantern* l = new Lantern(i);
		answers[i] = l->CalcDescendents(256);
		delete l;
	}
	for (std::vector<Lantern>::iterator it = fishies->begin(); it != fishies->end(); ++it)
	{
		Lantern& l = *it;
		count += answers[l.Timer];
	}

	std::cout << "Puzzle Twelve: " << count << "\n";

	delete fishies;
}

void DaySeven()
{
	std::ifstream exprFile("DaySeven.txt");
	std::string singleExpr;
	std::vector<int> numbers;

	int min = INT_MAX;
	int max = INT_MIN;

	while (std::getline(exprFile, singleExpr)) // Gets a full line from the file
	{
		numbers.push_back(std::stoi(singleExpr));
		for (int i = 0; i < singleExpr.length(); ++i)
		{
			char& c = singleExpr.at(i);
			if (c == ',')
			{
				int number = std::stoi(singleExpr.substr(i + 1));
				numbers.push_back(number);

				if(number > max) max = number;
				if(number < min) min = number;
			}
		}
	}

	std::sort(numbers.begin(), numbers.end());
	int medianIdx = numbers.size() / 2;
		
	int median = numbers.at(medianIdx);

	int fuel = 0;
	for (std::vector<int>::const_iterator jt = numbers.begin(); jt != numbers.end(); ++jt)
	{
		int pos = *jt;
		int diff = fabsf(pos - median);
		fuel += diff;
	}
	std::cout << "Puzzle Thirteen: " << fuel << "\n";

	int average = (max + min) / 2;
	int direction = average > median ? 1 : -1;
	int start = median; int end = max;
	if (direction < 0)
	{
		end = min;
	}

	int bestFuel = INT_MAX;
	for (int i = start; i < end; i += direction)
	{
		int fuelTemp = 0;
		for (std::vector<int>::const_iterator jt = numbers.begin(); jt != numbers.end(); ++jt)
		{
			int pos = *jt;
			int diff = fabsf(pos - i);
			for(int j = 1; j <= diff; ++j)
			{
				fuelTemp += j;
			}
		}
		if (fuelTemp <= bestFuel)
		{
			bestFuel = fuelTemp;
		}
		else
		{
			break;
		}
	}

	std::cout << "Puzzle Fourteen: " << bestFuel << "\n";
}

void tokenise(std::string& s, std::vector<std::string>& vec, char delim)
{
	// we are looking for all instances of 1/4/7/8 (2, 4, 3, 7)
	int delimiter = s.find(' ');
	int start = 0;
	while(delimiter != std::string::npos)
	{
		std::string token = s.substr(start, delimiter - start);
		vec.push_back(token);
		start = delimiter + 1;
		delimiter = s.find(' ', delimiter + 1);
	}
	std::string token = s.substr(start);
	vec.push_back(token);
}

void DayEight()
{
	std::ifstream exprFile("DayEight.txt");
	std::string singleExpr;
	std::vector<std::string> input;
	std::vector<std::string> output;

	int min = INT_MAX;
	int max = INT_MIN;

	while (std::getline(exprFile, singleExpr)) // Gets a full line from the file
	{
		int delimiter = singleExpr.find('|');
		if(delimiter != std::string::npos)
		{
			input.push_back(singleExpr.substr(0, delimiter - 1));
			output.push_back(singleExpr.substr(delimiter + 2));
		}
	}

	int answer = 0;
	for (std::string s : output)
	{
		// we are looking for all instances of 1/4/7/8 (2, 4, 3, 7)
		int delimiter = s.find(' ');
		int start = 0;
		while(delimiter != std::string::npos)
		{
			std::string token = s.substr(start, delimiter - start);
			const int length = token.length();
			if(length == 2 || length == 4 || length == 3 || length == 7)
			{
				answer++;
			}			
			start = delimiter + 1;
			delimiter = s.find(' ', delimiter + 1);
		}
		std::string token = s.substr(start);
		const int length = token.length();
		if(length == 2 || length == 4 || length == 3 || length == 7)
		{
			answer++;
		}
	}
	std::cout << "Puzzle Fifteen: " << answer << "\n";

	std::vector<int> answers;
	int count = 0;
	for (std::string s : input)
	{
		std::string digits[10];

		std::vector<std::string> tokens;
		tokenise(s, tokens, ' ');

		for (std::string t : tokens)
		{
			switch(t.length())
			{
			case 2: digits[1] = t; break;
			case 4: digits[4] = t; break;
			case 3: digits[7] = t; break;
			case 7: digits[8] = t; break;
			default: break;
			}
		}

		for (std::string t : tokens)
		{
			switch (t.length())
			{
			case 5: // 2, 3, 5. 3 contains 1. 
			{
				// check 1
				int a = t.find(digits[1].at(0));
				int b = t.find(digits[1].at(1));
				if(a != std::string::npos && b != std::string::npos)
					digits[3] = t;
				else
				{	// 5 has 3 digits in common with 4, 2 only has 3
					int matches = 0;
					for (int i = 0; i < 4; ++i)
					{
						int a = t.find(digits[4].at(i));
						if(a != std::string::npos) matches++;
					}
					if(matches == 3) digits[5] = t;
					else digits[2] = t;
				}
			}
			break;
			case 6: //0, 6, 9. 6 doesn't contain 1
			{
				int a = t.find(digits[1].at(0));
				int b = t.find(digits[1].at(1));
				if(a == std::string::npos || b == std::string::npos)
					digits[6] = t;
				else // 0 or 9. 9 contains all of 4
				{
					int matches = 0;
					for (int i = 0; i < 4; ++i)
					{
						int a = t.find(digits[4].at(i));
						if(a != std::string::npos) matches++;
					}
					if(matches == 4) digits[9] = t;
					else digits[0] = t;
				}
			}
			break;
			}
		}

		bool safe = true;
		for (int i = 0; i < 10; ++i)
		{
			if (digits[i].empty())
			{
				safe = false;
				std::cout << "Uh Oh\n";				
			}
		}

		if (safe)
		{
			std::vector<std::string> outtokens;
			tokenise(output.at(count), outtokens, ' ');

			int answer = 0;
			for (std::string o : outtokens)
			{
				for (int d = 0; d < 10; ++d)
				{
					int len = digits[d].length();
					if(o.length() != len) continue;

					bool found = true;
					for (int di = 0; di < len; ++di)
					{
						int a = o.find(digits[d].at(di));
						if(a == std::string::npos) 
						{
							found = false;
							break;
						}
					}
					if (found)
					{
						answer *= 10;
						answer += d;
					}
				}
			}
			answers.push_back(answer);
		}
		count++;
	}

	int total = 0;
	for(int a : answers)
		total += a;
	std::cout << "Puzzle Sixteen: " << total << "\n";

}

int CheckBasin(std::set<std::pair<int, int> >& theSet, std::vector<std::string>& heights, int x, int y, int dirx, int diry)
{
	const int max = 100; // we know this. soz

	int nextx = x + dirx;
	int nexty = y + diry;

	if (nextx >= 0 && nextx < max && nexty >= 0 && nexty < 100)
	{
		int a = heights.at(nexty).at(nextx) - '0';
		if (a < 9)
		{
			std::pair<std::set<std::pair<int, int> >::iterator, bool> result = theSet.insert(std::pair<int, int>(nextx, nexty));
			if(result.second == true)
			{
				int neighbours = 1; // this specific idx
				neighbours += CheckBasin(theSet, heights, nextx, nexty, 0, 1);
				neighbours += CheckBasin(theSet, heights, nextx, nexty, 1, 0);
				neighbours += CheckBasin(theSet, heights, nextx, nexty, 0, -1);
				neighbours += CheckBasin(theSet, heights, nextx, nexty, -1, 0);
				return neighbours;
			}
		}
		return 0;
	}
	return 0;
}

void DayNine()
{
	std::ifstream exprFile("DayNine.txt");
	std::string singleExpr;
	std::vector<std::string> input;

	int x = 0;
	while (std::getline(exprFile, singleExpr)) // Gets a full line from the file
	{
		input.push_back(singleExpr);
		x = singleExpr.length();
	}

	const int y = input.size();

	std::vector<std::pair<int, int> > lows;

	int count = 0;
	int total = 0;
	for (std::string s : input)
	{
		for(int i = 0; i < x; ++i)
		{
			int a = s.at(i) - '0';

			if(i > 0)
				if(s.at(i-1) - '0' <= a)
					continue;

			if(i < (x-1))
				if(s.at(i+1) - '0' <= a)
					continue;

			if(count > 0)
				if(input.at(count-1).at(i) - '0' <= a)
					continue;

			if(count < y-1)
				if(input.at(count+1).at(i) - '0' <= a)
					continue;

			total += (a + 1);
			lows.push_back(std::pair<int, int>(i, count));
		}
		count++;
	}
	std::cout << "Puzzle Seventeen: " << total << "\n";

	std::list<int> totals;
	for (std::pair<int, int> pair : lows)
	{
		std::set<std::pair<int, int> > theSet;

		int tot = CheckBasin(theSet, input, pair.first, pair.second, 0, 0);

		totals.push_back(tot);
	}
	totals.sort(); totals.reverse();
	int tot = 1;
	int count3 = 0;
	for (int i : totals)
	{
		if(count3 < 3)
		{
			tot *= i;
			count3++;
		}
		else break;
	}
	std::cout << "Puzzle Seventeen: " << tot << "\n";
}

int main()
{
//	PuzzleTwo();
//	PuzzleThree();
//	PuzzleFour();
//	DayThree();
//	DayFour();
//	DayFive();
//	DaySix();
//	DaySeven();
//	DayEight();
	DayNine();
}
