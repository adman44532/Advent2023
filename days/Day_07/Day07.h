#pragma once
#ifndef DAY07_H
#define DAY07_H

#include "../Day.h"

class Day07 : public Day
{
public:
	Day07(std::string fileName) {
		fileContents = Utils::readInput(fileName);
	}
	void part1() override;
	void part2() override;
};

#endif // !DAY07_H