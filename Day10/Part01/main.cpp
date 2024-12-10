#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <regex>
#include <exception>
#include <vector>
#include <algorithm>

/*
--- Day 10: Hoof It ---
You all arrive at a Lava Production Facility on a floating island in the sky. As the others begin to search the massive industrial complex, you feel a small nose boop your leg and look down to discover a reindeer wearing a hard hat.

The reindeer is holding a book titled "Lava Island Hiking Guide". However, when you open the book, you discover that most of it seems to have been scorched by lava! As you're about to ask how you can help, the reindeer brings you a blank topographic map of the surrounding area (your puzzle input) and looks up at you excitedly.

Perhaps you can help fill in the missing hiking trails?

The topographic map indicates the height at each position using a scale from 0 (lowest) to 9 (highest). For example:

0123
1234
8765
9876
Based on un-scorched scraps of the book, you determine that a good hiking trail is as long as possible and has an even, gradual, uphill slope. For all practical purposes, this means that a hiking trail is any path that starts at height 0, ends at height 9, and always increases by a height of exactly 1 at each step. Hiking trails never include diagonal steps - only up, down, left, or right (from the perspective of the map).

You look up from the map and notice that the reindeer has helpfully begun to construct a small pile of pencils, markers, rulers, compasses, stickers, and other equipment you might need to update the map with hiking trails.

A trailhead is any position that starts one or more hiking trails - here, these positions will always have height 0. Assembling more fragments of pages, you establish that a trailhead's score is the number of 9-height positions reachable from that trailhead via a hiking trail. In the above example, the single trailhead in the top left corner has a score of 1 because it can reach a single 9 (the one in the bottom left).

This trailhead has a score of 2:

...0...
...1...
...2...
6543456
7.....7
8.....8
9.....9
(The positions marked . are impassable tiles to simplify these examples; they do not appear on your actual topographic map.)

This trailhead has a score of 4 because every 9 is reachable via a hiking trail except the one immediately to the left of the trailhead:

..90..9
...1.98
...2..7
6543456
765.987
876....
987....
This topographic map contains two trailheads; the trailhead at the top has a score of 1, while the trailhead at the bottom has a score of 2:

10..9..
2...8..
3...7..
4567654
...8..3
...9..2
.....01
Here's a larger example:

89010123
78121874
87430965
96549874
45678903
32019012
01329801
10456732
This larger example has 9 trailheads. Considering the trailheads in reading order, they have scores of 5, 6, 5, 3, 1, 3, 5, 3, and 5. Adding these scores together, the sum of the scores of all trailheads is 36.

The reindeer gleefully carries over a protractor and adds it to the pile. What is the sum of the scores of all trailheads on your topographic map?
*/

typedef struct s_pos
{
	int x;
	int y;
} pos;

typedef struct s_trail
{
	pos pos;
	bool valid;
	bool done;
	int trailHeadId;
} trail;
inline bool operator==(const trail& lhs, const trail& rhs) {
    return lhs.pos.x == rhs.pos.x &&
           lhs.pos.y == rhs.pos.y &&
           lhs.valid == rhs.valid &&
           lhs.done == rhs.done &&
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
				newTrail.pos.x = x;
				newTrail.pos.y = y;
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
		char currentHeight = map[trails[t].pos.y][trails[t].pos.x];
		// create new trails instead of chanign the current one
		if (trails[t].pos.y > 0 && map[trails[t].pos.y - 1][trails[t].pos.x] == currentHeight + 1)
		{
			trail newTrail;
			newTrail.pos.x = trails[t].pos.x;
			newTrail.pos.y = trails[t].pos.y - 1;
			newTrail.valid = true;
			newTrail.done = map[newTrail.pos.y][newTrail.pos.x] == '9';
			newTrail.trailHeadId = trails[t].trailHeadId;
			trails.push_back(newTrail);
		}
		if (trails[t].pos.y < map.size() - 1 && map[trails[t].pos.y + 1][trails[t].pos.x] == currentHeight + 1)
		{
			trail newTrail;
			newTrail.pos.x = trails[t].pos.x;
			newTrail.pos.y = trails[t].pos.y + 1;
			newTrail.valid = true;
			newTrail.done = map[newTrail.pos.y][newTrail.pos.x] == '9';
			newTrail.trailHeadId = trails[t].trailHeadId;
			trails.push_back(newTrail);
		}
		if (trails[t].pos.x > 0 && map[trails[t].pos.y][trails[t].pos.x - 1] == currentHeight + 1)
		{
			trail newTrail;
			newTrail.pos.x = trails[t].pos.x - 1;
			newTrail.pos.y = trails[t].pos.y;
			newTrail.valid = true;
			newTrail.done = map[newTrail.pos.y][newTrail.pos.x] == '9';
			newTrail.trailHeadId = trails[t].trailHeadId;
			trails.push_back(newTrail);
		}
		if (trails[t].pos.x < map[0].size() - 1 && map[trails[t].pos.y][trails[t].pos.x + 1] == currentHeight + 1)
		{
			trail newTrail;
			newTrail.pos.x = trails[t].pos.x + 1;
			newTrail.pos.y = trails[t].pos.y;
			newTrail.valid = true;
			newTrail.done = map[newTrail.pos.y][newTrail.pos.x] == '9';
			newTrail.trailHeadId = trails[t].trailHeadId;
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
