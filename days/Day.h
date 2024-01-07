#pragma once

#include <vector>
#include <string>
#include <iostream>
#include "../shared/Utils.h"

class Day
{
public:
	virtual void part1() = 0;
	virtual void part2() = 0;
	void solve() {
		part1(); part2();
	}
	void dumpContents() {
		std::cout << "Dumping...\n";
		for (auto line : fileContents) {
			std::cout << line << std::endl;
		}
	}

protected:
	std::vector<std::string> fileContents;
};