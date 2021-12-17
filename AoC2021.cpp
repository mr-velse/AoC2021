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
#include <queue>
#include <sstream>

#include "Inputs.h"
#include "Bingo.h"
#include "Vents.h"
#include "LanternFish.h"
#include "CaveNetwork.h"

void DayOne()
{
	int window = 0;
	int increases = 0;
	int last = -1;

	int prev = INT_MAX;
	int puzz1ans = 0;

	int index = 0;
	for (int depth : Depths)
	{
		if(depth > prev)
			puzz1ans++;
		prev = depth;

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

	std::cout << "Puzzle One: " << puzz1ans << "\n";
	std::cout << "Puzzle Two: " << increases << "\n";
}

void DayTwo()
{
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
		std::cout << "Puzzle Three: " << answer << "\n";
	}
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
		std::cout << "Puzzle Four: " << answer << "\n";
	}
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

	const uint64_t answer2 = oxynum * c02num;
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
	uint64_t count = fishies->size();
	uint64_t answers[6];

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

void DayTen()
{
	std::ifstream exprFile("DayTen.txt");
	std::string singleExpr;
	std::vector<std::string> input;

	int x = 0;
	while (std::getline(exprFile, singleExpr)) // Gets a full line from the file
	{
		input.push_back(singleExpr);
		x = singleExpr.length();
	}

	std::vector<std::string> incomplete;

	int score = 0;
	for (std::string s : input)
	{
		std::list<char> chars;
		for(int i = 0; i < s.length(); ++i)
		{
			char corruptChar = 0;
			char c = s.at(i);
			switch (c)
			{
			case '{':
			case '[':
			case '(':
			case '<':
				chars.push_back(c);
				break;
			case '}':
			{
				if (chars.back() == '{')
				{
					chars.pop_back();
				}
				else corruptChar = c;
			} break;
			case ']':
			{
				if (chars.back() == '[')
				{
					chars.pop_back();
				}
				else corruptChar = c;
			} break;
			case ')':
			{
				if (chars.back() == '(')
				{
					chars.pop_back();
				}
				else corruptChar = c;
			} break;
			case '>':
			{
				if (chars.back() == '<')
				{
					chars.pop_back();
				}
				else corruptChar = c;
			} break;

			}
			if (corruptChar != 0)
			{
				switch (c)
				{
				case '}': score += 1197; break;
				case ']': score += 57; break;
				case ')': score += 3; break;
				case '>': score += 25137; break;
				}
				break;
			}
			else if (i == s.length() - 1) // last char
			{
				incomplete.push_back(s);
			}
		}
	}

	std::cout << "Puzzle Eighteen: " << score << "\n";

	std::vector<uint64_t> scores;
	for (std::string s : incomplete)
	{
		std::list<char> needClosing;
		std::list<char> closers;
	//	std::string s = "[({(<(())[]>[[{[]{<()<>>";
		for (int i = s.length() - 1; i >= 0; i--)
		{
			char c = s.at(i);

			switch (c)
			{
			case '}':
			case ']':
			case ')':
			case '>':
				closers.push_front(c); break;
			case '{':
				if(closers.empty() || closers.front() != '}')
					needClosing.push_back(c);
				else
					closers.pop_front();
				break;
			case '[':
				if(closers.empty() || closers.front() != ']')
					needClosing.push_back(c);
				else
					closers.pop_front();
				break;
			case '(':
				if(closers.empty() || closers.front() != ')')
					needClosing.push_back(c);
				else
					closers.pop_front();
				break;
			case '<':
				if(closers.empty() || closers.front() != '>')
					needClosing.push_back(c);
				else
					closers.pop_front();
				break;
			}
		}

		uint64_t score = 0;
		for (char c : needClosing)
		{
			score *= 5;
			switch (c)
			{
			case '{': score += 3; break;
			case '[': score += 2; break;
			case '(': score += 1; break;
			case '<': score += 4; break;
			}
		}
		scores.push_back(score);
	}
	std::sort(scores.begin(), scores.end());
	int mid = scores.size() / 2;
	std::cout << "Puzzle Nineteen: " << scores[mid] << "\n";
}

