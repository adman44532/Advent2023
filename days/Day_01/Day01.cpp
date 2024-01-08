#include "Day01.h"
#include "../../shared/Utils.h"
#include <map>

void Day01::part1()
{
   int finalSum = 0;
   // For each line in the file
   for ( auto& line : fileContents )
   {
      // We store the first recorded number and last
      char firstNum = '\0';
      char lastNum = '\0';

      // We comb through the characters looking for digits
      for ( auto& c : line )
      {
         // If the char is a digit
         if ( isdigit(c) != 0 )
         {
            // If the first isn't set yet, we set it
            if ( firstNum == '\0' )
            {
               firstNum = c;
            }
            // Else we update the last number
            else
            {
               lastNum = c;
            }
         }
      }

      // Provide a safe check for if there is only one number in the line
      if ( lastNum == '\0' )
      {
         lastNum = firstNum;
      }

      std::string calibrationValueStr;
      calibrationValueStr.push_back(firstNum);
      calibrationValueStr.push_back(lastNum);

      finalSum += std::stoi(calibrationValueStr);
   }
   std::cout << "Day #1 Part #1: " << finalSum << "\n";
}

void Day01::part2()
{
   // This solution assumes that the input wouldn't contain the first 3 chars of any number word
   typedef std::map<std::string, char> wordNumMap;

   // Add the first 3 chars of each number word to the map
   wordNumMap wordList;
   wordList["one"] = '1';
   wordList["two"] = '2';
   wordList["thr"] = '3';
   wordList["fou"] = '4';
   wordList["fiv"] = '5';
   wordList["six"] = '6';
   wordList["sev"] = '7';
   wordList["eig"] = '8';
   wordList["nin"] = '9';
   int finalSum = 0;

   for ( auto& line : fileContents )
   {
      // We store the first recorded number and last
      char firstNum = '\0';
      char lastNum = '\0';

      // Create a sliding window that goes over the line looking for an element in the word list

      // Edge case the first value as a digit
      if ( isdigit(line[0]) != 0 )
      {
         firstNum = line[0];
      }

      for ( size_t i = 1, strSize = line.size() - 1; i < strSize; i++ )
      {
         std::string windowStr = line.substr(i - 1, 3);
         // First we check if the digit we are on is a number
         if ( isdigit(windowStr[1]) != 0 )
         {
            if ( firstNum == '\0' )
            {
               firstNum = windowStr[1];
            }
            else
            {
               lastNum = windowStr[1];
            }
         }
         // If it isn't a number, we check if its a word
         else
         {
            for ( const auto& pair : wordList )
            {
               //std::cout << "Windows: " << windowStr << " Word: " << pair.first << " Compared: " << (windowStr == pair.first) << "\n";
               if ( windowStr == pair.first )
               {
                  //std::cout << "Hit!" << "\n";
                  // If we find a matching word, assign based on the value in the map
                  if ( firstNum == '\0' )
                  {
                     firstNum = pair.second;
                  }
                  else
                  {
                     lastNum = pair.second;
                  }
                  break; // Exit the loop if a match is found
               }
            }

            // If it isn't a number and isn't a word, then we continue
         }
      }

      // Edge case for last character being a digit
      if ( isdigit(line.back()) != 0 )
      {
         if ( firstNum == '\0' )
         {
            firstNum = line.back();
         }
         else
         {
            lastNum = line.back();
         }
      }

      // If there is only one number, we need to copy first into last.
      if ( lastNum == '\0' )
      {
         lastNum = firstNum;
      }
      std::string calibrationValueStr;
      calibrationValueStr.push_back(firstNum);
      calibrationValueStr.push_back(lastNum);

      finalSum += std::stoi(calibrationValueStr);
   }
   std::cout << "Day #1 Part #2: " << finalSum << "\n";
}
