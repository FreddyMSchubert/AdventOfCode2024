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
	int x;
	int y;
};
struct ClawMachine
{
	Button buttonA;
	Button buttonB;
	Prize prize;
};

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
	int px = 0;
	int py = 0;
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
			px = std::stoi(match[1]);
			py = std::stoi(match[2]);
		}
		else if (i % 4 == 3 || i == lines.size() - 1)
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

	int minTokens = 0;

	for (auto clawMachine : clawMachines)
	{
		int maxPresses = 100;

		int localMinTokens = 999; // could never be higher than 300

		std::cout << "Claw Machine A: " << clawMachine.buttonA.x_move << " " << clawMachine.buttonA.y_move << " " << clawMachine.buttonA.cost << std::endl;
		std::cout << "Claw Machine B: " << clawMachine.buttonB.x_move << " " << clawMachine.buttonB.y_move << " " << clawMachine.buttonB.cost << std::endl;
		std::cout << "Prize: " << clawMachine.prize.x << " " << clawMachine.prize.y << std::endl;
		std::cout << "---" << std::endl;

		for (int a = 0; a <= maxPresses; a++)
		{
			for (int b = 0; b <= maxPresses; b++)
			{
				if (a * clawMachine.buttonA.x_move + b * clawMachine.buttonB.x_move == clawMachine.prize.x &&
					a * clawMachine.buttonA.y_move + b * clawMachine.buttonB.y_move == clawMachine.prize.y)
				{
					localMinTokens = std::min(localMinTokens, a * clawMachine.buttonA.cost + b * clawMachine.buttonB.cost);
				}
			}
		}

		if (localMinTokens != 999)
			minTokens += localMinTokens;
	}

	std::cout << "The fewest tokens you would have to spend to win all possible prizes is: " << minTokens << std::endl;
}
