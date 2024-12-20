#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <regex>
#include <exception>
#include <vector>
#include <algorithm>

struct Pos {
	int x;
	int y;
};

int taxicabDistance(int x1, int y1, int x2, int y2) // minecraft go wheeeee
{
	return std::abs(x1 - x2) + std::abs(y1 - y2);
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
		std::cout << line << std::endl;
	}

	int width = lines[0].size();
	int height = lines.size();

	Pos start{-1, -1};
	Pos end{-1, -1};

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (lines[i][j] == 'S')
			{
				start.x = j;
				start.y = i;
			}
			else if (lines[i][j] == 'E')
			{
				end.x = j;
				end.y = i;
			}
		}
	}

	int dx[] = {0, 0, 1, -1};
	int dy[] = {1, -1, 0, 0};

	auto inBounds = [&](int x, int y) {
		return x >= 0 && x < width && y >= 0 && y < height;
	};

	// bfs to find shortest normal path
	std::vector<std::vector<int>> dist(height, std::vector<int>(width, -1));
	dist[start.y][start.x] = 0;
	{
		std::queue<Pos> q;
		q.push(start);
		while (!q.empty())
		{
			auto cur = q.front();
			q.pop();
			for (int i = 0; i < 4; i++)
			{
				int ny=cur.y+dy[i], nx=cur.x+dx[i];
				if (inBounds(nx, ny) && lines[ny][nx] != '#' && dist[ny][nx] == -1)
				{
					dist[ny][nx] = dist[cur.y][cur.x] + 1;
					q.push({nx, ny});
				}
			}
		}
	}
	int normalDist = dist[end.y][end.x];

	std::vector<std::vector<int>> dist2end(height, std::vector<int>(width, -1));
	dist2end[end.y][end.x] = 0;
	{
		std::queue<Pos> q;
		q.push(end);
		while (!q.empty())
		{
			auto cur = q.front();
			q.pop();
			for (int i = 0; i < 4; i++)
			{
				int ny=cur.y+dy[i], nx=cur.x+dx[i];
				if (inBounds(nx, ny) && lines[ny][nx] != '#' && dist2end[ny][nx] == -1)
				{
					dist2end[ny][nx] = dist2end[cur.y][cur.x] + 1;
					q.push({nx, ny});
				}
			}
		}
	}

	struct CheatID {
		Pos start;
		Pos end;
		bool operator<(const CheatID &other) const
		{
			if (start.x != other.start.x)
				return start.x < other.start.x;
			if (start.y != other.start.y)
				return start.y < other.start.y;
			if (end.x != other.end.x)
				return end.x < other.end.x;
			return end.y < other.end.y;
		}
	};

	std::set<CheatID> cheats;
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			if (lines[y][x] == '#' || dist[y][x] == -1)
				continue;
			// loop through a 20 x 20 square around the current position
			// if its valid, add it to the set
			// must be less than 100 picoseconds
			for (int i = -20; i <= 20; i++)
			{
				for (int j = -20; j <= 20; j++)
				{
					if (i == 0 && j == 0)
						continue;
					int nx = x + j;
					int ny = y + i;
					if (!inBounds(nx, ny) || lines[ny][nx] == '#' || dist2end[ny][nx] == -1 || taxicabDistance(x, y, nx, ny) > 20)
						continue;
					int stepsTaken = std::abs(i) + std::abs(j);
					int cheatedTime = dist[y][x] + dist2end[ny][nx] + stepsTaken;
					int savedTime = normalDist - cheatedTime;
					if (savedTime >= 100)
					{
						CheatID id;
						id = {{x, y}, {nx, ny}};
						if (cheats.find(id) == cheats.end())
						{
							cheats.insert(id);
						}
					}
				}
			}
		}
	}

	// for (auto &cheat : cheats)
	// 	std::cout << "Start: " << cheat.start.x << ", " << cheat.start.y << " End: " << cheat.end.x << ", " << cheat.end.y << std::endl;
	std::cout << cheats.size() << std::endl;
}
