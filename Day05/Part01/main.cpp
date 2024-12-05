#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <regex>
#include <exception>
#include <vector>

bool doesRuleApply(const std::vector<int>& rules1, const std::vector<int>& rules2, const std::vector<int>& sequence) {
	for (size_t i = 0; i < rules1.size(); ++i) {
		int x = rules1[i];
		int y = rules2[i];
		int pos_x = -1, pos_y = -1;
		for (size_t j = 0; j < sequence.size(); ++j) {
			if (sequence[j] == x) pos_x = j;
			if (sequence[j] == y) pos_y = j;
		}
		if (pos_x != -1 && pos_y != -1 && pos_x > pos_y)
			return false;
	}
	return true;
}

int main()
{
	std::vector<std::string> lines;
	std::ifstream input;
	input.open("../input.txt");
	std::string line;
	while (std::getline(input, line))
	{
		lines.push_back(line);
	}

	std::vector<int> nbrs1;
	std::vector<int> nbrs2;

	bool start = true;

	int validsequences = 0;

	for (std::string l : lines)
	{
		std::cout << "yay " << l << std::endl;
		if (l.empty())
		{
			start = false;
			continue;
		}

		if (start)
		{
			std::cout << "yay1" << std::endl;
			int first, second;
			char delimiter;

			std::stringstream ss(l);
			ss >> first >> delimiter >> second;

			nbrs1.push_back(first);
			nbrs2.push_back(second);
		}
		else
		{
			std::cout << "yay2" << std::endl;
			std::vector<int> nbrs;

			std::stringstream ss(l);
			std::string num;
			while (std::getline(ss, num, ','))
				nbrs.push_back(std::stoi(num));

			if (doesRuleApply(nbrs1, nbrs2, nbrs))
			{
				// find middle
				std::cout << "For a length of " << nbrs.size() << " the middle is at " << nbrs.size() / 2 << std::endl;
				int middle = nbrs.size() / 2;
				validsequences += nbrs[middle];
			}
		}
	}

	std::cout << "Valid sequences: " << validsequences << std::endl;
}
