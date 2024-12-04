#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <regex>
#include <exception>
#include <vector>

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

	int crosses = 0;

	// loop through every grid cell
	for (size_t i = 0; i <= lines.size() - 3; i++)
	{
		for (size_t j = 0; j <= lines[i].length() - 3; j++)
		{
			char cl = lines[i][j];
			char cr = lines[i][j + 2];

			/*
			M.S
			.A.
			M.S
			*/

			std::cout << "Checking row " << i << " col " << j << " with cl " << cl << " and cr " << cr << std::endl;

			if (cl == 'M' && cr == 'M')
			{
				std::cout << "- Attempting to match M.M" << std::endl;
				std::cout << "- Match middle: " << (lines[i + 1][j + 1] == 'A') << " match top right: " << (lines[i + 2][j] == 'S') << " match bottom right: " << (lines[i + 2][j + 2] == 'S') << std::endl;
				if (lines[i + 1][j + 1] == 'A' && lines[i + 2][j] == 'S' && lines[i + 2][j + 2] == 'S')
				{
					crosses++;
				}
			}
			else if (cl == 'M' && cr == 'S')
			{
				std::cout << "- Attempting to match M.S" << std::endl;
				std::cout << "- Match middle: " << (lines[i + 1][j + 1] == 'A') << " match top right: " << (lines[i + 2][j] == 'M') << " match bottom right: " << (lines[i + 2][j + 2] == 'S') << std::endl;
				if (lines[i + 1][j + 1] == 'A' && lines[i + 2][j] == 'M' && lines[i + 2][j + 2] == 'S')
				{
					crosses++;
				}
			}
			else if (cl == 'S' && cr == 'M')
			{
				std::cout << "- Attempting to match S.M" << std::endl;
				std::cout << "- Match middle: " << (lines[i + 1][j + 1] == 'A') << " match top right: " << (lines[i + 2][j] == 'S') << " match bottom right: " << (lines[i + 2][j + 2] == 'M') << std::endl;
				if (lines[i + 1][j + 1] == 'A' && lines[i + 2][j] == 'S' && lines[i + 2][j + 2] == 'M')
				{
					crosses++;
				}
			}
			else if (cl == 'S' && cr == 'S')
			{
				std::cout << "- Attempting to match S.S" << std::endl;
				std::cout << "- Match middle: " << (lines[i + 1][j + 1] == 'A') << " match top right: " << (lines[i + 2][j] == 'M') << " match bottom right: " << (lines[i + 2][j + 2] == 'M') << std::endl;
				if (lines[i + 1][j + 1] == 'A' && lines[i + 2][j] == 'M' && lines[i + 2][j + 2] == 'M')
				{
					crosses++;
				}
			}
		}
	}

	std::cout << "Crosses: " << crosses << std::endl;
}
