#pragma once

#include <vector>
#include <algorithm>
#include <list>
#include <map>
#include <string>
#include <thread>


struct Caves
{
	struct Node
	{
		std::string name;
		std::vector<Node*> connections;
		bool major = true;
		bool start = false;
		bool end = false;
	};

	std::map<std::string, Node> nodes;

	void Add(std::string name);

	void AddConnection(std::string a, std::string b);

	int ExhaustiveVisit(bool pt2);
	
	void RecurseVisit(Node& second, std::vector<Node*>& path, std::vector<std::vector<Node*> >& paths);
};
