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
	std::ifstream input;
	input.open("../input.txt");
	std::vector<std::string> lines;
	std::string line;
	bool map = true;
	std::string moves;
	while (std::getline(input, line)) {
		if (map) {
			if (std::regex_match(line, std::regex("^[<>^v]+$"))) {
				map = false;
				moves += line;
			} else if (!line.empty()) {
				lines.push_back(line);
			}
		} else {
			moves += line;
		}
	}

	int robotX = 0;
	int robotY = 0;

	for (int y = 0; y < lines.size(); y++)
	{
		for (int x = 0; x < lines[y].size(); x++)
		{
			if (lines[y][x] == '@')
			{
				lines[y][x] = '.';
				robotX = x;
				robotY = y;
			}
		}
	}

	std::cout << "Moves: " << moves << std::endl;

	for (int i = 0; i < moves.size(); i++)
	{
		char move = moves[i];
		int newX = robotX;
		int newY = robotY;
		switch (move)
		{
			case '^':
				newY--;
				if (newY < 0)
					continue;
				break;
			case 'v':
				newY++;
				if (newY >= lines.size())
					continue;
				break;
			case '<':
				newX--;
				if (newX < 0)
					continue;
				break;
			case '>':
				newX++;
				if (newX >= lines[0].size())
					continue;
				break;
		}

		if (lines[newY][newX] == '.')
		{
			lines[newY][newX] = '@';
			lines[robotY][robotX] = '.';
			robotX = newX;
			robotY = newY;
		}
		else if (lines[newY][newX] == 'O')
		{
			int newBoxX = newX;
			int newBoxY = newY;
			while (lines[newBoxY][newBoxX] == 'O')
			{
				switch (move)
				{
					case '^':
						newBoxY--;
						break;
					case 'v':
						newBoxY++;
						break;
					case '<':
						newBoxX--;
						break;
					case '>':
						newBoxX++;
						break;
				}

				if (newBoxY < 0 || newBoxY >= lines.size() || newBoxX < 0 || newBoxX >= lines[0].size())
				{
					break;
				}
			}
			if (newBoxY < 0 || newBoxY >= lines.size() || newBoxX < 0 || newBoxX >= lines[0].size())
			{
				continue;
			}

			if (lines[newBoxY][newBoxX] == '.')
			{
				lines[newBoxY][newBoxX] = 'O';
				lines[newY][newX] = '@';
				lines[robotY][robotX] = '.';
				robotX = newX;
				robotY = newY;
			}
		}

		// print out
		for (int y = 0; y < lines.size(); y++)
		{
			std::cout << lines[y] << std::endl;
		}
	}

	int sum = 0;
	for (int y = 0; y < lines.size(); y++)
	{
		for (int x = 0; x < lines[y].size(); x++)
		{
			if (lines[y][x] == 'O')
			{
				sum += 100 * y + x;
			}
		}
	}
	std::cout << sum << std::endl;
}
