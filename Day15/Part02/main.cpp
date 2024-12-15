#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <regex>
#include <exception>
#include <vector>
#include <algorithm>

std::vector<std::string> getNewMap(std::vector<std::string> oldmap)
{
	int width = oldmap[0].size();
	int newWidth = width * 2;
	int height = oldmap.size();

	std::vector<std::string> newmap(height, std::string(newWidth, '.'));

	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			int x_new = x * 2;
			char current = oldmap[y][x];

			switch (current)
			{
				case '#':
					newmap[y][x_new] = '#';
					newmap[y][x_new + 1] = '#';
					break;
				case 'O':
					newmap[y][x_new] = '[';
					newmap[y][x_new + 1] = ']';
					break;
				case '@':
					newmap[y][x_new] = '@';
					newmap[y][x_new + 1] = '.'; // Robot occupies one space
					break;
				case '.':
				default:
					newmap[y][x_new] = '.';
					newmap[y][x_new + 1] = '.';
					break;
			}
		}
	}

	return newmap;
}

// gets [ as input
bool pushBox(std::vector<std::string> & lines, int x, int y, int deltaX, int deltaY, bool push = false)
{
	int targetX1 = x + deltaX;
	int targetY1 = y + deltaY;
	int targetX2 = x + deltaX + 1;
	int targetY2 = y + deltaY;

	if (targetX1 < 0 || targetX2 < 0 || targetX1 >= lines[0].size() || targetX2 >= lines[0].size() ||
		targetY1 < 0 || targetY1 >= lines.size() || targetY2 < 0 || targetY2 >= lines.size())
	{
		return false;
	}

	if (lines[targetY1][targetX1] == '#' || lines[targetY2][targetX2] == '#')
	{
		return false;
	}

	if (lines[targetY1][targetX1] == '[')
	{
		if (!pushBox(lines, targetX1, targetY1, deltaX, deltaY, push))
		{
			return false;
		}
	}
	if (lines[targetY1][targetX1] == ']')
	{
		if (!pushBox(lines, targetX1 - 1, targetY1, deltaX, deltaY, push))
		{
			return false;
		}
	}
	if (lines[targetY2][targetX2] == '[')
	{
		if (!pushBox(lines, targetX2, targetY2, deltaX, deltaY, push))
		{
			return false;
		}
	}
	if (lines[targetY2][targetX2] == ']')
	{
		if (!pushBox(lines, targetX2 - 1, targetY2, deltaX, deltaY, push))
		{
			return false;
		}
	}

	if (push)
	{
		lines[targetY1][targetX1] = '[';
		lines[targetY2][targetX2] = ']';
		lines[y][x] = '.';
		lines[y][x + 1] = '.';
	}
	return true;
}

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

	lines = getNewMap(lines);

	int robotX = 0;
	int robotY = 0;

	for (int y = 0; y < lines.size(); y++)
	{
		for (int x = 0; x < lines[y].size(); x++)
		{
			if (lines[y][x] == '@')
			{
				robotX = x;
				robotY = y;
			}
		}
	}

	for (size_t i = 0; i < moves.size(); i++)
	{
		int deltaX = 0;
		int deltaY = 0;
		char move = moves[i];
		for (int y = 0; y < lines.size(); y++)
		{
			std::cout << lines[y] << std::endl;
		}
		std::cout << "Move: " << move << std::endl;
		int newX = robotX;
		int newY = robotY;
		switch (move)
		{
			case '^':
				deltaY = -1;
				break;
			case 'v':
				deltaY = 1;
				break;
			case '<':
				deltaX = -1;
				break;
			case '>':
				deltaX = 1;
				break;
		}

		newX += deltaX;
		newY += deltaY;

		if (newY < 0 || newY >= lines.size() || newX < 0 || newX >= lines[0].size())
		{
			continue;
		}

		if (lines[newY][newX] == '.')
		{ // Simple move
			lines[newY][newX] = '@';
			lines[robotY][robotX] = '.';
			robotX = newX;
			robotY = newY;
		}
		else if (lines[newY][newX] == '[' || lines[newY][newX] == ']')
		{ // box move

			if (deltaX != 0)
			{
				// handle x seperately
				int freeX = robotX + deltaX;
				int freeY = robotY;

				while (freeX >= 0 && freeX < lines[0].size() && freeY >= 0 && freeY < lines.size() && (lines[freeY][freeX] == '[' || lines[freeY][freeX] == ']'))
				{
					if (lines[freeY][freeX] == '#' || lines[freeY][freeX] == '.')
						break;
					freeX += deltaX;
				}

				if (lines[freeY][freeX] == '#')
					continue;
				// loop back, moving boxes
				while (freeX != robotX)
				{
					lines[freeY][freeX] = lines[freeY][freeX - deltaX];
					lines[freeY][freeX - deltaX] = '.';
					freeX -= deltaX;
				}
				robotY = newY;
				robotX = newX;
				continue;
			}

			if (lines[newY][newX] == '[')
			{
				if (!pushBox(lines, newX, newY, deltaX, deltaY, false))
				{
					continue;
				}
				pushBox(lines, newX, newY, deltaX, deltaY, true);
			}
			if (lines[newY][newX] == ']')
			{
				if (!pushBox(lines, newX - 1, newY, deltaX, deltaY, false))
				{
					continue;
				}
				pushBox(lines, newX - 1, newY, deltaX, deltaY, true);
			}

			lines[newY][newX] = '@';
			lines[robotY][robotX] = '.';
			robotX = newX;
			robotY = newY;
		}
	}

	int sum = 0;
	for (int y = 0; y < lines.size(); y++)
	{
		for (int x = 0; x < lines[y].size(); x++)
		{
			if (lines[y][x] == '[')
			{
				sum += 100 * y + x;
			}
		}
	}
	std::cout << sum << std::endl;
}