void DayEleven()
{
	std::ifstream exprFile("DayEleven.txt");
	std::string singleExpr;
	int data[10][10];
	bool flashed[10][10];
	int firstAllFlash = -1;

	int row = 0;
	while (std::getline(exprFile, singleExpr)) // Gets a full line from the file
	{
		for(int i = 0; i < 10; ++i)
		{
			char x = singleExpr.at(i);
			data[i][row] = std::atoi(&x);
			flashed[i][row] = false;
		}
		row++;
	}

	uint64_t flashes = 0;
	for (int step = 0; step < 1000; ++step)
	{
		// initial increase
		for(int i = 0; i < 10; ++i)
		{
			for(int j = 0; j < 10; ++j)
			{
				data[i][j]++;
			}
		}

		bool hasflashed = false;
		do
		{
			hasflashed = false;
			for(int i = 0; i < 10; ++i)
			{
				for(int j = 0; j < 10; ++j)
				{
					if (data[i][j] > 9 && flashed[i][j] == false) // flash
					{
						hasflashed = true;
						flashed[i][j] = true;
						const bool negivalid = i > 0;
						const bool negjvalid = j > 0;
						const bool posivalid = i < 9;
						const bool posjvalid = j < 9;

						if(negivalid)
						{
							if(negjvalid) data[i-1][j-1]++;
							data[i-1][j]++;
							if(posjvalid) data[i-1][j+1]++;
						}
						if(posivalid)
						{
							if(negjvalid) data[i+1][j-1]++;
							data[i+1][j]++;
							if(posjvalid) data[i+1][j+1]++;
						}
						if(negjvalid) data[i][j-1]++;
						if(posjvalid) data[i][j+1]++;
					}

				}
			}
		} while(hasflashed == true);

		bool allFlashed = true;
		for(int i = 0; i < 10; ++i)
		{
			for(int j = 0; j < 10; ++j)
			{
				if (flashed[i][j] == true)
				{
					flashed[i][j] = false;
					data[i][j] = 0;
					if(step < 100)
					{
						flashes++;
					}
				}
				else
				{
					allFlashed = false;
				}
			}
		}
		if(allFlashed && firstAllFlash < 0)
		{
			firstAllFlash = step;
			break;
		}
	}
	std::cout << "Puzzle Twentyone: " << flashes << "\n";
	std::cout << "Puzzle Twentytwo: " << firstAllFlash + 1<< "\n";
}

void DayTwelve()
{
	std::ifstream exprFile("DayTwelve.txt");
	std::string singleExpr;

	Caves caves;

	while (std::getline(exprFile, singleExpr)) // Gets a full line from the file
	{
		int pos = singleExpr.find('-');
		if (pos != std::string::npos)
		{
			std::string first = singleExpr.substr(0, pos);
			std::string second = singleExpr.substr(pos+1);

			caves.AddConnection(first, second);
		}
	}

	std::cout << "Puzzle Twentythree: " << caves.ExhaustiveVisit(false) << "\n";
	std::cout << "Puzzle Twentyfour: " << caves.ExhaustiveVisit(true) << "\n";
}

