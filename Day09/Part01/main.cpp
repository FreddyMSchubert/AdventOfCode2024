#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <regex>
#include <exception>
#include <vector>
#include <algorithm>

void printIdLine(std::vector<int> idLine)
{
	for (int i = 0; i < idLine.size(); i++)
	{
		std::cout << "." << idLine[i];
	}
	std::cout << std::endl;
}

int main()
{
	int64_t outputNbr = 0;
	bool print = false;

	std::ifstream input;
	input.open("../input.txt");
	std::string line;
	std::getline(input, line);

	std::cout << "----- STEP 1\x1b[31m" << std::endl;
	// 1. conver to id dot format
	// in: 12345
	// out: 0..111....22222
	int id = 0;
	bool file = true;
	size_t pos = 0;
	std::vector<int> idLine;
	while (pos < line.size())
	{
		int nbr = line[pos] - '0';
		int c = file ? id : -1; // dots are -1
		for (int i = 0; i < nbr; i++)
			idLine.push_back(c);
		if (file)
			id++;
		pos++;
		file = !file;
		if (print)
			printIdLine(idLine);
	}

	if (print)
		std::cout << "----- STEP 2\x1b[32m" << std::endl;
	// 2. remove the garbage by appending to the left
	/*
	0..111....22222
	02.111....2222.
	022111....222..
	0221112...22...
	02211122..2....
	022111222......
	*/
	bool done = false;
	while (!done)
	{
		int firstFreeSpace = -1;
		int lastNonFreeSpace = -1;
		auto it_first = std::find(idLine.begin(), idLine.end(), -1);
		if (it_first != idLine.end())
			firstFreeSpace = std::distance(idLine.begin(), it_first);
		else
			firstFreeSpace = -1;
		auto it_last = std::find_if(idLine.rbegin(), idLine.rend(), [](int x){ return x != -1; });
		if (it_last != idLine.rend())
			lastNonFreeSpace = std::distance(it_last, idLine.rend()) - 1;
		else
			lastNonFreeSpace = -1;

		if (firstFreeSpace != -1 && lastNonFreeSpace != -1 && firstFreeSpace < lastNonFreeSpace)
		{
			int c = idLine[lastNonFreeSpace];
			idLine[lastNonFreeSpace] = -1;
			idLine[firstFreeSpace] = c;
		}
		else
			done = true;
		if (print)
			printIdLine(idLine);
	}

	if (print)
		std::cout << "----- STEP 3\x1b[34m" << std::endl;
	// 3. calc answer
	// in: 0099811188827773336446555566..............
	// out: 0 * 0 = 0, 1 * 0 = 0, 2 * 9 = 18, 3 * 9 = 27, 4 * 8 = 32
	for (int i = 0; i < idLine.size() - 1; i++)
	{
		if (idLine[i] != -1)
		{
			int nbr1 = idLine[i];
			outputNbr += nbr1 * i;
		}
		if (print)
			std::cout << idLine[i] << " * " << i << " = " << outputNbr << std::endl;
	}

	std::cout << "Answer: " << outputNbr << std::endl;
}
