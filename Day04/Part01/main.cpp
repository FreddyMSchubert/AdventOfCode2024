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

	std::vector<std::string> potentialHits;

	int len = std::string("XMAS").length();

	// Horizontal
	for (size_t i = 0; i < lines.size(); i++)
	{
		for (size_t j = 0; j < lines[i].length() - len + 1; j++)
		{
			std::string sub = lines[i].substr(j, len);
			potentialHits.push_back(sub);
		}
	}

	// Vertical
	for (size_t i = 0; i < lines.size() - len + 1; i++)
	{
		for (size_t j = 0; j < lines[i].length(); j++)
		{
			std::string sub = "";
			for (int k = 0; k < len; k++)
			{
				sub += lines[i + k][j];
			}
			potentialHits.push_back(sub);
		}
	}

	// Diagonal top left to bottom right
	for (size_t i = 0; i < lines.size() - len + 1; i++)
	{
		for (size_t j = 0; j < lines[i].length() - len + 1; j++)
		{
			std::string sub = "";
			for (int k = 0; k < len; k++)
			{
				sub += lines[i + k][j + k];
			}
			potentialHits.push_back(sub);
		}
	}

	// diagonal bottom left to top right
	for (size_t i = len - 1; i < lines.size(); i++)
	{
		for (size_t j = 0; j < lines[i].length() - len + 1; j++)
		{
			std::string sub = "";
			for (int k = 0; k < len; k++)
			{
				sub += lines[i - k][j + k];
			}
			potentialHits.push_back(sub);
		}
	}

	// LOOP
	int occurences = 0;
	for (size_t i = 0; i < potentialHits.size(); i++)
	{
		std::string hit = potentialHits[i];
		if (hit == "XMAS" || hit == "SAMX")
		{
			std::cout << "Found XMAS at index " << i << " with word " << hit << std::endl;
			occurences++;
		}
	}

	std::cout << "Found " << occurences << " occurences of XMAS" << std::endl;
}