void DayThirteen()
{
	std::ifstream exprFile("DayThirteen.txt");
	std::string singleExpr;

	std::vector<std::pair<int, int> > input;
	std::vector<std::pair<char, int> > folds;

	while (std::getline(exprFile, singleExpr)) // Gets a full line from the file
	{
		int pos = singleExpr.find(',');
		if (pos != std::string::npos)
		{
			std::string first = singleExpr.substr(0, pos);
			std::string second = singleExpr.substr(pos+1);

			input.push_back(std::pair<int,int>(std::stoi(first), std::stoi(second)));
		}
		else
		{
pos = singleExpr.find('=');
if (pos != std::string::npos)
{
	std::string first = singleExpr.substr(pos - 1, 1);
	std::string second = singleExpr.substr(pos + 1);

	folds.push_back(std::pair<char, int>(first.at(0), std::stoi(second)));
}
		}
	}
	bool part1 = true;
	for (std::pair<char, int>& p : folds)
	{
		if (p.first == 'x') // fold left
		{
			for (std::pair<int, int>& i : input)
			{
				if (i.first > p.second)
				{
					i.first -= (i.first - p.second) * 2;
				}
			}
		}
		else if (p.first == 'y') // fold up
		{
			for (std::pair<int, int>& i : input)
			{
				if (i.second > p.second)
				{
					i.second -= (i.second - p.second) * 2;
				}
			}
		}
		if (part1)
		{
			part1 = false;
			std::set<std::pair<int, int> > current = std::set<std::pair<int, int> >(input.begin(), input.end());
			std::cout << "Puzzle Twentyfive: " << current.size() << "\n";
		}
	}

	std::set<std::pair<int, int> > current = std::set<std::pair<int, int> >(input.begin(), input.end());

	int maxx, maxy; maxx = maxy = 0;
	for (std::pair<int, int> i : current)
	{
		if (i.first > maxx) maxx = i.first;
		if (i.second > maxy) maxy = i.second;
	}

	std::vector<std::string> lines;
	for (int i = 0; i <= maxy; ++i)
	{
		std::string s;
		s.append(maxx + 1, '.');
		lines.push_back(s);
	}
	for (std::pair<int, int> i : current)
	{
		lines.at(i.second).at(i.first) = '#';
	}

	std::cout << "Puzzle Twentysix: \n";
	for (std::string& s : lines)
	{
		std::cout << s << "\n";
	}
}

void DayFourteen()
{
	struct Rule
	{
		char a;
		char b;
		char r; // 'r'esult (what we insert)
		std::vector<int> p;
		uint64_t firedThisStep = 0;
		uint64_t firedNextStep = 0;
		Rule* depA;
		Rule* depB;
	};

	std::ifstream exprFile("DayFourteen.txt");
	std::string singleExpr;

	std::string first;
	std::vector<Rule> rules;

	while (std::getline(exprFile, singleExpr)) // Gets a full line from the file
	{
		if (first.empty())
		{
			first = singleExpr;
		}
		else if (!singleExpr.empty())
		{
			rules.push_back(Rule());
			rules.back().a = singleExpr.at(0);
			rules.back().b = singleExpr.at(1);
			rules.back().r = singleExpr.back();
		}
	}

	for (Rule& r : rules)
	{
		for (Rule& r2 : rules)
		{
			if(r.a == r2.a && r.r == r2.b) 
			{	r.depA = &r2; continue; }
			if(r.r == r2.a && r.b == r2.b) 
			{	r.depB = &r2; continue; }
		}
	}

	std::map<char, uint64_t> common;
	for (char c : first)
	{
		common.insert(std::pair<char, int>(c, 0));
	}

	// seed
	for(int i = 0; i < first.length(); ++i) // get each char
	{
		char ch = first[i];
		common[ch]++;

		if(i < (first.length() - 1))
		{
			char second = first[i+1];
			for (Rule& r : rules)
			{
				if (ch == r.a && second == r.b) // as soon as we find a valid one
				{
					r.firedThisStep++;
					break;
				}
			}
		}
	}

	for (int i = 0; i < 40; ++i)
	{
		for (Rule& r : rules)
		{
			if (r.firedThisStep > 0)
			{
				common[r.r] += r.firedThisStep;
				if(r.depA)
				{
					r.depA->firedNextStep += r.firedThisStep;
				}
				if (r.depB)
				{
					r.depB->firedNextStep += r.firedThisStep;
				}
				r.firedThisStep = 0;
			}
		}

		for (Rule& r : rules)
		{
			if(r.firedNextStep > 0) 
			{
				r.firedThisStep = r.firedNextStep;
				r.firedNextStep = 0;
			}
		}

		if (i == 9)
		{
			uint64_t max = 0;
			uint64_t min = ULLONG_MAX;
			char maxc, minc;
			int length = 0;
			for (std::pair<char, uint64_t> p : common)
			{
				if(p.second > max) { max = p.second; maxc = p.first; }
				if(p.second < min) { min = p.second; minc = p.first; }
				length += p.second;
			}

			std::cout << "Puzzle Twentyseven: " << max - min << "\n";	
		}
	}

	uint64_t max = 0;
	uint64_t min = ULLONG_MAX;
	char maxc, minc;
	int length = 0;
	for (std::pair<char, uint64_t> p : common)
	{
		if(p.second > max) { max = p.second; maxc = p.first; }
		if(p.second < min) { min = p.second; minc = p.first; }
		length += p.second;
	}

	std::cout << "Puzzle Twentyeight: " << max - min << "\n";	
}

