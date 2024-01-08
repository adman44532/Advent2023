#pragma once
#ifndef DAY03_H
#define DAY03_H

#include "../Day.h"

class Day03 : public Day
{
public:
   Day03(std::string fileName)
   {
      fileContents = Utils::readInput(fileName);
   }
   void part1() override;
   void part2() override;
};

#endif // !DAY03_H