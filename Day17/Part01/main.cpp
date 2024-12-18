#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <regex>
#include <exception>
#include <vector>
#include <algorithm>

int getOperandValue(int operand, const std::array<int, 3> &registers, bool isCombo)
{
	if (isCombo)
	{
		if (operand >= 0 && operand <= 3) return operand;
		switch (operand) {
			case 4: return registers[0]; // Register A
			case 5: return registers[1]; // Register B
			case 6: return registers[2]; // Register C
			default: throw std::invalid_argument("Invalid combo operand");
		}
	}
	else
	{
		return operand;
	}
}

int main()
{
	std::ifstream input;
	input.open("../input.txt");
	std::vector<std::string> lines;
	std::string line;
	while (std::getline(input, line))
	{
		lines.push_back(line);
	}

	std::array<int, 3> registers;
	std::vector<int> program;

	registers[0] = lines[0].find("Register A: ") != std::string::npos ? std::stoi(lines[0].substr(12)) : 0;
	registers[1] = lines[1].find("Register B: ") != std::string::npos ? std::stoi(lines[1].substr(12)) : 0;
	registers[2] = lines[2].find("Register C: ") != std::string::npos ? std::stoi(lines[2].substr(12)) : 0;
	std::string programLine = lines[4];
	std::istringstream programStream(programLine.substr(9));
	std::string programToken;
	while (std::getline(programStream, programToken, ','))
		program.push_back(std::stoi(programToken));

	int instructionPointer = 0;
	while (instructionPointer < program.size() - 1)
	{
		int opcode = program[instructionPointer];
		int operand = program[instructionPointer + 1];
		bool jumpOccurred = false;
		int denom, value, outVal;

		switch (opcode)
		{
			case 0: // adv
				denom = 1 << getOperandValue(operand, registers, true);
				registers[0] /= denom;
				break;
			case 1: // bxl
				value = getOperandValue(operand, registers, false);
				registers[1] ^= value;
				break;
			case 2: // bst
				value = getOperandValue(operand, registers, true);
				registers[1] = value % 8;
				break;
			case 3: // jnz
				value = getOperandValue(operand, registers, false);
				if (registers[0] != 0)
				{
					instructionPointer = value;
					jumpOccurred = true;
					continue;
				}
				break;
			case 4: // bxc
				registers[1] ^= registers[2];
				break;
			case 5: // out
				outVal = getOperandValue(operand, registers, true);
				outVal %= 8;
				std::cout << outVal << ",";
				break;
			case 6: // bdv
				denom = 1 << getOperandValue(operand, registers, true);
				registers[1] = registers[0] / denom; // Correct: B = A / denom
				break;
			case 7: // cdv
				denom = 1 << getOperandValue(operand, registers, true);
				registers[2] = registers[0] / denom; // Correct: C = A / denom
				break;
		}
		if (!jumpOccurred)
			instructionPointer += 2;
	}
}