void DayFifteen()
{
	struct Node
	{
		int value = 0;
		int x = 0;
		int y = 0;
		std::vector<Node*> neighbours;
	};
	std::ifstream exprFile("DayFifteen.txt");
	std::string singleExpr;

	std::vector<std::string> lines;
	std::vector<Node> nodes;

	int xmax, ymax; xmax = ymax = 0;
	while (std::getline(exprFile, singleExpr)) // Gets a full line from the file
	{
		lines.push_back(singleExpr);
		xmax = singleExpr.length();
		++ymax;
	}

	for(int ypos = 0; ypos < ymax; ypos++)
	{
		for(int xpos = 0; xpos < xmax; xpos++)
		{
			nodes.push_back(Node());
			char ch = lines[ypos].at(xpos);
			nodes.back().value = std::atoi(&ch);
			nodes.back().x = xpos;
			nodes.back().y = ypos;
		}
	}
	for(int xpos = 0; xpos < xmax; xpos++)
	{
		for(int ypos = 0; ypos < ymax; ypos++)
		{
			Node& n = nodes.at(xpos + (ypos * ymax));
			if(xpos > 0)
				n.neighbours.push_back(&(nodes.at((xpos -1) + (xmax * ypos))));
			if(ypos > 0)
				n.neighbours.push_back(&(nodes.at(xpos + (xmax * (ypos - 1)))));
			if(xpos < (xmax - 1))
				n.neighbours.push_back(&(nodes.at(xpos + 1 + (xmax * ypos))));
			if(ypos < (ymax - 1))
				n.neighbours.push_back(&(nodes.at(xpos + (xmax * (ypos + 1)))));
		}
	}
	{
		Node& start = nodes.front();
		Node& goal = nodes.back();

		std::set<Node*> openSet;
		openSet.insert(&start);

		// For node n, cameFrom[n] is the node immediately preceding it on the cheapest path from start
		// to n currently known.
		std::map<Node*, Node*> cameFrom;

		// For node n, gScore[n] is the cost of the cheapest path from start to n currently known.
		std::map<Node*, int> gScore; // := map with default value of Infinity
		gScore[&start] = 0;

		// For node n, fScore[n] := gScore[n] + h(n). fScore[n] represents our current best guess as to
		// how short a path from start to finish can be if it goes through n.
		std::map<Node*, int> fScore; // := map with default value of Infinity
		fScore[&start] = (xmax + ymax - start.x - start.y) * 10;

		bool success = false;
		std::vector<Node*> path;
		while(!openSet.empty())
		{	// This operation can occur in O(1) time if openSet is a min-heap or a priority queue
			Node* current = nullptr; //  := the node in openSet having the lowest fScore[] value
			int lowest = INT_MAX;
			for (Node* n : openSet)
			{
				std::map<Node*, int>::iterator it = fScore.find(n);
				if (it != fScore.end())
				{
					if (it->second < lowest)
					{
						current = it->first;
						lowest = it->second;
					}
				}
			}
			if(current == &goal)
			{
				path.push_back(current);

				std::map<Node*, Node*>::iterator it = cameFrom.find(current);
				while (it != cameFrom.end())
				{
					current = cameFrom[current];
					path.push_back(current);
					it = cameFrom.find(current);
				}

				success = true;
				break;
			}
		
			openSet.erase(current);

			for(Node* neighbor : current->neighbours)
			{
				std::map<Node*, int>::iterator it = gScore.find(neighbor);
				if (it == gScore.end())
					gScore[neighbor] = 1000000000; // arbitrary

				// d(current,neighbor) is the weight of the edge from current to neighbor
				// tentative_gScore is the distance from start to the neighbor through current
				int tentative_gScore = gScore[current] + neighbor->value;
				if(tentative_gScore < gScore[neighbor])
				{	// This path to neighbor is better than any previous one. Record it!
					cameFrom[neighbor] = current;
					gScore[neighbor] = tentative_gScore;
					int f = tentative_gScore + ((xmax + ymax - neighbor->x - neighbor->y)); // * 10);
				//	for(Node* n1 : neighbor->neighbours)
				//		f += n1->value; // favour the neighbour with lower value neighbours.
					fScore[neighbor] = f;
					std::set<Node*>::iterator it = openSet.find(neighbor);
					if(it == openSet.end())
					{					
						openSet.insert(neighbor);
					}
				}
			}
		}

		if (success)
		{
			int total = 0;
			for(Node* n : path)
				total += n->value;

			total -= start.value;

			std::cout << "Puzzle Twentynine: " << total << "\n";
		}
	}

	// expand to 5v5
	std::vector<Node>* nodes5x5 = new std::vector<Node>();
	nodes5x5->reserve(250000);
	for (int j = 0; j < ymax; ++j)
	{
		for(int f = 0; f < 5; ++f)
		{
			for(int i = 0; i < xmax; ++i)
			{
				const int idx = i + (j * xmax);
				nodes5x5->push_back(Node());
				nodes5x5->back().value = (nodes.at(idx).value + f);
				nodes5x5->back().x = nodes.at(idx).x + (f * xmax);
				nodes5x5->back().y = nodes.at(idx).y;
				if(nodes5x5->back().value > 9)
					nodes5x5->back().value -= 9;
			}
		}
	}
	xmax *= 5;
	for(int f = 1; f < 5; ++f)
	{
		for (int j = 0; j < ymax; ++j)
		{
			for(int i = 0; i < xmax; ++i)
			{
				const int idx = i + (j * xmax);
				nodes5x5->push_back(Node());
				nodes5x5->back().value = (nodes5x5->at(idx).value + f);
				nodes5x5->back().x = nodes5x5->at(idx).x;
				nodes5x5->back().y = nodes5x5->at(idx).y + (f * ymax);
				if(nodes5x5->back().value > 9)
					nodes5x5->back().value -= 9;
			}
		}
	}
	ymax *= 5;

	for(int xpos = 0; xpos < xmax; xpos++)
	{
		for(int ypos = 0; ypos < ymax; ypos++)
		{
			Node& n = nodes5x5->at(xpos + (ypos * ymax));
			if(xpos > 0)
				n.neighbours.push_back(&(nodes5x5->at((xpos -1) + (xmax * ypos))));
			if(ypos > 0)
				n.neighbours.push_back(&(nodes5x5->at(xpos + (xmax * (ypos - 1)))));
			if(xpos < (xmax - 1))
				n.neighbours.push_back(&(nodes5x5->at(xpos + 1 + (xmax * ypos))));
			if(ypos < (ymax - 1))
				n.neighbours.push_back(&(nodes5x5->at(xpos + (xmax * (ypos + 1)))));
		}
	}

	{
		Node& start = nodes5x5->front();
		Node& goal = nodes5x5->back();

		std::set<Node*> openSet;
		openSet.insert(&start);

		// For node n, cameFrom[n] is the node immediately preceding it on the cheapest path from start
		// to n currently known.
		std::map<Node*, Node*> cameFrom;

		// For node n, gScore[n] is the cost of the cheapest path from start to n currently known.
		std::map<Node*, int> gScore; // := map with default value of Infinity
		gScore[&start] = 0;

		// For node n, fScore[n] := gScore[n] + h(n). fScore[n] represents our current best guess as to
		// how short a path from start to finish can be if it goes through n.
		std::map<Node*, int> fScore; // := map with default value of Infinity
		fScore[&start] = (xmax + ymax - start.x - start.y) * 10;

		bool success = false;
		std::vector<Node*> path;
		while(!openSet.empty())
		{	// This operation can occur in O(1) time if openSet is a min-heap or a priority queue
			Node* current = nullptr; //  := the node in openSet having the lowest fScore[] value
			int lowest = INT_MAX;
			for (Node* n : openSet)
			{
				std::map<Node*, int>::iterator it = fScore.find(n);
				if (it != fScore.end())
				{
					if (it->second < lowest)
					{
						current = it->first;
						lowest = it->second;
					}
				}
			}
			if(current == &goal)
			{
				path.push_back(current);

				std::map<Node*, Node*>::iterator it = cameFrom.find(current);
				while (it != cameFrom.end())
				{
					current = cameFrom[current];
					path.push_back(current);
					it = cameFrom.find(current);
				}

				success = true;
				break;
			}

			openSet.erase(current);

			for(Node* neighbor : current->neighbours)
			{
				std::map<Node*, int>::iterator it = gScore.find(neighbor);
				if (it == gScore.end())
					gScore[neighbor] = 1000000000; // arbitrary

												   // d(current,neighbor) is the weight of the edge from current to neighbor
												   // tentative_gScore is the distance from start to the neighbor through current
				int tentative_gScore = gScore[current] + neighbor->value;
				if(tentative_gScore < gScore[neighbor])
				{	// This path to neighbor is better than any previous one. Record it!
					cameFrom[neighbor] = current;
					gScore[neighbor] = tentative_gScore;
					int f = tentative_gScore + ((xmax + ymax - neighbor->x - neighbor->y)); // * 10);
																							//	for(Node* n1 : neighbor->neighbours)
																							//		f += n1->value; // favour the neighbour with lower value neighbours.
					fScore[neighbor] = f;
					std::set<Node*>::iterator it = openSet.find(neighbor);
					if(it == openSet.end())
					{					
						openSet.insert(neighbor);
					}
				}
			}
		}

		if (success)
		{
			int total = 0;
			for(Node* n : path)
				total += n->value;

			total -= start.value;

			std::cout << "Puzzle Thirty: " << total << "\n";
		}
	}

}

