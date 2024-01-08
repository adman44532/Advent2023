#pragma once
#ifndef DAY01_H
#define DAY01_H

#include "../Day.h"

class Day01 : public Day
{
public:
   Day01(std::string fileName)
   {
      fileContents = Utils::ReadInput(fileName);
   }
   size_t part1() override;
   size_t part2() override;
   void display() override;
};

#endif // !DAY01_H