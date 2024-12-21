#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <regex>
#include <exception>
#include <vector>
#include <algorithm>
#include <map>
#include <functional>
#include <utility>

/*
--- Day 21: Keypad Conundrum ---
As you teleport onto Santa's Reindeer-class starship, The Historians begin to panic: someone from their search party is missing. A quick life-form scan by the ship's computer reveals that when the missing Historian teleported, he arrived in another part of the ship.

The door to that area is locked, but the computer can't open it; it can only be opened by physically typing the door codes (your puzzle input) on the numeric keypad on the door.

The numeric keypad has four rows of buttons: 789, 456, 123, and finally an empty gap followed by 0A. Visually, they are arranged like this:

+---+---+---+
| 7 | 8 | 9 |
+---+---+---+
| 4 | 5 | 6 |
+---+---+---+
| 1 | 2 | 3 |
+---+---+---+
	| 0 | A |
	+---+---+
Unfortunately, the area outside the door is currently depressurized and nobody can go near the door. A robot needs to be sent instead.

The robot has no problem navigating the ship and finding the numeric keypad, but it's not designed for button pushing: it can't be told to push a specific button directly. Instead, it has a robotic arm that can be controlled remotely via a directional keypad.

The directional keypad has two rows of buttons: a gap / ^ (up) / A (activate) on the first row and < (left) / v (down) / > (right) on the second row. Visually, they are arranged like this:

	+---+---+
	| ^ | A |
+---+---+---+
| < | v | > |
+---+---+---+
When the robot arrives at the numeric keypad, its robotic arm is pointed at the A button in the bottom right corner. After that, this directional keypad remote control must be used to maneuver the robotic arm: the up / down / left / right buttons cause it to move its arm one button in that direction, and the A button causes the robot to briefly move forward, pressing the button being aimed at by the robotic arm.

For example, to make the robot type 029A on the numeric keypad, one sequence of inputs on the directional keypad you could use is:

< to move the arm from A (its initial pos) to 0.
A to push the 0 button.
^A to move the arm to the 2 button and push it.
>^^A to move the arm to the 9 button and push it.
vvvA to move the arm to the A button and push it.
In total, there are three shortest possible sequences of button presses on this directional keypad that would cause the robot to type 029A: <A^A>^^AvvvA, <A^A^>^AvvvA, and <A^A^^>AvvvA.

Unfortunately, the area containing this directional keypad remote control is currently experiencing high levels of radiation and nobody can go near it. A robot needs to be sent instead.

When the robot arrives at the directional keypad, its robot arm is pointed at the A button in the upper right corner. After that, a second, different directional keypad remote control is used to control this robot (in the same way as the first robot, except that this one is typing on a directional keypad instead of a numeric keypad).

There are multiple shortest possible sequences of directional keypad button presses that would cause this robot to tell the first robot to type 029A on the door. One such sequence is v<<A>>^A<A>AvA<^AA>A<vAAA>^A.

Unfortunately, the area containing this second directional keypad remote control is currently -40 degrees! Another robot will need to be sent to type on that directional keypad, too.

There are many shortest possible sequences of directional keypad button presses that would cause this robot to tell the second robot to tell the first robot to eventually type 029A on the door. One such sequence is <vA<AA>>^AvAA<^A>A<v<A>>^AvA^A<vA>^A<v<A>^A>AAvA^A<v<A>A>^AAAvA<^A>A.

Unfortunately, the area containing this third directional keypad remote control is currently full of Historians, so no robots can find a clear path there. Instead, you will have to type this sequence yourself.

Were you to choose this sequence of button presses, here are all of the buttons that would be pressed on your directional keypad, the two robots' directional keypads, and the numeric keypad:

<vA<AA>>^AvAA<^A>A<v<A>>^AvA^A<vA>^A<v<A>^A>AAvA^A<v<A>A>^AAAvA<^A>A
v<<A>>^A<A>AvA<^AA>A<vAAA>^A
v<<A>>^A<A>AvA^<A<A>Av<Av<Av<A^>A
<A^A>^^AvvvA
029A
In summary, there are the following keypads:

One directional keypad that you are using.
Two directional keypads that robots are using.
One numeric keypad (on a door) that a robot is using.
It is important to remember that these robots are not designed for button pushing. In particular, if a robot arm is ever aimed at a gap where no button is present on the keypad, even for an instant, the robot will panic unrecoverably. So, don't do that. All robots will initially aim at the keypad's A key, wherever it is.

To unlock the door, five codes will need to be typed on its numeric keypad. For example:

029A
980A
179A
456A
379A
For each of these, here is a shortest sequence of button presses you could type to cause the desired code to be typed on the numeric keypad:

029A: <vA<AA>>^AvAA<^A>A<v<A>>^AvA^A<vA>^A<v<A>^A>AAvA^A<v<A>A>^AAAvA<^A>A
980A: <v<A>>^AAAvA^A<vA<AA>>^AvAA<^A>A<v<A>A>^AAAvA<^A>A<vA>^A<A>A
179A: <v<A>>^A<vA<A>>^AAvAA<^A>A<v<A>>^AAvA^A<vA>^AA<A>A<v<A>A>^AAAvA<^A>A
456A: <v<A>>^AA<vA<A>>^AAvAA<^A>A<vA>^A<A>A<vA>^A<A>A<v<A>A>^AAvA<^A>A
379A: <v<A>>^AvA^A<vA<AA>>^AAvA<^A>AAvA^A<vA>^AA<A>A<v<A>A>^AAAvA<^A>A
The Historians are getting nervous; the ship computer doesn't remember whether the missing Historian is trapped in the area containing a giant electromagnet or molten lava. You'll need to make sure that for each of the five codes, you find the shortest sequence of button presses necessary.

The complexity of a single code (like 029A) is equal to the result of multiplying these two values:

The length of the shortest sequence of button presses you need to type on your directional keypad in order to cause the code to be typed on the numeric keypad; for 029A, this would be 68.
The numeric part of the code (ignoring leading zeroes); for 029A, this would be 29.
In the above example, complexity of the five codes can be found by calculating 68 * 29, 60 * 980, 68 * 179, 64 * 456, and 64 * 379. Adding these together produces 126384.

Find the fewest number of button presses you'll need to perform in order to cause the robot in front of the door to type each code. What is the sum of the complexities of the five codes on your list?
*/

