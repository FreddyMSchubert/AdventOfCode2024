#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <regex>
#include <exception>
#include <vector>

/*
--- Day 6: Guard Gallivant ---
The Historians use their fancy device again, this time to whisk you all away to the North Pole prototype suit manufacturing lab... in the year 1518! It turns out that having direct access to history is very convenient for a group of historians.

You still have to be careful of time paradoxes, and so it will be important to avoid anyone from 1518 while The Historians search for the Chief. Unfortunately, a single guard is patrolling this part of the lab.

Maybe you can work out where the guard will go ahead of time so that The Historians can search safely?

You start by making a map (your puzzle input) of the situation. For example:

....#.....
.........#
..........
..#.......
.......#..
..........
.#..^.....
........#.
#.........
......#...
The map shows the current position of the guard with ^ (to indicate the guard is currently facing up from the perspective of the map). Any obstructions - crates, desks, alchemical reactors, etc. - are shown as #.

Lab guards in 1518 follow a very strict patrol protocol which involves repeatedly following these steps:

If there is something directly in front of you, turn right 90 degrees.
Otherwise, take a step forward.
Following the above protocol, the guard moves up several times until she reaches an obstacle (in this case, a pile of failed suit prototypes):

....#.....
....^....#
..........
..#.......
.......#..
..........
.#........
........#.
#.........
......#...
Because there is now an obstacle in front of the guard, she turns right before continuing straight in her new facing direction:

....#.....
........>#
..........
..#.......
.......#..
..........
.#........
........#.
#.........
......#...
Reaching another obstacle (a spool of several very long polymers), she turns right again and continues downward:

....#.....
.........#
..........
..#.......
.......#..
..........
.#......v.
........#.
#.........
......#...
This process continues for a while, but the guard eventually leaves the mapped area (after walking past a tank of universal solvent):

....#.....
.........#
..........
..#.......
.......#..
..........
.#........
........#.
#.........
......#v..
By predicting the guard's route, you can determine which specific positions in the lab will be in the patrol path. Including the guard's starting position, the positions visited by the guard before leaving the area are marked with an X:

....#.....
....XXXXX#
....X...X.
..#.X...X.
..XXXXX#X.
..X.X.X.X.
.#XXXXXXX.
.XXXXXXX#.
#XXXXXXX..
......#X..
In this example, the guard will visit 41 distinct positions on your map.

Predict the path of the guard. How many distinct positions will the guard visit before leaving the mapped area?


*/

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

	std::vector<std::vector<bool>> visited(lines.size(), std::vector<bool>(lines[0].size(), false));
	int direction = -1; // 0 = up, 1 = right, 2 = down, 3 = left
	int x = -1;
	int y = -1;

	for (size_t py = 0; py < lines.size(); py++)
	{
		std::string l = lines[py];
		for (size_t px = 0; px < l.size(); px++)
		{
			if (lines[py][px] == '^' || lines[py][px] == 'v' || lines[py][px] == '<' || lines[py][px] == '>')
			{
				x = px;
				y = py;
				visited[y][x] = true;

				if (lines[py][px] == '^')
				{
					direction = 0;
				}
				else if (lines[py][px] == '>')
				{
					direction = 1;
				}
				else if (lines[py][px] == 'v')
				{
					direction = 2;
				}
				else if (lines[py][px] == '<')
				{
					direction = 3;
				}
			}
		}
	}

	while (true)
	{
		if (direction == 0)
		{
			if (y - 1 <= 0)
			{
				break;
			}
			if (lines[y - 1][x] == '#')
			{
				direction = 1;
			}
			else
			{
				y--;
				visited[y][x] = true;
			}
		}
		else if (direction == 1)
		{
			if (x + 1 >= lines[y].size())
			{
				break;
			}
			if (lines[y][x + 1] == '#')
			{
				direction = 2;
			}
			else
			{
				x++;
				visited[y][x] = true;
			}
		}
		else if (direction == 2)
		{
			if (y + 1 >= lines.size())
			{
				break;
			}
			if (lines[y + 1][x] == '#')
			{
				direction = 3;
			}
			else
			{
				y++;
				visited[y][x] = true;
			}
		}
		else if (direction == 3)
		{
			if (x - 1 <= 0)
			{
				break;
			}
			if (lines[y][x - 1] == '#')
			{
				direction = 0;
			}
			else
			{
				x--;
				visited[y][x] = true;
			}
		}
	}

	int count = 0;
	for (int py = 0; py < visited.size(); py++)
	{
		for (int px = 0; px < visited[py].size(); px++)
		{
			if (visited[py][px])
			{
				count++;
			}
		}
	}

	std::cout << count << std::endl;
}
