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
			for (int i = 0; i < 4; i++)
			{
				int x1=x+dx[i], y1=y+dy[i];
				if (!inBounds(x1, y1))
					continue;
				for (int j = 0; j < 4; j++)
				{
					int x2=x1+dx[j], y2=y1+dy[j];
					if (!inBounds(x2, y2) || lines[y2][x2] == '#' || dist2end[y2][x2] == -1)
						continue;
					int cheatedTime = dist[y][x] + dist2end[y2][x2] + 2;
					int savedTime = normalDist - cheatedTime;
					if (savedTime >= 2)
					{
						CheatID id;
						id.start.x = x;
						id.start.y = y;
						id.end.x = x2;
						id.end.y = y2;
						if (cheats.find(id) == cheats.end())
						{
							cheats.insert(id);
						}
					}
				}
			}
		}
	}


	std::cout << cheats.size() << std::endl;

	// log out all cheats
	for (auto &cheat : cheats)
	{
		std::cout << "Start: " << cheat.start.x << ", " << cheat.start.y << " End: " << cheat.end.x << ", " << cheat.end.y << std::endl;
	}
}
