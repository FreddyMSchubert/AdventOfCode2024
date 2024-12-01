#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

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

	int similarity = 0;
	for (auto it = col1.begin(); it != col1.end(); ++it)
	{
		std::cout << *it << std::endl;
		int appearences = 0;
		for (auto it2 = col2.begin(); it2 != col2.end(); ++it2)
			if (*it == *it2)
				appearences++;

		similarity += *it * appearences;
	}

	std::cout << "Similarity Score: " << similarity << std::endl;
}