struct Packet
{
	uint8_t version = 0;
	uint8_t id = 0;
	uint64_t value = 0;
	bool lengthid = 0;
	uint32_t length = 0; 
	std::vector<Packet> subs;

	int sum()
	{
		int total = version;
		for (Packet& p : subs)
		{
			total += p.sum();
		}
		return total;
	}

	uint64_t calc()
	{
		for (Packet& p : subs)
		{
			p.calc();
		}

		switch (id)
		{
			case 0: // sum
			{
				for (Packet& p : subs)
				{
					value += p.value;
				}
			} break;
			case 1: // mul
			{
				value = 1;
				for (Packet& p : subs)
				{
					value *= p.value;
				}
			} break;
			case 2: // min
			{
				value = UINT64_MAX;
				for (Packet& p : subs)
				{
					if(p.value < value)
						value = p.value;
				}
			} break;
			case 3: // max
			{
				for (Packet& p : subs)
				{
					if(p.value > value)
						value = p.value;
				}
			} break;
			case 5: // >
			{
				value = subs[0].value > subs[1].value ? 1 : 0;
			} break;
			case 6: // <
			{
				value = subs[0].value < subs[1].value ? 1 : 0;
			} break;
			case 7: // ==
			{
				value = subs[0].value == subs[1].value ? 1 : 0;
			} break;
		}
		return value;
	}

};

