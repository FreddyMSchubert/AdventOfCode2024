#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

int abs(int num)
{
	if (num < 0)
	{
		return -num;
	}
	return num;
}

int main()
{
	std::multiset<int> col1;
	std::multiset<int> col2;

	std::ifstream input;
	input.open("../input.txt");
	if (!input.is_open() || !input.good())
	{
		std::cerr << "Error opening file" << std::endl;
		return 1;
	}
	std::string line;
	while (std::getline(input, line))
	{
		int num1, num2;
		std::istringstream iss(line);
		iss >> num1;
		iss >> num2;
		col1.insert(num1);
		col2.insert(num2);
	}

	int total = 0;
	for (size_t i = 0; i < col1.size(); ++i)
	{
		auto it = col1.begin();
		auto it2 = col2.begin();
		std::advance(it, i);
		std::advance(it2, i);
		total += abs(*it - *it2);
	}

	std::cout << "Total: " << total << std::endl;
}
