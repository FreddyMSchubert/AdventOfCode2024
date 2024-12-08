#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <regex>
#include <exception>
#include <vector>

struct Node
{
	int x;
	int y;
	float dist;
	char type;
};

float posDist(int x1, int x2, int y1, int y2)
{
    // Calculate the difference in x and y coordinates
    int deltaX = x2 - x1;
    int deltaY = y2 - y1;

    // Compute the square of differences
    float distanceSquared = (float)(deltaX * deltaX) + (float)(deltaY * deltaY);

    // Calculate the square root of the sum to get the Euclidean distance
    float distance = sqrt(distanceSquared);

    return distance;
}

bool isColinear(int x1, int y1, int x2, int y2, int x, int y) {
    return (x2 - x1) * (y - y1) == (y2 - y1) * (x - x1);
}

int main()
{
	int64_t outputNbr = 0;

	std::vector<std::string> lines;
	std::ifstream input;
	input.open("../input.txt");
	std::string line;
	while (std::getline(input, line))
	{
		lines.push_back(line);
	}

	std::vector<std::vector<bool>> visited = std::vector<std::vector<bool>>(lines.size(), std::vector<bool>(lines[0].size(), false));
	std::vector<Node> nodes;

	for (int y = 0; y < lines.size(); y++)
	{
		for (int x = 0; x < lines[0].size(); x++)
		{
			if (lines[y][x] != '.')
			{
				Node node;
				node.x = x;
				node.y = y;
				node.dist = 0;
				node.type = lines[y][x];
				nodes.push_back(node);
			}
		}
	}

	// loop through all possible antenna postiions
	for (int y = 0; y < lines.size(); y++)
	{
		for (int x = 0; x < lines[0].size(); x++)
		{
			// calculate node dist for
			std::vector<Node> tempNodes = nodes;
			for (int i = 0; i < tempNodes.size(); i++)
			{
				tempNodes[i].dist = posDist(x, tempNodes[i].x, y, tempNodes[i].y);
			}

			// loop through all possible antennas / chars
			for (int i = 0; i < 255; i++)
			{
				char c = i;
				std::vector<Node> cNodes;
				for (int j = 0; j < tempNodes.size(); j++)
				{
					if (tempNodes[j].type == c)
					{
						cNodes.push_back(tempNodes[j]);
					}
				}

				// check every two-node combo
				for (int n1 = 0; n1 < cNodes.size(); n1++)
				{
					for (int n2 = n1 + 1; n2 < cNodes.size(); n2++)
					{
						Node node1 = cNodes[n1];
						Node node2 = cNodes[n2];
						if (node1.type != node2.type || node1.x == node2.x && node1.y == node2.y)
						{
							continue;
						}
						if ((node1.dist == node2.dist * 2 || node1.dist * 2 == node2.dist) && isColinear(node1.x, node1.y, node2.x, node2.y, x, y))
						{
							visited[y][x] = true;
							std::cout << "Found: " << y << ", " << x << ", which is true because of " << node1.y << ", " << node1.x << " dist " << node1.dist << " and " << node2.y << ", " << node2.x << " dist " << node2.dist << " match type " << node1.type << std::endl;
							continue;
						}
					}
				}
			}
		}
	}

	// print visited
	for (int y = 0; y < lines.size(); y++)
	{
		for (int x = 0; x < lines[0].size(); x++)
		{
			if (visited[y][x])
			{
				std::cout << "X";
			}
			else
			{
				std::cout << ".";
			}
		}
		std::cout << std::endl;
	}

	for (int y = 0; y < lines.size(); y++)
	{
		for (int x = 0; x < lines[0].size(); x++)
		{
			if (visited[y][x])
			{
				outputNbr++;
			}
		}
	}

	std::cout << "Answer: " << outputNbr << std::endl;
}
