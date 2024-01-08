#pragma once
#ifndef DAY02_H
#define DAY02_H

#include "../Day.h"

class Day02 : public Day
{
public:
   Day02(std::string fileName)
   {
      fileContents = Utils::ReadInput(fileName);
   }
   size_t part1() override;
   size_t part2() override;
   void display() override;
};

#endif // !DAY01_H