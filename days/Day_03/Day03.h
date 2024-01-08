#pragma once
#ifndef DAY03_H
#define DAY03_H

#include "../Day.h"

class Day03 : public Day
{
public:
   Day03(std::string fileName)
   {
      fileContents = Utils::ReadInput(fileName);
   }
   size_t part1() override;
   size_t part2() override;
   void display() override;
};

#endif // !DAY03_H