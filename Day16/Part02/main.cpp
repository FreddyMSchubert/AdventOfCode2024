#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <regex>
#include <exception>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <climits>
#include <unordered_map>
#include <map>
#include <queue>

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

struct pair_hash {
	std::size_t operator()(const std::pair<int, int>& p) const {
		return std::hash<int>()(p.first) ^ (std::hash<int>()(p.second) << 1);
	}
};

typedef struct s_reindeer reindeer;
typedef struct s_reindeer
{
	pos position;
	Direction direction;
	int score;

	std::string getKey() const {
		return std::to_string(position.x) + "," + std::to_string(position.y) + "," + std::to_string(direction);
	}

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

	std::priority_queue<reindeer, std::vector<reindeer>, CompareReindeer> q;

	std::unordered_map<std::string, int> minimalScores; // lowest score to reach each unique state
	std::unordered_map<std::string, std::vector<std::string>> predecessors; // predecessors of each unique state

	reindeer startReindeer;
	startReindeer.position = start;
	startReindeer.direction = EAST;
	startReindeer.score = 0;
	q.push(startReindeer);

	while (!q.empty())
	{
		reindeer current = q.top();
		q.pop();

		std::string currKey = current.getKey();
		if (minimalScores.find(currKey) != minimalScores.end()) {
			if (current.score > minimalScores[currKey]) {
				continue; // Current path is worse; skip it.
			}
		} else {
			// First time reaching this state; set its minimal score
			minimalScores[currKey] = current.score;
		}

		if (current.position.x == end.x && current.position.y == end.y)
		{
			std::cout << "Found end with score: " << current.score << std::endl;
		}

		// move forward
		int new_x = current.position.x + directions[current.direction].x;
		int new_y = current.position.y + directions[current.direction].y;
		if (new_x >= 0 && new_x < lines[0].size() && new_y >= 0 && new_y < lines.size() && lines[new_y][new_x] != '#')
		{
			reindeer next = current;
			next.position.x = new_x;
			next.position.y = new_y;
			next.score++;

			std::string nextKey = next.getKey();
			if (minimalScores.find(nextKey) == minimalScores.end() || minimalScores[nextKey] > next.score)
			{
				q.push(next);
				minimalScores[nextKey] = next.score;
				predecessors[nextKey].clear();
				predecessors[nextKey].push_back(currKey);
			}
			else if (minimalScores[nextKey] == next.score)
			{
				q.push(next);
				predecessors[nextKey].push_back(currKey);
			}
		}

		if (current.position.y == 7 && current.position.x == 15)
		{
			std::cout << "Debug with " << current.score << std::endl;
		}

		// rotate left
		reindeer next = current;
		next.direction = (Direction)((current.direction + 3) % 4);
		next.score += 1000;
		std::string nextKey = next.getKey();
		if (minimalScores.find(nextKey) == minimalScores.end() || next.score < minimalScores[nextKey])
		{
			q.push(next);
			minimalScores[nextKey] = next.score;
			predecessors[nextKey].clear();
			predecessors[nextKey] = { currKey };
		}
		else if (next.score == minimalScores[nextKey])
		{
			q.push(next);
			predecessors[nextKey].push_back(currKey);
		}

		// rotate right
		next = current;
		next.direction = (Direction)((current.direction + 1) % 4);
		next.score += 1000;
		nextKey = next.getKey();
		if (minimalScores.find(nextKey) == minimalScores.end() || next.score < minimalScores[nextKey])
		{
			q.push(next);
			minimalScores[nextKey] = next.score;
			predecessors[nextKey].clear();
			predecessors[nextKey] = { currKey };
		}
		else if (next.score == minimalScores[nextKey])
		{
			q.push(next);
			predecessors[nextKey].push_back(currKey);
		}
	}

	std::vector<std::string> endStates;
	int minimalEndScore = INT_MAX;

	for (const auto& [key, score] : minimalScores)
	{
		int x, y, dir;
		sscanf(key.c_str(), "%d,%d,%d", &x, &y, &dir);
		if (x == end.x && y == end.y && score < minimalEndScore)
			minimalEndScore = score;
	}
	for (const auto& [key, score] : minimalScores)
	{
		int x, y, dir;
		sscanf(key.c_str(), "%d,%d,%d", &x, &y, &dir);
		if (x == end.x && y == end.y && score == minimalEndScore)
			endStates.push_back(key);
	}
	for (const auto& [key, score] : minimalScores)
	{
		int x, y, dir;
		sscanf(key.c_str(), "%d,%d,%d", &x, &y, &dir);
		if (x == end.x && y == end.y)
			std::cout << " I reached the end! " << key << " with score " << score << std::endl;
	}

	std::unordered_set<std::string> pathStates;

	std::queue<std::string> traverseQueue;
	std::cout << endStates.size() << " end states found." << std::endl;
	for (const auto& endKey : endStates)
		traverseQueue.push(endKey);

	while (!traverseQueue.empty())
	{
		std::string key = traverseQueue.front();
		traverseQueue.pop();

		if (pathStates.find(key) != pathStates.end())
			continue;

		pathStates.insert(key);

		if (predecessors.find(key) != predecessors.end())
		{
			for (const auto& predKey : predecessors[key])
			{
				traverseQueue.push(predKey);
			}
		}
	}

	std::unordered_set<std::pair<int, int>, pair_hash> uniquePathPositions;
	for (const auto& key : pathStates)
	{
		int x, y, dir;
		if (sscanf(key.c_str(), "%d,%d,%d", &x, &y, &dir) != 3) {
			continue;
		}
		uniquePathPositions.emplace(std::make_pair(x, y));
	}

	std::vector<std::string> markedMap = lines;
	for (const auto& p : uniquePathPositions)
	{
		int x = p.first;
		int y = p.second;
		if (lines[y][x] != 'S' && lines[y][x] != 'E')
			markedMap[y][x] = 'O';
	}
	markedMap[start.y][start.x] = 'O';
	markedMap[end.y][end.x] = 'O';

	// Print
	for (const auto& l : markedMap)
	{
		std::cout << l << std::endl;
	}

	int count = 0;
	for (const auto& l : markedMap)
	{
		count += std::count(l.begin(), l.end(), 'O');
	}

	std::cout << "Number of tiles on at least one optimal path: " << count << std::endl;

	return 0;
}
