#pragma once
#ifndef DAY04_H
#define DAY04_H

#include "../Day.h"

class Day04 : public Day
{
public:
   Day04(std::string fileName)
   {
      fileContents = Utils::ReadInput(fileName);
   }
   size_t part1() override;
   size_t part2() override;
   void display() override;
};

#endif // !DAY04_H