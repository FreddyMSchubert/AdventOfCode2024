#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <regex>
#include <exception>
#include <vector>
#include <algorithm>
#include <queue>
#define GRID_SIZE 71

bool isGoalStillReachable(std::vector<std::string> map)
{
	std::pair<int, int> start = {0, 0};
	std::pair<int, int> goal = {GRID_SIZE - 1, GRID_SIZE - 1};
	std::vector<std::pair<int, int>> directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

	std::queue<std::pair<std::pair<int, int>, int>> q; // ((x, y), steps)
	std::set<std::pair<int, int>> visited;

	q.push({start, 0});
	visited.insert(start);

	while (!q.empty())
	{
		auto [pos, steps] = q.front();
		q.pop();

		if (pos == goal)
		{
			return true;
		}

		for (const auto & [dx, dy] : directions)
		{
			int nx = pos.first + dx;
			int ny = pos.second + dy;

			if (nx >= 0 && nx < GRID_SIZE && ny >= 0 && ny < GRID_SIZE && map[ny][nx] == '.' && !visited.count({nx, ny}))
			{
				visited.insert({nx, ny});
				q.push({{nx, ny}, steps + 1});
			}
		}
	}

	return false;
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
	int parsingLine = 0;
	std::vector<std::string> map(71, std::string(71, '.'));
	while (isGoalStillReachable(map))
	{
		std::string line = lines[parsingLine];
		std::regex re("([0-9]+),([0-9]+)");
		std::smatch match;
		std::regex_search(line, match, re);
		int x = std::stoi(match[1]);
		int y = std::stoi(match[2]);
		map[y][x] = '#';
		parsingLine++;
	}

	std::cout << parsingLine << ": " << lines[parsingLine] << std::endl;

	return 0;
}
