#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

bool isValid(std::vector<int> nbrs)
{
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
		return false;
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
		return false;
	}

	return true;
}

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

		for (size_t i = 0; i < nbrs.size(); i++)
		{
			std::vector<int> nbrswithouti = nbrs;
			nbrswithouti.erase(nbrswithouti.begin() + i);
			if (isValid(nbrswithouti))
			{
				safeReports++;
				break;
			}
		}
	}

	std::cout << "Safe reports with problem dampener: " << safeReports << std::endl;
}
