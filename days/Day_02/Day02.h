#pragma once
#ifndef DAY02_H
#define DAY02_H

#include "../Day.h"

class Day02 : public Day
{
public:
   Day02(std::string fileName)
   {
      fileContents = Utils::readInput(fileName);
   }
   void part1() override;
   void part2() override;
};

#endif // !DAY01_H