#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <regex>
#include <exception>
#include <vector>
#include <algorithm>

int main()
{
	int64_t outputNbr = 0;
	bool print = false;
	int maxTrailHeadId = 0;

	std::ifstream input;
	input.open("../input.txt");
	std::vector<std::string> lines;
	std::string line;
	while (std::getline(input, line))
	{
		lines.push_back(line);
	}

	// create a vector of int64_t
	std::vector<int64_t> stones;
	std::istringstream iss(lines[0]);
	std::string token;
	while (std::getline(iss, token, ' '))
	{
		stones.push_back(std::stoll(token));
	}

	for (int i = 0; i < 75; i++)
	{
		std::cout << "Blink " << i << std::endl;
		std::vector<int64_t> newStones;
		for (int j = 0; j < stones.size(); j++)
		{
			std::string str = std::to_string(stones[j]);
			if (stones[j] == 0)
				newStones.push_back(1);
			else if (str.size() % 2 == 0)
			{
				int half = static_cast<int>(str.size()) / 2;
				std::string left = str.substr(0, half);
				std::string right = str.substr(half);
				newStones.push_back(std::stoll(left));
				newStones.push_back(std::stoll(right));
			}
			else
			{
				newStones.push_back(stones[j] * 2024);
			}

		}
		stones = newStones;
	}

	std::cout << "Number of stones after 25 blinks: " << stones.size() << std::endl;
}
