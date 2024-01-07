#pragma once
#ifndef DAY01_H
#define DAY01_H

#include "../Day.h"

class Day01 : public Day
{
public:
	Day01(std::string fileName) {
		fileContents = Utils::readInput(fileName);
	}
	void part1() override;
	void part2() override;
};

#endif // !DAY01_H