void BuildPacket(Packet& p, int& seek, std::vector<bool>& input, bool skipPadding)
{
	// parse header
	p.version += input.at(seek++) ? 1 : 0;	p.version = p.version << 1;
	p.version += input.at(seek++) ? 1 : 0;	p.version = p.version << 1;
	p.version += input.at(seek++) ? 1 : 0;

	p.id += input.at(seek++) ? 1 : 0;	p.id = p.id << 1;
	p.id += input.at(seek++) ? 1 : 0;	p.id = p.id << 1;
	p.id += input.at(seek++) ? 1 : 0;

	if (p.id == 4) // literal
	{
		// build the value
		bool carryOn = true;
		while(carryOn)
		{	
			carryOn = input.at(seek++);
			// read four bits into the value
			p.value = p.value << 1;
			p.value += input.at(seek++) ? 1 : 0;	p.value = p.value << 1;
			p.value += input.at(seek++) ? 1 : 0;	p.value = p.value << 1;
			p.value += input.at(seek++) ? 1 : 0;	p.value = p.value << 1;
			p.value += input.at(seek++) ? 1 : 0;
		}
		while(carryOn);
	}
	else // operator
	{
		p.lengthid = input.at(seek++); // 0 = read 15bits, 1 = read 11 bits
		p.length += input.at(seek++) ? 1 : 0;	p.length = p.length << 1;
		p.length += input.at(seek++) ? 1 : 0;	p.length = p.length << 1;
		p.length += input.at(seek++) ? 1 : 0;	p.length = p.length << 1;
		p.length += input.at(seek++) ? 1 : 0;	p.length = p.length << 1;
		p.length += input.at(seek++) ? 1 : 0;	p.length = p.length << 1;
		p.length += input.at(seek++) ? 1 : 0;	p.length = p.length << 1;
		p.length += input.at(seek++) ? 1 : 0;	p.length = p.length << 1;
		p.length += input.at(seek++) ? 1 : 0;	p.length = p.length << 1;
		p.length += input.at(seek++) ? 1 : 0;	p.length = p.length << 1;
		p.length += input.at(seek++) ? 1 : 0;	p.length = p.length << 1;
		p.length += input.at(seek++) ? 1 : 0;
		if (!p.lengthid)
		{
			p.length = p.length << 1;
			p.length += input.at(seek++) ? 1 : 0;	p.length = p.length << 1;
			p.length += input.at(seek++) ? 1 : 0;	p.length = p.length << 1;
			p.length += input.at(seek++) ? 1 : 0;	p.length = p.length << 1;
			p.length += input.at(seek++) ? 1 : 0;
		}

		if (p.lengthid) // 11 bits = number of subpackets
		{
			for (int i = 0; i < p.length; ++i)
			{
				p.subs.push_back(Packet());
				BuildPacket(p.subs.back(), seek, input, false);
			}
		}
		else // p.length is the number of bits to read
		{
			int runningLength = p.length;
			do
			{
				int oldSeek = seek;
				p.subs.push_back(Packet());
				BuildPacket(p.subs.back(), seek, input, false);
				runningLength -= (seek - oldSeek);
			}
			while (runningLength >= 11); // note - peek, do not increment
		}
	}
	if(skipPadding)
	{
		int rem = seek % 4;
		seek += (4 - rem); // padding
	}
}

