#pragma once
#ifndef DAY05_H
#define DAY05_H

#include "../Day.h"

class Day05 : public Day
{
public:
   Day05(std::string fileName)
   {
      fileContents = Utils::readInput(fileName);
   }
   void part1() override;
   void part2() override;
};

#endif // !DAY05_H