/*
std::vector<std::vector<char>> keypad1 = {
	{'7', '8', '9'},
	{'4', '5', '6'},
	{'1', '2', '3'},
	{' ', '0', 'A'}
};
std::vector<std::vector<char>> keypad2 = {
	{' ', '^', 'A'},
	{'<', 'v', '>'}
};

└[~/aoc/Day21/Part01]> make ren
rm -f christmasIsComing
clang++ main.cpp -o christmasIsComing -std=c++17 -fsanitize=address -g
./christmasIsComing
Next combo: 805A
<^^^AvvvA^^A>vvA
is valid: 1
v<<A>^AAA>Av<AAA>^A<AA>AvA<AA>^A
is valid: 1
v<A<AA>>^AvA<^A>AAAvA^Av<A<A>>^AAAvA<^A>Av<<A>>^AAvA^Av<A>^Av<<A>>^AAvA<^A>A
is valid: 1
shortestLen 76 * num 805 = result 61180
*/

typedef struct s_pos {
	int y;
	int x;

	bool operator<(const struct s_pos &other) const {
		if (x == other.x) {
			return y < other.y;
		}
		return x < other.x;
	}
	bool operator==(const struct s_pos &other) const {
		return y == other.y && x == other.x;
	}
} t_pos;

std::vector<char> getMovesTo(std::vector<std::vector<char>> keypad, char targetSpace, t_pos & pos, char prevDir, char nextDir)
{

	std::vector<char> returnVec = std::vector<char>();

	if (keypad[pos.y][pos.x] == targetSpace)
		return returnVec;

	int targetX = -1;
	int targetY = -1;
	for (int y = 0; y < keypad.size(); y++)
	{
		for (int x = 0; x < keypad[y].size(); x++)
		{
			if (keypad[y][x] == targetSpace)
			{
				targetX = x;
				targetY = y;
				break;
			}
		}
		if (targetX != -1)
			break;
	}

	// assume y dominance
	std::vector<char> movesYdom;
	struct s_pos tempPos = pos;
	bool ypassedoverEmpty = false;
	while (tempPos.y != targetY)
	{
		if (keypad[tempPos.y][tempPos.x] == 'x')
		{
			ypassedoverEmpty = true;
		}
		if (tempPos.y < targetY)
		{
			movesYdom.push_back('v');
			tempPos.y++;
		}
		else
		{
			movesYdom.push_back('^');
			tempPos.y--;
		}
	}
	while (tempPos.x != targetX)
	{
		if (keypad[tempPos.y][tempPos.x] == 'x')
		{
			ypassedoverEmpty = true;
		}
		if (tempPos.x < targetX)
		{
			movesYdom.push_back('>');
			tempPos.x++;
		}
		else
		{
			movesYdom.push_back('<');
			tempPos.x--;
		}
	}

	// assume x dominance
	std::vector<char> movesXdom;
	bool xpassedoverEmpty = false;
	tempPos = pos;
	while (tempPos.x != targetX)
	{
		if (keypad[tempPos.y][tempPos.x] == 'x')
		{
			xpassedoverEmpty = true;
		}
		if (tempPos.x < targetX)
		{
			movesXdom.push_back('>');
			tempPos.x++;
		}
		else
		{
			movesXdom.push_back('<');
			tempPos.x--;
		}
	}
	while (tempPos.y != targetY)
	{
		if (keypad[tempPos.y][tempPos.x] == 'x')
		{
			xpassedoverEmpty = true;
		}
		if (tempPos.y < targetY)
		{
			movesXdom.push_back('v');
			tempPos.y++;
		}
		else
		{
			movesXdom.push_back('^');
			tempPos.y--;
		}
	}

	char neededNextMoveX = movesXdom[0];
	char neededNextMoveY = movesYdom[0];
	t_pos neededNextMoveXPos;
	t_pos neededNextMoveYPos;
	for (int y = 0; y < keypad.size(); y++)
	{
		for (int x = 0; x < keypad[y].size(); x++)
		{
			if (keypad[y][x] == neededNextMoveX)
			{
				neededNextMoveXPos = { y, x };
			}
			if (keypad[y][x] == neededNextMoveY)
			{
				neededNextMoveYPos = { y, x };
			}
		}
	}

	int neededMovesToGetToNextMoveX = std::abs(neededNextMoveXPos.x - pos.x) + std::abs(neededNextMoveXPos.y - pos.y);
	int neededMovesToGetToNextMoveY = std::abs(neededNextMoveYPos.x - pos.x) + std::abs(neededNextMoveYPos.y - pos.y);

	bool x = false;

	if (ypassedoverEmpty)
	{
		if (!xpassedoverEmpty)
			x = true;
		else
			throw std::runtime_error("Both passed over empty");
	}
	else
	{
		if (xpassedoverEmpty)
			x = false;
		else
		{
			if (neededMovesToGetToNextMoveX != neededMovesToGetToNextMoveY)
				x = (neededMovesToGetToNextMoveY < neededMovesToGetToNextMoveX) ? false : true;
			else if (movesXdom[0] == prevDir)
				x = true;
			else if (movesYdom[0] == prevDir)
				x = false;
			else if (nextDir != '-')
			{
				std::vector<char> nextMove = getMovesTo(keypad, nextDir, pos, prevDir, '-');
				char nextMoveStart = nextMove.size() > 0 ? nextMove[0] : '-';
				if (nextMoveStart == '^' || nextMoveStart == 'v')
					x = false;
				else
					x = true;
			}
			else
				x = true;

			if (x == true && xpassedoverEmpty)
				x = false;
			else if (x == false && ypassedoverEmpty)
				x = true;
		}
	}

	if (!x)
	{
		while (pos.y != targetY)
		{
			if (pos.y < targetY)
				pos.y++;
			else
				pos.y--;
		}
		while (pos.x != targetX)
		{
			if (pos.x < targetX)
				pos.x++;
			else
				pos.x--;
		}
		returnVec = movesYdom;
	}
	else
	{
		while (pos.x != targetX)
		{
			if (pos.x < targetX)
				pos.x++;
			else
				pos.x--;
		}
		while (pos.y != targetY)
		{
			if (pos.y < targetY)
				pos.y++;
			else
				pos.y--;
		}
		returnVec = movesXdom;
	}

	return returnVec;
}