void DaySixteen()
{
	std::map<char, uint8_t> hexmap;
	hexmap.insert(std::pair<char, uint8_t>('0', 0));
	hexmap.insert(std::pair<char, uint8_t>('1', 1));
	hexmap.insert(std::pair<char, uint8_t>('2', 2));
	hexmap.insert(std::pair<char, uint8_t>('3', 3));
	hexmap.insert(std::pair<char, uint8_t>('4', 4));
	hexmap.insert(std::pair<char, uint8_t>('5', 5));
	hexmap.insert(std::pair<char, uint8_t>('6', 6));
	hexmap.insert(std::pair<char, uint8_t>('7', 7));
	hexmap.insert(std::pair<char, uint8_t>('8', 8));
	hexmap.insert(std::pair<char, uint8_t>('9', 9));
	hexmap.insert(std::pair<char, uint8_t>('A', 10));
	hexmap.insert(std::pair<char, uint8_t>('B', 11));
	hexmap.insert(std::pair<char, uint8_t>('C', 12));
	hexmap.insert(std::pair<char, uint8_t>('D', 13));
	hexmap.insert(std::pair<char, uint8_t>('E', 14));
	hexmap.insert(std::pair<char, uint8_t>('F', 15));

	std::ifstream exprFile("DaySixteen.txt");
	std::string singleExpr;

	std::vector<bool> input;

	int xmax, ymax; xmax = ymax = 0;
	while (std::getline(exprFile, singleExpr)) // Gets a full line from the file
	{
		for(int i = 0; i < singleExpr.length(); ++i)
		{
			uint8_t x = hexmap[singleExpr.at(i)];
			input.push_back(x & 8);
			input.push_back(x & 4);
			input.push_back(x & 2);
			input.push_back(x & 1);
		}
	}

	std::vector<Packet> packets;

	int seek = 0;
	while (seek < (input.size() - 11))
	{
		packets.push_back(Packet());
		BuildPacket(packets.back(), seek, input, true);
	}

	int total = packets.front().sum();
	std::cout << "Puzzle Thirty-one: " << total << "\n";

	uint64_t calc = packets.front().calc();
	std::cout << "Puzzle Thirty-two: " << calc << "\n";
}

