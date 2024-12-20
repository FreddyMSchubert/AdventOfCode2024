#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <regex>
#include <exception>
#include <vector>
#include <algorithm>

#include <string>
#include <vector>

bool isPossibleToProduce(const std::string& design, const std::vector<std::string>& towel_patterns)
{
	size_t n = design.size();
	std::vector<bool> dp(n + 1, false);
	dp[0] = true; // Empty string can always be formed

	for (size_t i = 1; i <= n; ++i) {
		for (const std::string& pattern : towel_patterns)
		{
			size_t pat_len = pattern.size();
			if (pat_len > i) continue;

			if (design.compare(i - pat_len, pat_len, pattern) == 0)
			{
				if (dp[i - pat_len])
				{
					dp[i] = true;
					break;
				}
			}
		}
	}

	return dp[n];
}


int main()
{
	std::ifstream input;
	input.open("../input.txt");
	std::vector<std::string> lines;
	std::string line;
	while (std::getline(input, line))
	{
		lines.push_back(line);
	}

	std::string towel_patterns_line = lines[0];
	std::vector<std::string> towel_patterns;
	std::stringstream ss(towel_patterns_line);
	std::string token;
	while (std::getline(ss, token, ','))
	{
		token.erase(0, token.find_first_not_of(" \t\r\n"));
		token.erase(token.find_last_not_of(" \t\r\n") + 1);
		towel_patterns.push_back(token);
	}

	int index = 2;

	std::vector<std::string> desired_designs;
	while (index < lines.size())
	{
		if (!lines[index].empty())
		{
			desired_designs.push_back(lines[index]);
		}
		++index;
	}

	int valid_designs = 0;
	for (const auto& design : desired_designs)
	{
		if (isPossibleToProduce(design, towel_patterns))
		{
			++valid_designs;
			std::cout << "Design " << design << " is possible" << std::endl;
		}
		else
		{
			std::cout << "Design " << design << " is impossible" << std::endl;
		}
	}

	std::cout << "Valid designs: " << valid_designs << std::endl;

	return 0;
}
