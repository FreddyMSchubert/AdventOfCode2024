#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <regex>
#include <exception>
#include <vector>

// basically count up in binary
bool nextOperatorCombo(std::vector<int>& operators)
{
	for (int i = operators.size() - 1; i >= 0; --i)
	{
		if (operators[i] < 2)
		{
			operators[i]++;
			while (++i < operators.size())
				operators[i] = 0;
			return true;
		}
	}
	return false;
}

int countDigits(int64_t number)
{
	if (number == 0) return 1;
	int digits = 0;
	while (number != 0) {
		number /= 10;
		digits++;
	}
	return digits;
}

void printCalc(std::vector<int64_t> numbers, std::vector<int> operators)
{
	std::cout << numbers[0];
	for (int i = 0; i < operators.size(); ++i)
	{
		if (operators[i] == 0)
			std::cout << " + ";
		else if (operators[i] == 1)
			std::cout << " * ";
		else if (operators[i] == 2)
			std::cout << " || ";
		else
			throw std::runtime_error("Invalid operator");
		std::cout << numbers[i + 1];
	}
	std::cout << std::endl;
}

int64_t concatenate(int64_t a, int64_t b)
{
	int digits = countDigits(b);
	return a * static_cast<int64_t>(std::pow(10, digits)) + b;
}

int64_t calcResult(std::vector<int64_t> numbers, std::vector<int> operators)
{
	int64_t result = numbers[0];
	for (int i = 0; i < operators.size(); ++i)
	{
		if (operators[i] == 0)
			result += numbers[i + 1];
		else if (operators[i] == 1)
			result *= numbers[i + 1];
		else if (operators[i] == 2)
			result = concatenate(result, numbers[i + 1]);
		else
			throw std::runtime_error("Invalid operator");
	}
	return result;
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

		std::vector<int> operators(values.size() - 1, 0); // false = +, true = *

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
