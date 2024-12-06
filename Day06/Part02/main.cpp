#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <regex>
#include <exception>
#include <vector>

bool isPathInfinitelyRepeating(std::vector<std::string> lines, int direction, int x, int y)
{
	std::vector<std::vector<int>> visited(lines.size(), std::vector<int>(lines[0].size(), -1)); // save the int of the direction we were in when visiting to verify a loop, -1 = not visited

	while (true)
	{
		if (direction == 0)
		{
			if (y - 1 < 0)
			{
				break;
			}
			if (lines[y - 1][x] == '#')
			{
				direction = 1;
			}
			else
			{
				y--;
				if (visited[y][x] == direction)
				{
					return true;
				}
				visited[y][x] = direction;
			}
		}
		else if (direction == 1)
		{
			if (x + 1 >= lines[y].size())
			{
				break;
			}
			if (lines[y][x + 1] == '#')
			{
				direction = 2;
			}
			else
			{
				x++;
				if (visited[y][x] == direction)
				{
					return true;
				}
				visited[y][x] = direction;
			}
		}
		else if (direction == 2)
		{
			if (y + 1 >= lines.size())
			{
				break;
			}
			if (lines[y + 1][x] == '#')
			{
				direction = 3;
			}
			else
			{
				y++;
				if (visited[y][x] == direction)
				{
					return true;
				}
				visited[y][x] = direction;
			}
		}
		else if (direction == 3)
		{
			if (x - 1 < 0)
			{
				break;
			}
			if (lines[y][x - 1] == '#')
			{
				direction = 0;
			}
			else
			{
				x--;
				if (visited[y][x] == direction)
				{
					return true;
				}
				visited[y][x] = direction;
			}
		}
	}

	return false;
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

	int direction = -1; // 0 = up, 1 = right, 2 = down, 3 = left
	int x = -1;
	int y = -1;

	for (size_t py = 0; py < lines.size(); py++)
	{
		std::string l = lines[py];
		for (size_t px = 0; px < l.size(); px++)
		{
			if (lines[py][px] == '^' || lines[py][px] == 'v' || lines[py][px] == '<' || lines[py][px] == '>')
			{
				x = px;
				y = py;

				if (lines[py][px] == '^')
				{
					direction = 0;
				}
				else if (lines[py][px] == '>')
				{
					direction = 1;
				}
				else if (lines[py][px] == 'v')
				{
					direction = 2;
				}
				else if (lines[py][px] == '<')
				{
					direction = 3;
				}
			}
		}
	}

	int count = 0;

	for (int obstrX = 0; obstrX < lines[0].size(); obstrX++)
	{
		for (int obstrY = 0; obstrY < lines.size(); obstrY++)
		{
			if (lines[obstrY][obstrX] == '#')
			{
				continue;
			}

			if (obstrX == x && obstrY == y)
			{
				continue;
			}

			std::vector<std::string> newLines = lines;
			newLines[obstrY][obstrX] = '#';

			if (isPathInfinitelyRepeating(newLines, direction, x, y))
			{
				count++;
			}
		}
	}

	std::cout << count << std::endl;

	return 0;
}
