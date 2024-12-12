#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <regex>
#include <exception>
#include <vector>
#include <algorithm>

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
	for (int i = 0; i < lines.size(); i++)
	{
		for (int j = 0; j < lines[i].size(); j++)
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
				if (x < 0 || x >= lines.size() || y < 0 || y >= lines[x].size() || visited[x][y] || lines[x][y] != lines[i][j])
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

			int area = region.size();
			int perimeter = 0;
			for (auto [x, y] : region)
			{
				if (x == 0 || lines[x - 1][y] != lines[x][y])
					perimeter++;
				if (x == (int)lines.size() - 1 || lines[x + 1][y] != lines[x][y])
					perimeter++;
				if (y == 0 || lines[x][y - 1] != lines[x][y])
					perimeter++;
				if (y == (int)lines[x].size() - 1 || lines[x][y + 1] != lines[x][y])
					perimeter++;
			}
			total_price += area * perimeter;
			std::cout << "Region " << lines[i][j] << " has price " << area << " * " << perimeter << " = " << area * perimeter << std::endl;
		}
	}

	std::cout << "Total price: " << total_price << std::endl;
}
