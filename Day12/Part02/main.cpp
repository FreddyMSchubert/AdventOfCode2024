#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <regex>
#include <exception>
#include <vector>
#include <algorithm>

typedef struct s_fence_direction {
	int coord;
	bool vertical;
	int boundary1;
	int boundary2;
	int direction;
}	fence_direction;

// over load == fence
bool operator==(const fence_direction &lhs, const fence_direction &rhs)
{
	return lhs.coord == rhs.coord && lhs.vertical == rhs.vertical && lhs.boundary1 == rhs.boundary1 && lhs.boundary2 == rhs.boundary2 && lhs.direction == rhs.direction;
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

	int total_price = 0;

	// loop through, identify regions. mark visited regions as done
	std::vector<std::vector<bool>> visited(lines.size(), std::vector<bool>(lines[0].size(), false));
	for (int i = 0; i < (int)lines.size(); i++)
	{
		for (int j = 0; j < (int)lines[i].size(); j++)
		{
			if (visited[i][j])
			{
				continue;
			}

			std::set<std::pair<int, int>> region;
			std::vector<std::pair<int, int>> stack; // stack of coordinates to visit
			stack.push_back({i, j});
			while (!stack.empty())
			{
				auto [x, y] = stack.back();
				stack.pop_back();
				if (x < 0 || x >= (int)lines.size() || y < 0 || y >= (int)lines[x].size() || visited[x][y] || lines[x][y] != lines[i][j])
				{
					continue;
				}
				visited[x][y] = true;
				region.insert({x, y});
				stack.push_back({x + 1, y});
				stack.push_back({x - 1, y});
				stack.push_back({x, y + 1});
				stack.push_back({x, y - 1});
			}

			std::vector<std::pair<int, int>> side_tiles;
			std::vector<fence_direction> directions;
			for (auto [x, y] : region)
			{
				if (lines[x - 1][y] != lines[i][j])
				{
					int boundary1 = y;
					int boundary2 = y;
					while (boundary1 >= 0 && lines[x][boundary1] != lines[x - 1][boundary1] && lines[x][boundary1] == lines[x][y])
					{
						boundary1--;
					}
					while (boundary2 <= (int)lines[x].size() && lines[x][boundary2] != lines[x - 1][boundary2] && lines[x][boundary2] == lines[x][y])
					{
						boundary2++;
					}
					fence_direction dir = {x - 1, true, boundary1, boundary2, -1};
					if (std::find(directions.begin(), directions.end(), dir) == directions.end())
					{
						directions.push_back(dir);
						std::cout << lines[i][j] << " - Detected a vertical boundary at " << x - 1 << "|" << y << " between " << boundary1 << " and " << boundary2 << std::endl;
					}
				}
				if (lines[x + 1][y] != lines[i][j])
				{
					int boundary1 = y;
					int boundary2 = y;
					while (boundary1 >= 0 && lines[x][boundary1] != lines[x + 1][boundary1] && lines[x][boundary1] == lines[x][y])
					{
						boundary1--;
					}
					while (boundary2 <= (int)lines[x].size() && lines[x][boundary2] != lines[x + 1][boundary2] && lines[x][boundary2] == lines[x][y])
					{
						boundary2++;
					}
					fence_direction dir = {x + 1, true, boundary1, boundary2, 1};
					if (std::find(directions.begin(), directions.end(), dir) == directions.end())
					{
						directions.push_back(dir);
						std::cout << lines[i][j] << " - Detected a vertical boundary at " << x + 1 << "|" << y << " between " << boundary1 << " and " << boundary2 << std::endl;
					}
				}
				if (lines[x][y - 1] != lines[i][j])
				{
					int boundary1 = x;
					int boundary2 = x;
					while (boundary1 >= 0 && lines[boundary1][y] != lines[boundary1][y - 1] && lines[boundary1][y] == lines[x][y])
					{
						boundary1--;
					}
					while (boundary2 <= (int)lines.size() && lines[boundary2][y] != lines[boundary2][y - 1] && lines[boundary2][y] == lines[x][y])
					{
						boundary2++;
					}
					fence_direction dir = {y - 1, false, boundary1, boundary2, -1};
					if (std::find(directions.begin(), directions.end(), dir) == directions.end())
					{
						directions.push_back(dir);
						std::cout << lines[i][j] << " - Detected a horizontal boundary at " << x << "|" << y - 1 << " between " << boundary1 << " and " << boundary2 << std::endl;
					}
				}
				if (lines[x][y + 1] != lines[i][j])
				{
					int boundary1 = x;
					int boundary2 = x;
					while (boundary1 >= 0 && lines[boundary1][y] != lines[boundary1][y + 1] && lines[boundary1][y] == lines[x][y])
					{
						boundary1--;
					}
					while (boundary2 <= (int)lines.size() && lines[boundary2][y] != lines[boundary2][y + 1] && lines[boundary2][y] == lines[x][y])
					{
						boundary2++;
					}
					fence_direction dir = {y + 1, false, boundary1, boundary2, 1};
					if (std::find(directions.begin(), directions.end(), dir) == directions.end())
					{
						directions.push_back(dir);
						std::cout << lines[i][j] << " - Detected a horizontal boundary at " << x << "|" << y + 1 << " between " << boundary1 << " and " << boundary2 << std::endl;
					}
				}
			}

			int area = region.size();
			int perimeter = directions.size();
			total_price += area * perimeter;
			std::cout << "Region " << lines[i][j] << " has price " << area << " * " << perimeter << " = " << area * perimeter << std::endl;
		}
	}

	std::cout << "Total price: " << total_price << std::endl;
}