bool	isPossible(std::vector<char> & moves, std::vector<std::vector<char>> keypad, t_pos pos)
{
	for (char c : moves)
	{
		if (c == '^')
		{
			if (pos.y == 0)
				return false;
			if (keypad[pos.y - 1][pos.x] == 'x')
				return false;
			pos.y--;
		}
		else if (c == 'v')
		{
			if (pos.y == keypad.size() - 1)
				return false;
			if (keypad[pos.y + 1][pos.x] == 'x')
				return false;
			pos.y++;
		}
		else if (c == '<')
		{
			if (pos.x == 0)
				return false;
			if (keypad[pos.y][pos.x - 1] == 'x')
				return false;
			pos.x--;
		}
		else if (c == '>')
		{
			if (pos.x == keypad[0].size() - 1)
				return false;
			if (keypad[pos.y][pos.x + 1] == 'x')
				return false;
			pos.x++;
		}
		else if (c == 'A')
		{
			if (keypad[pos.y][pos.x] == 'x')
				return false;
		}
	}
	return true;
}

int main()
{
	const t_pos numRobotStart = { 3, 2 };
	const t_pos dirRobotStart = { 0, 2 };

	t_pos numRobot = numRobotStart;

	int results = 0;

	std::vector<std::vector<char>> keypad1 = {
		{'7', '8', '9'},
		{'4', '5', '6'},
		{'1', '2', '3'},
		{'x', '0', 'A'}
	};
	std::vector<std::vector<char>> keypad2 = {
		{'x', '^', 'A'},
		{'<', 'v', '>'}
	};

	std::ifstream input;
	input.open("../input.txt");
	std::vector<std::string> lines;
	std::string line;
	while (std::getline(input, line))
	{
		lines.push_back(line);
		std::cout << "Next combo: " << line << std::endl;

		std::vector<char> moves;
		std::vector<char> moves2;

		for (char c : line)
			moves.push_back(c);

		for (char c : moves)
			std::cout << c;
		std::cout << std::endl;

		for (int k = 0; k < 3; k++)
		{
			t_pos robotPos = dirRobotStart;
			for (int j = 0; j < moves.size(); j++)
			{
				char c = moves[j];
				std::vector<std::vector<char>> keypad = k == 0 ? keypad1 : keypad2;
				if (keypad[robotPos.y][robotPos.x] == c)
				{
					moves2.push_back('A');
					continue;
				}

				char nextDir;
				if (j != moves.size() - 1)
					nextDir = moves[j + 1];
				else
					nextDir = '-';
				char prevDir;
				if (j != 0)
					prevDir = moves[j - 1];
				else
					prevDir = '-';
				moves2 = getMovesTo(keypad, c, robotPos, prevDir, nextDir);
				moves2.push_back('A');
			}

			moves.clear();
			moves = moves2;

			for (char c : moves)
				std::cout << c;
			std::cout << std::endl;
		}

		// calc result
		int num = std::stoi(line.substr(0, line.size() - 1), nullptr, 10);
		int shortestLen = moves.size();

		std::cout << " shortestLen " << shortestLen << " * num " << num << " = result " << shortestLen * num << std::endl;

		results += shortestLen * num;

		std::cout << "---------------------------------" << std::endl;
	}

	std::cout << "Results: " << results << std::endl;
}
