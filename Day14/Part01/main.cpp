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
	for (int i = 0; i < 100; i++)
	{
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
	{
		std::cout << q << " ";
		safetyFactor *= q;
	}
	
	std::cout << "Safety factor: " << safetyFactor << std::endl;
}
