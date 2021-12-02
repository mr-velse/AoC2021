// AoC2021.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <fstream>

#include "Inputs.h"

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
		if(space != std::string::npos)
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

int main()
{
	PuzzleTwo();
	PuzzleThree();
	PuzzleFour();
}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
