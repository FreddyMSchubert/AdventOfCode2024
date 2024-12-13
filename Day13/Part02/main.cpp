#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <regex>
#include <exception>
#include <vector>
#include <algorithm>

struct Button
{
	int x_move;
	int y_move;
	int cost;
};
struct Prize
{
	int64_t x;
	int64_t y;
};
struct ClawMachine
{
	Button buttonA;
	Button buttonB;
	Prize prize;
};

int64_t findMinimalCost(const ClawMachine& machine)
{
	int ax = machine.buttonA.x_move;
	int ay = machine.buttonA.y_move;
	int bx = machine.buttonB.x_move;
	int by = machine.buttonB.y_move;
	int64_t px = machine.prize.x;
	int64_t py = machine.prize.y;
	
	int64_t a = (px * by - py * bx) / (ax * by - ay * bx);
	int64_t b = (px * ay - py * ax) / (bx * ay - by * ax);
	if (a * ax + b * bx == px && a * ay + b * by == py)
		return a * machine.buttonA.cost + b * machine.buttonB.cost;

	return -1;
}

int main()
{
	std::ifstream input;
	input.open("../input.txt");
	std::vector<std::string> lines;
	std::string line;
	std::vector<ClawMachine> clawMachines;
	int ax = 0;
	int ay = 0;
	int bx = 0;
	int by = 0;
	int64_t px = 0;
	int64_t py = 0;
	int i = 0;
	while (std::getline(input, line))
	{
		lines.push_back(line);
	}
	for (std::string & line : lines)
	{
		if (i % 4 == 0)
		{
			std::regex buttonA_regex("Button A: X\\+(\\d+), Y\\+(\\d+)");
			std::smatch match;

			std::regex_search(line, match, buttonA_regex);
			ax = std::stoi(match[1]);
			ay = std::stoi(match[2]);
		}
		else if (i % 4 == 1)
		{
			std::regex buttonB_regex("Button B: X\\+(\\d+), Y\\+(\\d+)");
			std::smatch match;

			std::regex_search(line, match, buttonB_regex);
			bx = std::stoi(match[1]);
			by = std::stoi(match[2]);
		}
		else if (i % 4 == 2)
		{
			std::regex prize_regex("Prize: X=(\\d+), Y=(\\d+)");
			std::smatch match;

			std::regex_search(line, match, prize_regex);
			px = std::stoll(match[1]) + 10000000000000;
			py = std::stoll(match[2]) + 10000000000000;
		}
		else if (i % 4 == 3 || i == (int)lines.size() - 1)
		{
			ClawMachine clawMachine;
			clawMachine.buttonA.x_move = ax;
			clawMachine.buttonA.y_move = ay;
			clawMachine.buttonA.cost = 3;
			clawMachine.buttonB.x_move = bx;
			clawMachine.buttonB.y_move = by;
			clawMachine.buttonB.cost = 1;
			clawMachine.prize.x = px;
			clawMachine.prize.y = py;
			clawMachines.push_back(clawMachine);
		}

		i++;
	}

	int64_t minTokens = 0;

	for (int i = 0; i < (int)clawMachines.size(); i++)
	{
		std::cout << "Processing claw machine " << i + 1 << std::endl;
		int64_t cost = findMinimalCost(clawMachines[i]);
		std::cout << "The fewest tokens you would have to spend to win the prize " << i + 1 << " is: " << cost << std::endl;
		if (cost == -1)
		{
			std::cout << "This claw machine is impossible to win." << std::endl;
			continue;
		}
		minTokens += cost;
	}

	std::cout << "The fewest tokens you would have to spend to win all possible prizes is: " << minTokens << std::endl;
}
