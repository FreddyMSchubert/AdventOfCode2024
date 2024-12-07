#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <regex>
#include <exception>
#include <vector>

// basically count up in binary
bool nextOperatorCombo(std::vector<bool>& operators)
{
	for (int i = operators.size() - 1; i >= 0; --i)
	{
		if (operators[i] == false)
		{
			operators[i] = true;
			while (++i < operators.size())
				operators[i] = false;
			return true;
		}
	}
	return false;
}

int64_t calcResult(std::vector<int64_t> numbers, std::vector<bool> operators)
{
	int64_t result = numbers[0];
	for (int i = 0; i < operators.size(); ++i)
	{
		if (operators[i] == false)
			result += numbers[i + 1];
		else
			result *= numbers[i + 1];
	}
	return result;
}

void printCalc(std::vector<int64_t> numbers, std::vector<bool> operators)
{
	std::cout << numbers[0];
	for (int i = 0; i < operators.size(); ++i)
	{
		if (operators[i] == false)
			std::cout << " + ";
		else
			std::cout << " * ";
		std::cout << numbers[i + 1];
	}
	std::cout << std::endl;
}

int main()
{
	int64_t validCombos = 0;

	std::vector<std::string> lines;
	std::ifstream input;
	input.open("../input.txt");
	std::string line;
	while (std::getline(input, line))
	{
		lines.push_back(line);

		std::istringstream iss(line);
		int64_t key;
		char delim;
		iss >> key >> delim;

		std::vector<int64_t> values;
		int64_t number;
		while (iss >> number)
			values.push_back(number);

		std::cout << key << ": ";
		for (int i = 0; i < values.size(); ++i)
			std::cout << values[i] << " ";
		std::cout << std::endl;

		std::vector<bool> operators(values.size() - 1, false); // false = +, true = *

		bool found = false;
		do
		{
			if (calcResult(values, operators) == key)
			{
				validCombos += calcResult(values, operators);
				std::cout << "--- Valid: ";
				printCalc(values, operators);
				found = true;
				break;
			}
		} while (nextOperatorCombo(operators));
		if (!found)
			std::cout << "--- Invalid" << std::endl;
	}

	std::cout << "Valid combinations: " << validCombos << std::endl;
}
