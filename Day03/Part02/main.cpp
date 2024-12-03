#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <regex>
#include <exception>

int main()
{
	std::regex pattern(R"(mul\((\d+),(\d+)\)|do\(\)|don't\(\))");

	int sum = 0;
	bool processMul = true;

	std::ifstream input;
	input.open("../input.txt");
	std::string line;
	while (std::getline(input, line))
	{
		auto begin = std::sregex_iterator(line.begin(), line.end(), pattern);
		auto end = std::sregex_iterator();

		for (std::sregex_iterator i = begin; i != end; ++i)
		{
			std::smatch match = *i;
			if (match[0].str().find("mul(") != std::string::npos && processMul)
			{
				std::string x_str = match[1].str();
				std::string y_str = match[2].str();
				try
				{
					int x = std::stoi(x_str);
					int y = std::stoi(y_str);
					sum += x * y;
				}
				catch (std::exception &ex)
				{}
			}
			else if (match[0].str().find("do()") != std::string::npos)
			{
				processMul = true;
			}
			else if (match[0].str().find("don't()") != std::string::npos)
			{
				processMul = false;
			}
		}
	}

	std::cout << "Sum: " << sum << std::endl;
}
