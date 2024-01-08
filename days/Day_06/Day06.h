#pragma once
#ifndef DAY06_H
#define DAY06_H

#include "../Day.h"

class Day06 : public Day
{
public:
   Day06(std::string fileName)
   {
      fileContents = Utils::ReadInput(fileName);
   }
   size_t part1() override;
   size_t part2() override;
   void display() override;
};

#endif // !DAY06_H