#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <regex>
#include <exception>
#include <vector>
#include <algorithm>
using namespace std;


struct Regs {
	long long A;
	long long B;
	long long C;
};

static long long combo(int op, const Regs &r) {
	if (op <= 3) return op;
	else if (op == 4) return r.A;
	else if (op == 5) return r.B;
	else if (op == 6) return r.C;
	else throw invalid_argument("Invalid combo operand");
}

static vector<int> runProgram(const vector<int> &program, Regs regs, long long a = -1) {
	vector<int> outputs;
	if (a != -1) regs.A = a;

	int i = 0;
	while (i < (int)program.size()) {
		int opcode = program[i];
		int operand = (i + 1 < (int)program.size()) ? program[i + 1] : 0;

		switch (opcode) {
			case 0: { // adv
				long long denom = (1LL << combo(operand, regs));
				regs.A = regs.A / denom;
				break;
			}
			case 1: { // bxl
				regs.B = regs.B ^ operand;
				break;
			}
			case 2: { // bst
				int val = combo(operand, regs) % 8;
				regs.B = val;
				break;
			}
			case 3: { // jnz
				if (regs.A != 0) {
					i = operand;
					continue;
				}
				break;
			}
			case 4: { // bxc
				regs.B = regs.B ^ regs.C;
				break;
			}
			case 5: { // out
				int outVal = combo(operand, regs) % 8;
				outputs.push_back(outVal);
				break;
			}
			case 6: { // bdv
				long long denom = (1LL << combo(operand, regs));
				regs.B = regs.A / denom;
				break;
			}
			case 7: { // cdv
				long long denom = (1LL << combo(operand, regs));
				regs.C = regs.A / denom;
				break;
			}
		}

		i += 2;
	}

	return outputs;
}

static long long recursiveSearch(const vector<int> &program, const vector<int> &output, Regs reg, int index, long long a)
{
	if (index < 0)
		return a; 

	std::cout << "Index: " << index << "\n";
	int output_value = output[index];

	int neededLen = (int)output.size() - index; 
	for (int newVal = 0; newVal < 8; newVal++) {
		long long testa = (a << 3) + newVal;
		Regs testRegs = reg;
		testRegs.A = testa;

		vector<int> out = runProgram(program, testRegs);
		if ((int)out.size() == neededLen) {
			bool match = true;
			for (int k = 0; k < neededLen; k++) {
				if (out[k] != output[index + k]) {
					match = false;
					break;
				}
			}
			if (match) {
				// Recurse further down
				long long res = recursiveSearch(program, output, testRegs, index - 1, testa);
				if (res != -1) return res;
			}
		}
	}

	return -1;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	vector<string> lines;
	{
		ifstream input("../input.txt");
		string line;
		while (std::getline(input, line))
			lines.push_back(line);
	}

	Regs regs;
	std::vector<int> program;
	regs.A = lines[0].find("Register A: ") != std::string::npos ? std::stoll(lines[0].substr(12)) : 0;
	regs.B = lines[1].find("Register B: ") != std::string::npos ? std::stoll(lines[1].substr(12)) : 0;
	regs.C = lines[2].find("Register C: ") != std::string::npos ? std::stoll(lines[2].substr(12)) : 0;
	std::string programLine = lines[4];
	std::istringstream programStream(programLine.substr(9));
	std::string programToken;
	while (std::getline(programStream, programToken, ','))
		program.push_back(std::stoi(programToken));

	vector<int> outputs = runProgram(program, regs);

	Regs reg0 = regs;
	reg0.A = 0; 

	long long result = recursiveSearch(program, program, reg0, (int)program.size() - 1, 0);
	cout << result << "\n";

	return 0;
}
