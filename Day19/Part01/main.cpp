#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <regex>
#include <exception>
#include <vector>
#include <algorithm>

/*
--- Day 19: Linen Layout ---
Today, The Historians take you up to the hot springs on Gear Island! Very suspiciously, absolutely nothing goes wrong as they begin their careful search of the vast field of helixes.

Could this finally be your chance to visit the onsen next door? Only one way to find out.

After a brief conversation with the reception staff at the onsen front desk, you discover that you don't have the right kind of money to pay the admission fee. However, before you can leave, the staff get your attention. Apparently, they've heard about how you helped at the hot springs, and they're willing to make a deal: if you can simply help them arrange their towels, they'll let you in for free!

Every towel at this onsen is marked with a pattern of colored stripes. There are only a few patterns, but for any particular pattern, the staff can get you as many towels with that pattern as you need. Each stripe can be white (w), blue (u), black (b), red (r), or green (g). So, a towel with the pattern ggr would have a green stripe, a green stripe, and then a red stripe, in that order. (You can't reverse a pattern by flipping a towel upside-down, as that would cause the onsen logo to face the wrong way.)

The Official Onsen Branding Expert has produced a list of designs - each a long sequence of stripe colors - that they would like to be able to display. You can use any towels you want, but all of the towels' stripes must exactly match the desired design. So, to display the design rgrgr, you could use two rg towels and then an r towel, an rgr towel and then a gr towel, or even a single massive rgrgr towel (assuming such towel patterns were actually available).

To start, collect together all of the available towel patterns and the list of desired designs (your puzzle input). For example:

r, wr, b, g, bwu, rb, gb, br

brwrr
bggr
gbbr
rrbgbr
ubwu
bwurrg
brgr
bbrgwb
The first line indicates the available towel patterns; in this example, the onsen has unlimited towels with a single red stripe (r), unlimited towels with a white stripe and then a red stripe (wr), and so on.

After the blank line, the remaining lines each describe a design the onsen would like to be able to display. In this example, the first design (brwrr) indicates that the onsen would like to be able to display a black stripe, a red stripe, a white stripe, and then two red stripes, in that order.

Not all designs will be possible with the available towels. In the above example, the designs are possible or impossible as follows:

brwrr can be made with a br towel, then a wr towel, and then finally an r towel.
bggr can be made with a b towel, two g towels, and then an r towel.
gbbr can be made with a gb towel and then a br towel.
rrbgbr can be made with r, rb, g, and br.
ubwu is impossible.
bwurrg can be made with bwu, r, r, and g.
brgr can be made with br, g, and r.
bbrgwb is impossible.
In this example, 6 of the eight designs are possible with the available towel patterns.

To get into the onsen as soon as possible, consult your list of towel patterns and desired designs carefully. How many designs are possible?


*/

#include <string>
#include <vector>

bool isPossibleToProduce(const std::string& design, const std::vector<std::string>& towel_patterns) {
    size_t n = design.size();
    std::vector<bool> dp(n + 1, false);
    dp[0] = true; // Empty string can always be formed

    for (size_t i = 1; i <= n; ++i) {
        for (const std::string& pattern : towel_patterns) {
            size_t pat_len = pattern.size();
            if (pat_len > i) continue; // Pattern longer than current substring

            // Check if the pattern matches the substring ending at i
            if (design.compare(i - pat_len, pat_len, pattern) == 0) {
                if (dp[i - pat_len]) {
                    dp[i] = true;
                    break; // No need to check other patterns
                }
            }
        }
    }

    return dp[n];
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

	std::string towel_patterns_line = lines[0];
	std::vector<std::string> towel_patterns;
	std::stringstream ss(towel_patterns_line);
	std::string token;
	while (std::getline(ss, token, ','))
	{
		token.erase(0, token.find_first_not_of(" \t\r\n"));
		token.erase(token.find_last_not_of(" \t\r\n") + 1);
		towel_patterns.push_back(token);
	}

	int index = 2;

	std::vector<std::string> desired_designs;
	while (index < lines.size())
	{
		if (!lines[index].empty())
		{
			desired_designs.push_back(lines[index]);
		}
		++index;
	}

	int valid_designs = 0;
	for (const auto& design : desired_designs)
	{
		if (isPossibleToProduce(design, towel_patterns))
		{
			++valid_designs;
			std::cout << "Design " << design << " is possible" << std::endl;
		}
		else
		{
			std::cout << "Design " << design << " is impossible" << std::endl;
		}
	}

	std::cout << "Valid designs: " << valid_designs << std::endl;

	return 0;
}
