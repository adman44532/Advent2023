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
std::vector<std::string> splitString(std::string stringToSplit, const std::string delim)
{
   std::vector<std::string> wordList;
   size_t pos = 0;
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

// Removes trailing white spaces from the beginning and end of string where applicable
// param stringToTrim: Modifies the given string
void trimString(std::string& stringToTrim)
{
   // Check the starting value for space
   if (stringToTrim[0] == ' ')
   {
      stringToTrim = stringToTrim.substr(1, stringToTrim.size());
   }
   // Check the last value for space
   if (stringToTrim.back() == ' ')
   {
      stringToTrim.pop_back();
   }
}

// For the list of cards, compute the number of matches between the winning numbers and received numbers
// param cardList: Reference to the list of cards in the file
// param output: Reference to the output vector for the number of matches
void computeNumberOfMatches(const std::vector<std::string>& cardList, std::vector<int> &output)
{
   // Compute the number of matches for each card, a series of string splits to get the right information
   for (const auto& card : cardList)
   {
      std::set<int> winningNumbers;
      std::set<int> yourNumbers;

      const std::vector<std::string> cardInfo = splitString(card, ":");

      // Get the Card ID
      const int cardID = std::stoi(splitString(cardInfo[0], " ").back());

      // Get the Two sets of data from the card
      std::vector<std::string> cardData = splitString(cardInfo[1], "|");

      // GET WINNING NUMBERS
      trimString(cardData[0]);
      std::vector<std::string> dataStr = splitString(cardData[0], " ");
      // Convert each number to int and add to set
      for (const auto& valueStr : dataStr)
      {
         int value = std::stoi(valueStr);
         winningNumbers.insert(value);
      }

      // GET YOUR NUMBERS
      trimString(cardData[1]);
      dataStr = splitString(cardData[1], " ");
      // Convert each number to int and add to set
      for (const auto& valueStr : dataStr)
      {
         int value = std::stoi(valueStr);
         yourNumbers.insert(value);
      }

      // Now that we have the two sets of numbers, we perform set_intersection
      std::set<int> intersecting;
      std::set_intersection(winningNumbers.begin(), winningNumbers.end(), yourNumbers.begin(), yourNumbers.end(), std::inserter(intersecting, intersecting.begin()));

      output.push_back(intersecting.size());
   }
}

int main()
{
   std::vector<std::string> cardList;
   std::vector<int> numOfMatches;

   readFile(cardList);

   computeNumberOfMatches(cardList, numOfMatches);

   // For the length of the # of cards, create a tally list to have a count of each card (and add onto next), fill the vector with 1s
   std::vector<int> tallies(numOfMatches.size(), 1);

   // Loop through the tallies to compute its copies
   for (int i = 0, talliesSize = tallies.size(); i < talliesSize; i++)
   {
      // Loop down for x number cards for x matches below the current value
      for (size_t j = 1, loopSize = numOfMatches[i]; j <= loopSize; j++)
      {
         // Adding the current amount of tallies to the following x cards below
         tallies[i + j] += tallies[i];
      }
   }

   // Run through the tallies summing all the values
   int totalCards = 0;
   for (const auto& tally : tallies)
   {
      totalCards += tally;
   }
   
   // Print the final result
   std::cout << "The total number of cards is... " << totalCards << "\n";
}