#include <iostream>
#include <iterator>
#include <string>
#include <regex>
#include <sstream>

#include "Rational.h"

#define RATIONAL_OP(r1, r2, op) \
	std::cout << r1 << " " << #op << " " << r2 << " = " << r1 op r2 << std::endl;

void process(std::istream& in, bool echoInput)
{
	std::regex inputRegex("^(-?\\d+)/(\\d+)\\s+(-?\\d+)/(\\d+)$");

	while (in)
	{
		std::string line;
		std::getline(in, line);

		if (echoInput)
		{
			std::cout << line << std::endl;
		}

		if (line.empty())
		{
			continue;
		}

		auto inputBegin =
			std::sregex_iterator(line.begin(), line.end(), inputRegex);
		auto inputEnd = std::sregex_iterator();
		if (std::distance(inputBegin, inputEnd) != 1)
		{
			throw std::runtime_error("Bad input line");
		}
		std::smatch match = *inputBegin;

		auto conv = [&match](int start)
		{
			int n = std::stoi(match[start].str());
			int d = std::stoi(match[start + 1].str());
			if (d <= 0)
			{
				throw std::runtime_error("Bad denominator");
			}
			return Rational(n, d);
		};

		const auto r1 = conv(1);
		const auto r2 = conv(3);

		RATIONAL_OP(r1, r2, +);
		RATIONAL_OP(r1, r2, -);
		RATIONAL_OP(r1, r2, *);
		RATIONAL_OP(r1, r2, / );
	}
}

void test()
{
	auto input = "2/3 -4/2\n"
		"5/3 0/6\n"
		"1/4 31/6\n"
		"2/8 7/14\n"
		;
	std::istringstream in(input);
	process(in, true);
}

int main(int argc, char**argv)
{
	test();
	process(std::cin, false);

	return 0;
}