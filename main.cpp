#include <iostream>

#include "days/Day_01/Day01.h"
#include "days/Day_02/Day02.h"
#include <filesystem>

int main()
{
   Day01 day01("inputs/day01.txt");
   day01.display();
   Day02 day02("inputs/day02.txt");
   day02.display();
}