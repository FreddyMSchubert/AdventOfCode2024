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
inline bool operator==(const pos& lhs, const pos& rhs) {
    return lhs.x == rhs.x && lhs.y == rhs.y;
}

typedef struct s_trail
{
	pos position;
	bool valid;
	bool done;
	int trailHeadId;
	std::vector<pos> path;
} trail;

inline bool operator==(const trail& lhs, const trail& rhs) {
    return lhs.position.x == rhs.position.x &&
           lhs.position.y == rhs.position.y &&
           lhs.valid == rhs.valid &&
           lhs.done == rhs.done &&
		   lhs.path == rhs.path &&
           lhs.trailHeadId == rhs.trailHeadId;
}


int main()
{
	int64_t outputNbr = 0;
	bool print = false;
	int maxTrailHeadId = 0;

	std::ifstream input;
	input.open("../input.txt");
	std::vector<std::string> map;
	std::string line;
	while (std::getline(input, line))
	{
		map.push_back(line);
	}

	/*
		basically, flood fill but only sstarting where the height is 0 and ending where the height is 9, sloping in between
		recursive structure sucks because huge example, so we gotta loop this.
	*/
	std::vector<trail> trails;

	// 1 for every 0 create a trail
	// 2 for every trail, look at every direction you can go in. if none exist, either delete yourself or split yourself up.
	// 3 once at 9, youre finished
	// 4 count every trails thats not a duplicate


	// 1
	for (int y = 0; y < map.size(); y++)
	{
		for (int x = 0; x < map[0].size(); x++)
		{
			if (map[y][x] == '0')
			{
				trail newTrail;
				newTrail.position.x = x;
				newTrail.position.y = y;
				newTrail.valid = true;
				newTrail.done = false;
				newTrail.trailHeadId = maxTrailHeadId++;
				trails.push_back(newTrail);
			}
		}
	}

	// 2
	for (int t = 0; t < trails.size(); t++)
	{
		if (!trails[t].valid || trails[t].done)
			continue;

		// check if we can go up
		char currentHeight = map[trails[t].position.y][trails[t].position.x];
		// create new trails instead of chanign the current one
		if (trails[t].position.y > 0 && map[trails[t].position.y - 1][trails[t].position.x] == currentHeight + 1)
		{
			trail newTrail;
			newTrail.position.x = trails[t].position.x;
			newTrail.position.y = trails[t].position.y - 1;
			newTrail.valid = true;
			newTrail.done = map[newTrail.position.y][newTrail.position.x] == '9';
			newTrail.trailHeadId = trails[t].trailHeadId;
			newTrail.path = trails[t].path;
			newTrail.path.push_back(trails[t].position);
			trails.push_back(newTrail);
		}
		if (trails[t].position.y < map.size() - 1 && map[trails[t].position.y + 1][trails[t].position.x] == currentHeight + 1)
		{
			trail newTrail;
			newTrail.position.x = trails[t].position.x;
			newTrail.position.y = trails[t].position.y + 1;
			newTrail.valid = true;
			newTrail.done = map[newTrail.position.y][newTrail.position.x] == '9';
			newTrail.trailHeadId = trails[t].trailHeadId;
			newTrail.path = trails[t].path;
			newTrail.path.push_back(trails[t].position);
			trails.push_back(newTrail);
		}
		if (trails[t].position.x > 0 && map[trails[t].position.y][trails[t].position.x - 1] == currentHeight + 1)
		{
			trail newTrail;
			newTrail.position.x = trails[t].position.x - 1;
			newTrail.position.y = trails[t].position.y;
			newTrail.valid = true;
			newTrail.done = map[newTrail.position.y][newTrail.position.x] == '9';
			newTrail.trailHeadId = trails[t].trailHeadId;
			newTrail.path = trails[t].path;
			newTrail.path.push_back(trails[t].position);
			trails.push_back(newTrail);
		}
		if (trails[t].position.x < map[0].size() - 1 && map[trails[t].position.y][trails[t].position.x + 1] == currentHeight + 1)
		{
			trail newTrail;
			newTrail.position.x = trails[t].position.x + 1;
			newTrail.position.y = trails[t].position.y;
			newTrail.valid = true;
			newTrail.done = map[newTrail.position.y][newTrail.position.x] == '9';
			newTrail.trailHeadId = trails[t].trailHeadId;
			newTrail.path = trails[t].path;
			newTrail.path.push_back(trails[t].position);
			trails.push_back(newTrail);
		}
		trails[t].valid = false;
	}

	// 4
	int score = 0;
	for (int th = 0; th < maxTrailHeadId; th++)
	{
		std::vector<trail> trailss;
		for (int i = 0; i < trails.size(); i++)
		{
			if (trails[i].trailHeadId == th && trails[i].done && std::find(trailss.begin(), trailss.end(), trails[i]) == trailss.end())
				trailss.push_back(trails[i]);
		}
		score += trailss.size();
	}

	std::cout << "The sum of the scores of all trailheads is: " << score << std::endl;
}
