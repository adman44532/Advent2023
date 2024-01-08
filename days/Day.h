#pragma once

#include <vector>
#include <string>
#include <iostream>
#include "../shared/Utils.h"

class Day
{
public:
   // Calculates the answer for Part 1 of the puzzle
   virtual size_t part1() = 0;
   // Calculates the answer for Part 2 of the puzzle
   virtual size_t part2() = 0;
   // Displays the answers for Part 1 and Part 2 into the console
   virtual void display() = 0;
   // Shows the contents of the file given to the object
   void dumpContents()
   {
      std::cout << "Dumping...\n";
      for ( auto line : fileContents )
      {
         std::cout << line << std::endl;
      }
   }

protected:
   std::vector<std::string> fileContents;
};