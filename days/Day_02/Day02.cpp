#include "Day02.h"
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <fstream>
#include "../../shared/Utils.h"
using RGB = struct
{
   int red;
   int green;
   int blue;
};

size_t Day02::part1()
{
   // Bag of marbles defined in hpp

   std::vector<int> possibleGameIDs;

   for (const auto& game : fileContents )
   {
      bool hasGameFailed = false;

      // Example game line - Game 1: 12 red, 2 green, 5 blue; 9 red, 6 green, 4 blue
      // ':' Separates the Game Info from the draws
      // ';' Separates the different draws
      // ' ' Separates the in between
      auto gameInfo = Utils::SplitString(game, ':'); 

      int gameID = std::stoi(Utils::SplitString(gameInfo[0], ' ').back());

      auto gameDraws = Utils::SplitString(gameInfo[1], ';');

      for (const auto& draw : gameDraws )
      {
         RGB tallyRGB = { 0,0,0 };

         auto colours = Utils::SplitString(draw, ',');
         for ( auto& colour : colours )
         {
            colour = colour.substr(1, colour.back());

            auto keyValue = Utils::SplitString(colour, ' ');
            if ( keyValue[1] == "red" )
            {
               tallyRGB.red += std::stoi(keyValue[0]);
            }
            else if ( keyValue[1] == "green" )
            {
               tallyRGB.green += std::stoi(keyValue[0]);
            }
            else if ( keyValue[1] == "blue" )
            {
               tallyRGB.blue += std::stoi(keyValue[0]);
            }
         }

         if ( tallyRGB.red <= bag["red"] && tallyRGB.green <= bag["green"] && tallyRGB.blue <= bag["blue"] )
         {
            //std::cout << "PASSED\n\n";
         }
         else
         {
            //std::cout << "FAILED\n\n";
            hasGameFailed = true;
         }
      }

      if ( hasGameFailed == false )
      {
         possibleGameIDs.push_back(gameID);
      }
   }

   size_t finalSum = 0;
   for ( auto& gameID : possibleGameIDs )
   {
      finalSum += gameID;
   }

   return finalSum;
}

size_t Day02::part2()
{
   // Bag of marbles defined in hpp

   std::vector<int> possibleGameIDs;
   size_t finalPower = 0;

   for (const auto& game : fileContents )
   {
      RGB highestTallyRGB = { 0,0,0 };
      bool hasGameFailed = false;

      // Example game line - Game 1: 12 red, 2 green, 5 blue; 9 red, 6 green, 4 blue
      // ':' Separates the Game Info from the draws
      // ';' Separates the different draws
      // ' ' Separates the in between
      auto gameInfo = Utils::SplitString(game, ':');

      int gameID = std::stoi(Utils::SplitString(gameInfo[0], ' ').back());

      auto gameDraws = Utils::SplitString(gameInfo[1], ';');

      for (const auto& draw : gameDraws )
      {
         RGB tallyRGB = { 0,0,0 };
         
         auto colours = Utils::SplitString(draw, ',');
         for ( auto& colour : colours )
         {
            colour = colour.substr(1, colour.back());

            auto keyValue = Utils::SplitString(colour, ' ');
            if ( keyValue[1] == "red" )
            {
               auto value = std::stoi(keyValue[0]);
               if ( value > highestTallyRGB.red )
               {
                  highestTallyRGB.red = value;
               }
               tallyRGB.red += std::stoi(keyValue[0]);
            }
            else if ( keyValue[1] == "green" )
            {
               auto value = std::stoi(keyValue[0]);
               if ( value > highestTallyRGB.green )
               {
                  highestTallyRGB.green = value;
               }
               tallyRGB.green += std::stoi(keyValue[0]);
            }
            else if ( keyValue[1] == "blue" )
            {
               auto value = std::stoi(keyValue[0]);
               if ( value > highestTallyRGB.blue )
               {
                  highestTallyRGB.blue = value;
               }
               tallyRGB.blue += std::stoi(keyValue[0]);
            }
         }
         
      }
      finalPower += highestTallyRGB.red * highestTallyRGB.green * highestTallyRGB.blue;
   }

   return finalPower;
}

void Day02::display()
{
   std::cout << "\n--- Day 2: Cube Conundrum ---\n";
   std::cout << "Part 1: What is the sum of the IDs of those games? " << part1() << "\n";
   std::cout << "Part 2: What is the sum of the power of these sets? " << part2() << "\n";
}
