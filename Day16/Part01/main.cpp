#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <regex>
#include <exception>
#include <vector>
#include <algorithm>

typedef struct s_pos
{
	int x;
	int y;
} pos;

enum Direction {
	NORTH,
	EAST,
	SOUTH,
	WEST
};

typedef struct s_reindeer reindeer;
typedef struct s_reindeer
{
	pos position;
	Direction direction;
	int score;

	bool operator==(const reindeer& other) const
	{
		return position.x == other.position.x &&
			position.y == other.position.y &&
			direction == other.direction;
	}
} reindeer;
struct CompareReindeer {
	bool operator()(const reindeer& a, const reindeer& b) const {
		return a.score > b.score; // Lower score has higher priority
	}
};


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

	pos start;
	pos end;
	for (int y = 0; y < lines.size(); y++)
	{
		for (int x = 0; x < lines[y].size(); x++)
		{
			if (lines[y][x] == 'S')
			{
				start.x = x;
				start.y = y;
			}
			if (lines[y][x] == 'E')
			{
				end.x = x;
				end.y = y;
			}
		}
	}

	std::vector<pos> directions = {
		{0, -1}, // NORTH
		{1, 0},  // EAST
		{0, 1},  // SOUTH
		{-1, 0}  // WEST
	};

	std::vector<reindeer> visited;

	std::priority_queue<reindeer, std::vector<reindeer>, CompareReindeer> q;

	reindeer startReindeer;
	startReindeer.position = start;
	startReindeer.direction = EAST;
	startReindeer.score = 0;
	q.push(startReindeer);

	while (!q.empty())
	{
		reindeer current = q.top();
		q.pop();

		if (current.position.x == end.x && current.position.y == end.y)
		{
			std::cout << "Lowest score: " << current.score << std::endl;
			break;
		}

		if (std::find(visited.begin(), visited.end(), current) != visited.end())
		{
			continue;
		}
		visited.push_back(current);

		// move forward
		int new_x = current.position.x + directions[current.direction].x;
		int new_y = current.position.y + directions[current.direction].y;
		if (new_x >= 0 && new_x < lines[0].size() && new_y >= 0 && new_y < lines.size() && lines[new_y][new_x] != '#')
		{
			reindeer next = current;
			next.position.x = new_x;
			next.position.y = new_y;
			next.score++;
			q.push(next);
		}

		// rotate left
		reindeer next = current;
		next.direction = (Direction)((current.direction + 3) % 4);
		next.score += 1000;
		q.push(next);

		// rotate right
		next = current;
		next.direction = (Direction)((current.direction + 1) % 4);
		next.score += 1000;
		q.push(next);
	}

	return 0;
}
