#include "CaveNetwork.h"

void RecurseVisitThreaded(const Caves::Node& second, const std::vector<Caves::Node*>* path, int& total, bool pt2)
{
	int num_visits = pt2 ? 2 : 1;

	std::vector<Caves::Node*> pathCopy(path->begin(), path->end());
	for (int i = 0; i < second.connections.size(); ++i)
	{
		if (i == 0)
		{
			if (second.connections[i]->end == true) // stop
			{
				total++;
				continue;
			}

			if (second.connections[i]->major == false) // if it is a minor we only visit it if it isn't already in the list
			{
				int count = std::count(path->begin(), path->end(), second.connections[i]);
				if(count >= num_visits)
				{
					continue;
				}
				else if(pt2 && count == 1)
				{
					bool escape = false;
					for (Caves::Node* n : pathCopy)
					{
						if (n->major == false)
						{
							int count = std::count(pathCopy.begin(), pathCopy.end(), n);
							if (count >= num_visits)
							{
								escape = true;
								break;
							}
						}
					}
					if(escape) continue; // we already found a double
				}
			}
			std::vector<Caves::Node*>* pathThread = new std::vector<Caves::Node*>(path->begin(), path->end());
			pathThread->push_back(second.connections[i]);

			int totalthread = 0;
		//	std::thread t(RecurseVisitThreaded, *(second.connections[i]), pathThread, std::ref(totalthread));
			RecurseVisitThreaded(*(second.connections[i]), pathThread, total, num_visits);
		//	t.join();
		//	total += totalthread;
		}
		else
		{
			if(second.connections[i]->end == true)
			{
				total++;
				continue;
			}

			if (second.connections[i]->major == false) // if it is a minor we only visit it if it isn't already in the list
			{
				int count = std::count(pathCopy.begin(), pathCopy.end(), second.connections[i]);
				if(count >= num_visits)
				{
					continue; // definitely too many
				}
				else if(pt2 && count == 1)
				{
					bool escape = false;
					for (Caves::Node* n : pathCopy)
					{
						if (n->major == false)
						{
							int count = std::count(pathCopy.begin(), pathCopy.end(), n);
							if (count >= num_visits)
							{
								escape = true;
								break;
							}
						}
					}
					if(escape) continue; // we already found a double
				}
			}

			std::vector<Caves::Node*>* pathThread = new std::vector<Caves::Node*>(path->begin(), path->end());
			pathThread->push_back(second.connections[i]);

			int totalthread = 0;
		//	std::thread t(RecurseVisitThreaded, *(second.connections[i]), pathThread, std::ref(totalthread));		
			RecurseVisitThreaded(*(second.connections[i]), pathThread, total, num_visits);
		//	t.join();
		//	total += totalthread;
		}
	}

	delete path; // we created the memory for this before we made the thread, can now delete it.
}

void Caves::Add(std::string name)
{
	std::pair<std::map<std::string, Node>::iterator, bool> result = nodes.insert(std::pair<std::string, Node>(name, Node()));
	result.first->second.name = name;
	char c = name.at(0);
	result.first->second.major = c < 'a';
}

void Caves::AddConnection(std::string a, std::string b)
{
	std::map<std::string, Node>::iterator finda = nodes.find(a);
	if(finda == nodes.end())
		Add(a);
	std::map<std::string, Node>::iterator findb = nodes.find(b);
	if(findb == nodes.end())
		Add(b);

	int pos = b.find("start");
	if(pos == std::string::npos) // don't bother adding the start node to the list of connections, we never return to it.
		nodes[a].connections.push_back(&(nodes[b]));

	pos = a.find("start");
	if(pos == std::string::npos) // don't bother adding the start node to the list of connections, we never return to it.
		nodes[b].connections.push_back(&(nodes[a]));
}

int Caves::ExhaustiveVisit(bool pt2)
{
	std::string start("start");
	std::string end("end");

	Node& startNode = nodes[start];
	Node& endNode = nodes[end];
	startNode.start = true;
	endNode.end = true;

	std::vector<std::vector<Node*> > paths;
	paths.reserve(4096);

	std::vector<int> totalthreaded;
	for (int i = 0; i < startNode.connections.size(); ++i)
	{
		//	paths.push_back(std::vector<Node*>());
		//	paths.back().push_back(&startNode);
		//	paths.back().push_back(startNode.connections[i]);

		std::vector<Node*>* pathThread = new std::vector<Node*>();
		pathThread->push_back(&startNode);
		pathThread->push_back(startNode.connections[i]);

		totalthreaded.push_back(0);
		std::thread t(RecurseVisitThreaded, *(startNode.connections[i]), pathThread, std::ref(totalthreaded.back()), pt2);
		t.join();
		//RecurseVisit(*(startNode.connections[i]), paths.back(), paths);
		//paths.erase(std::remove_if(paths.begin(), paths.end(),[](std::vector<Node*> v){ return v.back()->end == false; } ));
	}

	int total = 0;
	for (int i : totalthreaded)
	{
		total += i;
	}

	return total;
}

void Caves::RecurseVisit(Node& second, std::vector<Node*>& path, std::vector<std::vector<Node*> >& paths)
{
	bool pathUsed = false;
	std::vector<Node*> pathCopy(path.begin(), path.end());
	for (int i = 0; i < second.connections.size(); ++i)
	{
		if (i == 0)
		{
			if (second.connections[i]->end == true) // stop
			{
				path.push_back(second.connections[i]);
				pathUsed = true;
				continue;
			}

			if (second.connections[i]->major == false) // if it is a minor we only visit it if it isn't already in the list
			{
				//	std::vector<Node*>::iterator it = std::find(path.begin(), path.end(), second.connections[i]);
				//	if(it != path.end())
				//		continue;
				int count = std::count(path.begin(), path.end(), second.connections[i]);
				if(count >= 2)
				{
					auto it = std::find(paths.begin(), paths.end(), path);
					paths.erase(it);
					continue;
				}

				// we also only visit it if it is a leaf node AND this node is also minor 
				//	if(second.connections[i]->connections.size() == 1 && second.major == false)
				//	{
				//		continue;
				//	}
			}
			path.push_back(second.connections[i]);
			RecurseVisit(*(second.connections[i]), path, paths);
		}
		else
		{
			bool end = false;
			if(second.connections[i]->end == false)
			{
				if (second.connections[i]->major == false) // if it is a minor we only visit it if it isn't already in the list
				{
					//	std::vector<Node*>::iterator it = std::find(pathCopy.begin(), pathCopy.end(), second.connections[i]);
					//	if(it != pathCopy.end())
					//		continue;

					int count = std::count(pathCopy.begin(), pathCopy.end(), second.connections[i]);
					if(count >= 2)
					{
						continue;
					}

					// we also only visit it if it is not a leaf node AND this node is also minor
					//	if(second.connections[i]->connections.size() == 1 && second.major == false)
					//		continue;
				}
			}
			else 
				end = true;

			paths.push_back(std::vector<Node*>());
			for(int j = 0; j < pathCopy.size(); ++j)
			{
				paths.back().push_back(pathCopy[j]);
			}				
			paths.back().push_back(second.connections[i]);

			if(!end)
			{
				RecurseVisit(*(second.connections[i]), paths.back(), paths);
			}
		}
	}
}