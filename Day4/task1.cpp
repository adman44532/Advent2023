/*
#include <iostream>
#include <cmath>
#include <vector>
#include <set>
#include <fstream>
#include <string>
#include <algorithm>

// Reads a file, adding its contents to a vector given
// param output: the vector to which items are added (modifies)
void readFile(std::vector<std::string>& output)
{
   std::ifstream file("data.txt");

   if (file.is_open())
   {
      while (file.good())
      {
         std::string line;
         std::getline(file, line);
         output.push_back(line);
      }
   }
}

// Takes in a string and splits it into a vector by the given delimeter
// param stringToSplit: Copy of input string as it gets erased
// param delim: The delimeter character
// return : Vector of strings for each splitted entry
std::vector<std::string> splitString(std::string stringToSplit, std::string delim)
{
   std::vector<std::string> wordList;
   int pos = 0;
   const int delimSize = delim.size();

   // Loop while there are still characters in possibly split, stringToSplit's size changes each iteration
   while (pos < stringToSplit.size())
   {
      if (stringToSplit[0] == delim[0])
      {
         stringToSplit.erase(0, 1);
      }
      // Get the position of the next delimeter
      pos = stringToSplit.find(delim);
      // Everything up to the delimeter is now a word, push it onto the return vector
      wordList.push_back(stringToSplit.substr(0, pos));
      // Erase the characters up to and includeing the delimeter.
      stringToSplit.erase(0, pos + delimSize);
   }

   // For strings that are reduced to below the position, we add the rest of the string as the final value
   if (wordList.back() != stringToSplit)
   {
      wordList.push_back(stringToSplit);
   }

   return wordList;
}

int main()
{
   // Store set A (Winning Numbers)
   std::set<int> winningNumbers;
   // Store set B (Your Numbers)
   std::set<int> yourNumbers;

   int finalSum = 0;

   std::vector<std::string> fileContents;

   // Read in the file
   readFile(fileContents);

   for (size_t i = 0, fileSize = fileContents.size(); i < fileSize; i++)
   {
      winningNumbers.clear();
      yourNumbers.clear();
      std::cout << "\nNew game: \n" << fileContents[i] << "\n";
      // Split the string to remove "Card #:"
      std::vector<std::string> cards = splitString(fileContents[i], ":");

      std::vector<std::string> twoSets = splitString(cards[1], "|");

      // GET WINNING NUMBERS
      // In the first set, we need to remove the trailing spaces
      twoSets[0] = twoSets[0].substr(1, twoSets[0].back());
      twoSets[0].pop_back();
      std::cout << "Uncut Winning Numbers: " << twoSets[0] << "\n";
      std::vector<std::string> winningNumStr = splitString(twoSets[0], " ");
      // Convert each number to int and add to set
      for (size_t j = 0, numSize = winningNumStr.size(); j < numSize; j++)
      {
         int value = std::stoi(winningNumStr[j]);
         winningNumbers.insert(value);
         std::cout << value << "\n";
      }

      // GET YOUR NUMBERS
      twoSets[1] = twoSets[1].substr(1, twoSets[1].size()); // No end space
      std::cout << "Uncut Your Numbers: " << twoSets[1] << "\n";
      std::vector<std::string> yourNumStr = splitString(twoSets[1], " ");
      // Convert each number to int and add to set
      for (size_t j = 0, numSize = yourNumStr.size(); j < numSize; j++)
      {
         int value = std::stoi(yourNumStr[j]);
         yourNumbers.insert(value);
         std::cout << value << "\n";
      }
      std::cout << "Here we go: ";
      // Now that we have the two sets of numbers, we perform set_intersection
      std::set<int> intersecting;
      std::set_intersection(winningNumbers.begin(), winningNumbers.end(), yourNumbers.begin(), yourNumbers.end(), std::inserter(intersecting, intersecting.begin()));
      for (int const& value : intersecting)
      {
         std::cout << value << ' ';
      }
      std::cout << "\n";

      // Allocate the points
      if (intersecting.size() != 0)
      {
         int points = 1;
         for (size_t j = 1, interSize = intersecting.size(); j < interSize; j++)
         {
            points *= 2;
         }
         finalSum += points;
      }
   }
   std::cout << "All that work is... " << finalSum;

   // For each line in the file
      // Split the string
         // Extract the winning Numbers
         // Extract the your numbers
         // Intersect the two sets
      // Allocate the points based on intersection count

   // Sum all the points
}
*/