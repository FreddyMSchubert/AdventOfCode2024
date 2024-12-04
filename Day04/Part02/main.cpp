#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <regex>
#include <exception>
#include <vector>

typedef struct cross
{
	char top_left;
	char top_right;
	char center;
	char bottom_left;
	char bottom_right;

	bool operator==(const cross& other) const {
	return top_left == other.top_left &&
			top_right == other.top_right &&
			center == other.center &&
			bottom_left == other.bottom_left &&
			bottom_right == other.bottom_right;
}
}	cross;

int main()
{
	std::vector<std::string> lines;
	std::ifstream input;
	input.open("../input.txt");
	std::string line;
	while (std::getline(input, line))
	{
		lines.push_back(line);
	}

	std::vector<cross> possibleCrosses;
	possibleCrosses.push_back({ 'M', 'S', 'A', 'M', 'S' });
	possibleCrosses.push_back({ 'M', 'M', 'A', 'S', 'S' });
	possibleCrosses.push_back({ 'S', 'S', 'A', 'M', 'M' });
	possibleCrosses.push_back({ 'S', 'M', 'A', 'S', 'M' });

	int crosses = 0;

	// loop through every grid cell
	for (size_t i = 0; i <= lines.size() - 3; i++)
	{
		for (size_t j = 0; j <= lines[i].length() - 3; j++)
		{
			cross c;
			c.top_left = lines[i][j];
			c.top_right = lines[i][j + 2];
			c.center = lines[i + 1][j + 1];
			c.bottom_left = lines[i + 2][j];
			c.bottom_right = lines[i + 2][j + 2];

			for (size_t k = 0; k < possibleCrosses.size(); k++)
				if (c == possibleCrosses[k])
					crosses++;
		}
	}

	std::cout << "Crosses: " << crosses << std::endl;
}
