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

	std::vector<std::vector<bool>> visited(lines.size(), std::vector<bool>(lines[0].size(), false));
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
				visited[y][x] = true;

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

	while (true)
	{
		if (direction == 0)
		{
			if (y - 1 <= 0)
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
				visited[y][x] = true;
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
				visited[y][x] = true;
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
				visited[y][x] = true;
			}
		}
		else if (direction == 3)
		{
			if (x - 1 <= 0)
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
				visited[y][x] = true;
			}
		}
	}

	int count = 0;
	for (int py = 0; py < visited.size(); py++)
	{
		for (int px = 0; px < visited[py].size(); px++)
		{
			if (visited[py][px])
			{
				count++;
			}
		}
	}

	std::cout << count << std::endl;
}
