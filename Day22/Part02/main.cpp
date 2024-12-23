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

struct TupleHash {
	std::size_t operator()(const std::tuple<int, int, int, int>& key) const {
		return std::hash<int>()(std::get<0>(key)) ^ 
			(std::hash<int>()(std::get<1>(key)) << 1) ^ 
			(std::hash<int>()(std::get<2>(key)) << 2) ^ 
			(std::hash<int>()(std::get<3>(key)) << 3);
	}
};

uint64_t mix(uint64_t in, uint64_t value)
{
	return in ^ value;
}
uint64_t prune(uint64_t in)
{
	return in % 16777216;
}
std::vector<uint64_t> generatePrices(uint64_t in)
{
	std::vector<uint64_t> prices;
	prices.reserve(2001);
	prices.push_back(in);

	uint64_t current = in;
	for (int i = 0; i < 2000; ++i)
	{
		uint64_t temp = current * 64;
		current = mix(current, temp);
		current = prune(current);

		temp = current / 32;
		current = mix(current, temp);
		current = prune(current);

		temp = current * 2048;
		current = mix(current, temp);
		current = prune(current);

		prices.push_back(current);
	}

	return prices;
}
std::vector<int> computeChanges(const std::vector<int>& P)
{
	std::vector<int> changes;
	changes.reserve(P.size() - 1);
	for (size_t i = 0; i < P.size() - 1; ++i) {
		changes.push_back(P[i + 1] - P[i]);
	}
	return changes;
}
// unique key from four changes
std::tuple<int, int, int, int> createPatternKey(const std::vector<int>& C, size_t index)
{
	return std::make_tuple(C[index], C[index + 1], C[index + 2], C[index + 3]);
}

std::unordered_map<std::tuple<int, int, int, int>, int, TupleHash> getScores(const std::vector<int>& P, const std::vector<int>& C) {
	std::unordered_map<std::tuple<int, int, int, int>, int, TupleHash> ANS;

	for (size_t i = 0; i + 3 < C.size(); ++i) {
		auto pattern = createPatternKey(C, i);
		if (ANS.find(pattern) == ANS.end()) {
			if (i + 4 < P.size()) {
				ANS[pattern] = P[i + 4];
			}
		}
	}

	return ANS;
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
	}

	uint64_t p1 = 0;
	std::unordered_map<std::tuple<int, int, int, int>, int, TupleHash> SCORE;

	for (const auto& str : lines)
	{
		uint64_t initialSecret = std::stoull(str);xw

		std::vector<uint64_t> P = generatePrices(initialSecret);
		p1 += P.back();

		std::vector<int> P_mod10;
		P_mod10.reserve(P.size());
		for (const auto& num : P)
			P_mod10.push_back(static_cast<int>(num % 10));
		std::vector<int> C = computeChanges(P_mod10);

		std::unordered_map<std::tuple<int, int, int, int>, int, TupleHash> S = getScores(P_mod10, C);
		for (const auto& [k, v] : S)
			SCORE[k] += v;
	}

	int maxScore = 0;
	for (const auto& [k, v] : SCORE)
		if (v > maxScore) {
			maxScore = v;

	std::cout << "Sum of the 2000th secret numbers: " << p1 << std::endl;
	std::cout << "Maximum score from patterns: " << maxScore << std::endl;

	return 0;
}
