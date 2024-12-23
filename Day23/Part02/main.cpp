#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <regex>
#include <exception>
#include <vector>
#include <algorithm>
#include <map>
#include <functional>
#include <utility>
#include <unordered_set>

void findCliqueDFS(
	const std::string& pc,
	const std::unordered_map<std::string, std::unordered_set<std::string>>& connections,
	std::vector<std::string>& currentClique,
	std::unordered_set<std::string>& visited,
	std::vector<std::string>& largestClique)
{
	currentClique.push_back(pc);
	if (currentClique.size() > largestClique.size())
		largestClique = currentClique;
	visited.insert(pc);

	for (const auto& neighbor : connections.at(pc))
	{
		bool isConnectedToAll = true;
		for (const auto& member : currentClique)
		{
			if (member == neighbor) continue;
			if (connections.at(neighbor).find(member) == connections.at(neighbor).end())
			{
				isConnectedToAll = false;
				break;
			}
		}

		if (isConnectedToAll && !visited.count(neighbor))
		{
			findCliqueDFS(neighbor, connections, currentClique, visited, largestClique);
		}
	}

	currentClique.pop_back();
}

int main()
{
	std::ifstream input;
	input.open("../input.txt");
	std::vector<std::string> lines;
	std::string line;
	uint64_t sum = 0;
	while (std::getline(input, line))
	{
		lines.push_back(line);
	}

	std::unordered_map<std::string, std::unordered_set<std::string>> connections;
	for (const auto& l : lines)
	{
		size_t dash_pos = l.find('-');
		if (dash_pos == std::string::npos)
		{
			throw std::runtime_error("Invalid input");
		}
		std::string first = l.substr(0, dash_pos);
		std::string second = l.substr(dash_pos + 1);
		connections[first].insert(second);
		connections[second].insert(first);
	}

	std::vector<std::string> largestClique;

	for (const auto& [node, neighbors] : connections)
	{
		std::vector<std::string> currentClique;
		std::unordered_set<std::string> visited;
		findCliqueDFS(node, connections, currentClique, visited, largestClique);
	}

	std::sort(largestClique.begin(), largestClique.end());

	for (size_t i = 0; i < largestClique.size(); ++i)
	{
		std::cout << largestClique[i];
		if (i < largestClique.size() - 1)
			std::cout << ",";
	}
	std::cout << std::endl;

	return 0;
}
