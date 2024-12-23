#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <regex>
#include <exception>
#include <vector>
#include <algorithm>
#include <map>
#include <functional>
#include <utility>

uint64_t mix(uint64_t in, uint64_t value)
{
	return in ^ value;
}
uint64_t prune(uint64_t in)
{
	return in % 16777216;
}
uint64_t getNextSecret(uint64_t in)
{
	// Step 1: Multiply by 64, mix, prune
	uint64_t temp = in * 64;
	in = mix(in, temp);
	in = round(in);
	in = prune(in);

	// Step 2: Divide by 32, mix, prune
	temp = in / 32;
	in = mix(in, temp);
	in = prune(in);

	// Step 3: Multiply by 2048, mix, prune
	temp = in * 2048;
	in = mix(in, temp);
	in = prune(in);

	return in;
}

int main()
{
	std::ifstream input;
	input.open("../input.txt");
	std::vector<std::string> lines;
	std::string line;
	uint64_t sum = 0;
	while (std::getline(input, line))
	{
		lines.push_back(line);

		std::cout << line << ": ";

		uint64_t nbr = std::stoll(line);
		for (int i = 0; i < 2000; i++)
		{
			nbr = getNextSecret(nbr);
		}
		std::cout << nbr << std::endl;
		sum += nbr;
	}

	std::cout << "sum" << sum << std::endl;
}
