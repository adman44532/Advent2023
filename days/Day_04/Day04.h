#pragma once
#ifndef DAY04_H
#define DAY04_H

#include "../Day.h"

class Day04 : public Day
{
public:
   Day04(std::string fileName)
   {
      fileContents = Utils::readInput(fileName);
   }
   void part1() override;
   void part2() override;
};

#endif // !DAY04_H