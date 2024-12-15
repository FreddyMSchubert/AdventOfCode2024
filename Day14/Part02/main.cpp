#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <regex>
#include <exception>
#include <vector>
#include <algorithm>

struct Robot {
	int x;
	int y;
	int vx;
	int vy;
};

bool parse_robot_line(const std::string& line, Robot& robot)
{
	std::regex rgx(R"(p=(-?\d+),(-?\d+)\s+v=(-?\d+),(-?\d+))");
	std::smatch matches;

	if (std::regex_match(line, matches, rgx)) {
		try {
			robot.x = std::stoi(matches[1].str());
			robot.y = std::stoi(matches[2].str());
			robot.vx = std::stoi(matches[3].str());
			robot.vy = std::stoi(matches[4].str());
			return true;
		}
		catch (const std::exception& e) {
			std::cerr << "Error converting string to integer in line: " << line << std::endl;
			return false;
		}
	}
	else {
		std::cerr << "Line does not match expected format: " << line << std::endl;
		return false;
	}
}

bool isChristmasTree(std::vector<std::vector<char>> input)
{
	int size = 5;
	// Check if there is a sizexsize area with all robots clumped together

	for (size_t y = 0; y < input.size(); y++)
	{
		for (size_t x = 0; x < input[0].size(); x++)
		{
			if (x + size >= input[0].size() || y + size >= input.size())
				continue;

			bool isTree = true;
			for (int i = 0; i < size; i++)
			{
				for (int j = 0; j < size; j++)
				{
					if (input[y + i][x + j] != '#')
					{
						isTree = false;
						break;
					}
				}
				if (!isTree)
					break;
			}
			if (isTree)
				return true;
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
	std::vector<Robot> robots;
	while (std::getline(input, line))
	{
		lines.push_back(line);
		Robot robot;
		if (parse_robot_line(line, robot))
			robots.push_back(robot);
	}

	int gridSizeY = 103;
	int gridSizeX = 101;

	// Simulate robot mischief for 100 turns
	int i = 0;
	std::vector<std::vector<char>> grid(gridSizeY, std::vector<char>(gridSizeX, '.'));
	while (!isChristmasTree(grid))
	{
		std::cout << "-------\nSecond " << i << std::endl;
		for (auto& robot : robots)
		{
			int newX = robot.x + robot.vx;
			int newY = robot.y + robot.vy;

			while (newX < 0)
				newX += gridSizeX;
			while (newX >= gridSizeX)
				newX -= gridSizeX;
			while (newY < 0)
				newY += gridSizeY;
			while (newY >= gridSizeY)
				newY -= gridSizeY;
			
			robot.x = newX;
			robot.y = newY;
		}

		// Print grid
		for (int y = 0; y < gridSizeY; y++)
			for (int x = 0; x < gridSizeX; x++)
				grid[y][x] = '.';
		for (auto& robot : robots)
			grid[robot.y][robot.x] = '#';
		std::cout << "\033[2J\033[1;1H" << std::endl;
		std::cout << "-------\nSecond " << i << std::endl;
		for (int y = 0; y < gridSizeY; y++)
		{
			for (int x = 0; x < gridSizeX; x++)
				std::cout << grid[y][x];
			std::cout << std::endl;
		}
		i++;
	}

	// Count robots in each quadrant
	std::vector<int> quadrants(4, 0);
	for (auto& robot : robots)
	{
		if (robot.x == gridSizeX / 2 || robot.y == gridSizeY / 2)
			continue;
		if (robot.x < gridSizeX / 2 && robot.y < gridSizeY / 2)
			quadrants[0]++;
		else if (robot.x >= gridSizeX / 2 && robot.y < gridSizeY / 2)
			quadrants[1]++;
		else if (robot.x < gridSizeX / 2 && robot.y >= gridSizeY / 2)
			quadrants[2]++;
		else if (robot.x >= gridSizeX / 2 && robot.y >= gridSizeY / 2)
			quadrants[3]++;
	}

	int safetyFactor = 1;
	for (auto& q : quadrants)
		safetyFactor *= q;
	
	std::cout << "Safety factor: " << safetyFactor << std::endl;
}
