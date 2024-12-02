#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

int main()
{
	int safeReports = 0;

	std::ifstream input;
	input.open("../input.txt");
	if (!input.is_open() || !input.good())
	{
		std::cerr << "Error opening file" << std::endl;
		return 1;
	}
	std::string line;
	while (std::getline(input, line))
	{
		std::istringstream iss(line);
		int nbr;
		std::vector<int> nbrs;
		while (iss >> nbr)
		{
			nbrs.push_back(nbr);
		}

		bool valid = true;

		// 1. determine direction
		bool ascending = false;
		for (size_t i = 0; i < nbrs.size() - 1; i++)
		{
			if (nbrs[i] < nbrs[i + 1])
			{
				ascending = true;
				break;
			}
			else if (nbrs[i] > nbrs[i + 1])
			{
				ascending = false;
				break;
			}
		}

		// 2. verify direction
		for (size_t i = 0; i < nbrs.size() - 1; i++)
		{
			if (ascending && nbrs[i] > nbrs[i + 1])
			{
				valid = false;
				break;
			}
			else if (!ascending && nbrs[i] < nbrs[i + 1])
			{
				valid = false;
				break;
			}
			else if (nbrs[i] == nbrs[i + 1])
			{
				valid = false;
				break;
			}
		}
		if (!valid)
		{
			std::cout << "Line " << line << " is invalid because it contains numbers in the wrong order" << std::endl;
			continue;
		}

		// 3. calculate offsets
		int largestOffset = 0;
		for (size_t i = 0; i < nbrs.size() - 1; i++)
		{
			int offset = nbrs[i] - nbrs[i + 1];
			if (offset < 0)
			{
				offset = -offset;
			}
			if (offset > largestOffset)
			{
				largestOffset = offset;
			}
		}
		if (largestOffset > 3)
		{
			std::cout << "Line " << line << " is invalid because it contains numbers with an offset larger than 3" << std::endl;
			continue;
		}

		std::cout << "Line " << line << " is valid" << std::endl;

		safeReports++;
	}

	std::cout << "Safe reports: " << safeReports << std::endl;
}
