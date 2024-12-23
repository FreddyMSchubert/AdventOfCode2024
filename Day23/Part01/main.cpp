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

	// all node names
	std::vector<std::string> nodes;
	for (const auto& c : connections)
		nodes.push_back(c.first);
	
	// find all sets of 3
	std::vector<std::vector<std::string>> sets;
	for (size_t i = 0; i < nodes.size(); ++i)
	{
		for (size_t j = i + 1; j < nodes.size(); ++j)
		{
			if (connections[nodes[i]].find(nodes[j]) != connections[nodes[i]].end())
			{
				for (size_t k = j + 1; k < nodes.size(); ++k)
				{
					if (connections[nodes[i]].find(nodes[k]) != connections[nodes[i]].end() &&
						connections[nodes[j]].find(nodes[k]) != connections[nodes[j]].end())
					{
						sets.push_back({ nodes[i], nodes[j], nodes[k] });
					}
				}
			}
		}
	}

	size_t filtered_count = 0;
	for (const auto& s : sets)
	{
		for (const auto& n : s)
		{
			if (!n.empty() && (n[0] == 't' || n[0] == 'T'))
			{
				++filtered_count;
				break;
			}
		}
	}

	std::cout << "Number of sets: " << filtered_count << std::endl;
}
