#pragma once
#ifndef DAY05_H
#define DAY05_H

#include "../Day.h"

class Day05 : public Day
{
public:
   Day05(std::string fileName)
   {
      fileContents = Utils::ReadInput(fileName);
   }
   size_t part1() override;
   size_t part2() override;
   void display() override;
};

#endif // !DAY05_H