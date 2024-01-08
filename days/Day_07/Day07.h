#pragma once
#ifndef DAY07_H
#define DAY07_H

#include "../Day.h"

class Day07 : public Day
{
public:
   Day07(std::string fileName)
   {
      fileContents = Utils::ReadInput(fileName);
   }
   size_t part1() override;
   size_t part2() override;
   void display() override;
};

#endif // !DAY07_H