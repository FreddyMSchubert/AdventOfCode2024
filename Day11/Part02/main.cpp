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
#include <unordered_map>

struct Stone
{
	std::string value;
	int stepsLeft;
};

struct Key
{
	std::string value;
	int depth;
	bool operator==(const Key &other) const
	{
		return depth == other.depth && value == other.value;
	}
};

struct KeyHash
{
	std::size_t operator()(const Key &k) const
	{
		std::hash<std::string> sh;
		std::hash<int> ih;
		return sh(k.value) ^ (ih(k.depth) << 1);
	}
};

static std::unordered_map<Key, int64_t, KeyHash> memo;

std::string trimLeadingZeros(const std::string &val)
{
	size_t firstNonZero = 0;
	while (firstNonZero < val.size() && val[firstNonZero] == '0')
	{
		firstNonZero++;
	}
	if (firstNonZero == val.size())
	{
		return "0";
	}
	return val.substr(firstNonZero);
}

void expandStoneRec(const std::string &s, int depth, int64_t & count)
{
	if (depth == 0)
	{
		count += 1;
		return;
	}

	Key k{ s, depth };
	if (auto it = memo.find(k); it != memo.end())
	{
		count += it->second;
		return;
	}

	int64_t localCount = 0;

	if (s == "0")
	{
		expandStoneRec("1", depth - 1, localCount);
	}
	else if ((int)s.size() % 2 == 0)
	{
		int half = (int)s.size() / 2;
		std::string leftVal = trimLeadingZeros(s.substr(0, half));
		std::string rightVal = trimLeadingZeros(s.substr(half));
		expandStoneRec(leftVal, depth - 1, localCount);
		expandStoneRec(rightVal, depth - 1, localCount);
	}
	else
	{
		std::string multiplied = std::to_string(std::stoll(s) * 2024);
		expandStoneRec(multiplied, depth - 1, localCount);
	}

	memo[k] = localCount;
	count += localCount;
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

	std::vector<std::string> Rawstones;
	std::istringstream iss(lines[0]);
	std::string token;
	while (std::getline(iss, token, ' '))
	{
		Rawstones.push_back(token);
	}

	int64_t count = 0;

	std::vector<Stone> stones;
	for (const auto &stone : Rawstones)
	{
		stones.push_back({stone, 75});
	}

	for (size_t i = 0; i < stones.size(); i++)
		expandStoneRec(stones[i].value, stones[i].stepsLeft, count);

	std::cout << "Number of stones after 75 blinks: " << count << std::endl;
}
