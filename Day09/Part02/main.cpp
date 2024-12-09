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
		if (idLine[i] == -1)
			std::cout << ".";
		else
			std::cout << "_" << idLine[i];
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

	std::cout << "----- STEP 2\x1b[32m" << std::endl;
	// Identify files: collect (id, start, end)
	std::vector<std::tuple<int,int,int>> files;
	{
		int currentId = idLine[0];
		int start = 0;
		for (int i = 1; i < (int)idLine.size(); i++) {
			if (idLine[i] != currentId) {
				files.push_back(std::make_tuple(currentId, start, i - 1));
				currentId = idLine[i];
				start = i;
			}
		}
		files.push_back(std::make_tuple(currentId, start, (int)idLine.size() - 1));
	}

	// Remove free space entries from files vector
	files.erase(std::remove_if(files.begin(), files.end(), [](auto &f){return std::get<0>(f) == -1;}), files.end());

	// Sort files by descending ID
	std::sort(files.begin(), files.end(), [](auto &a, auto &b){return std::get<0>(a) > std::get<0>(b);});

	// For each file in descending order, try to move it as a whole
	for (auto &f : files) {
		int fid, fstart, fend;
		std::tie(fid, fstart, fend) = f;
		int flen = fend - fstart + 1;

		// Search for free space to the left of fstart
		int bestPos = -1;
		int count = 0;
		for (int i = 0; i < fstart; i++) {
			if (idLine[i] == -1) {
				count++;
				if (count == flen) {
					bestPos = i - flen + 1;
					break;
				}
			} else {
				count = 0;
			}
		}

		// If found suitable space, move file
		if (bestPos != -1) {
			for (int i = fstart; i <= fend; i++) {
				idLine[i] = -1;
			}
			for (int i = 0; i < flen; i++) {
				idLine[bestPos + i] = fid;
			}

			// Update f to new position
			fstart = bestPos;
			fend = bestPos + flen - 1;
			f = std::make_tuple(fid, fstart, fend);
		}
	}

	std::cout << "----- STEP 3\x1b[34m" << std::endl;
	// 3. calc answer
	// in: 0099811188827773336446555566..............
	// out: 0 * 0 = 0, 1 * 0 = 0, 2 * 9 = 18, 3 * 9 = 27, 4 * 8 = 32
	for (int64_t i = 0; i < idLine.size() - 1; i++)
	{
		if (idLine[i] != -1)
		{
			int64_t nbr1 = idLine[i];
			outputNbr += nbr1 * i;
			if (print)
				std::cout << idLine[i] << " * " << i << " = " << outputNbr << std::endl;
		}
	}

	std::cout << "Answer: " << outputNbr << std::endl;
}
