#pragma once
#ifndef DAY06_H
#define DAY06_H

#include "../Day.h"

class Day06 : public Day
{
public:
   Day06(std::string fileName)
   {
      fileContents = Utils::readInput(fileName);
   }
   void part1() override;
   void part2() override;
};

#endif // !DAY06_H