void DaySeventeen()
{
	std::string input("target area : x = 195..238, y = -93.. - 67");

	int ymax = -67;
	int ymin = -93;

	int xmin = 195;
	int xmax = 238;

	// x and y are independent so what are the most number of x steps that still reach the area?
	int mostxsteps = 0;
	bool vertical = false;

	std::set<int> validXvel;

	for (int i = 0; i <= xmax; ++i)
	{
		int xpos = 0;
		int xvel = i;
		int steps = 0;
		while (xvel > 0)
		{
			xpos += xvel;
			xvel--;
			if(xvel < 0) xvel = 0;
			steps++;

			if (xpos >= xmin && xpos <= xmax)
			{
				validXvel.insert(i);
				if (mostxsteps < steps)
				{
					mostxsteps = steps;
					if(xvel == 0 && !vertical)
						vertical = true;
					continue;
				}
			}
		}
	}

	std::vector<int> validYvel;

	int highestvalid = 0;
	// highest
	for (int i = -1000; i < 1000; ++i)
	{
		int ypos = 0;
		int yvel = i;
		int steps = 0;
		int highest = 0;
		while (ypos >= ymin && (vertical || steps <= mostxsteps))
		{
			ypos += yvel;
			yvel--;
			steps++;
			if(ypos > highest) highest = ypos;

			if (ypos >= ymin && ypos <= ymax)
			{
				highestvalid = highest;
				validYvel.push_back(i);
			}
		}
	}

	std::set<std::pair<int,int> > valids;
	for (int x : validXvel)
	{
		for (int y : validYvel)
		{
			int xpos = 0;
			int ypos = 0;
			int xvel = x;
			int yvel = y;
			while (ypos >= ymin && xpos <= xmax)
			{
				ypos += yvel;
				yvel--;
				xpos += xvel;
				xvel--;
				if(xvel < 0) xvel = 0;

				if (ypos >= ymin && ypos <= ymax && xpos >= xmin && xpos <= xmax)
				{
					valids.insert(std::pair<int,int>(x,y));
					break;
				}
			}
		}
	}

	std::cout << "Puzzle Thirty-three: " << highestvalid << "\n";

	std::cout << "Puzzle Thirty-four: " << valids.size() << "\n";
}

int main()
{
	DayOne();
	DayTwo();
	DayThree();
	DayFour();
	DayFive();
//	DaySix();
	DaySeven();
	DayEight();
	DayNine();
	DayTen();
	DayEleven();
	DayTwelve();
	DayThirteen();
	DayFourteen();
//	DayFifteen();
	DaySixteen();
	DaySeventeen();
}
