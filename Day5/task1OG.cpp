#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <deque>

// Reads data.txt, pushing each line onto output
// param output: The output vector pushed onto
void readFile(std::deque<std::string>& output)
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

// Converts a str line to int
// param line: The whole line to perform string split
// param output: The integers from the wordList
void lineToInt(std::string& line, std::deque<long long>& output)
{
   std::vector<std::string> wordList = splitString(line, " ");
   for (size_t i = 0, listSize = wordList.size(); i < listSize; i++)
   {
      output.push_back(std::stoll(wordList[i]));
   }
}

size_t countUntilEmpty(const std::deque<std::string>& vec)
{
   int count = 0;
   for (const auto& item : vec)
   {
      if (item.empty())
      {
         break;
      }
      count++;
   }
   return count;
}

int main()
{
   // Moving through the document it should go
   // Read and discard text line
   // Read int line (syphon first digit) and get 1st range, delete the line
   // Check if any of previous category is in that range
   // If not move on
   // If we run into a "" line, then we stop, all items left get given their original placement, delete the line
   // Repeat

   // Storage
   int lowestLocation = 0;
   std::deque<std::string> fileContents;

   // Read in the file contents
   readFile(fileContents);

   // Have it be a two category system, reading in one category and the following.
   // The first category is then mapped onto the second producing the first category for the next interation
   // The categories are culled from the fileContents so it continuously reads from the top

   // Firstly we need to take the seeds cause they follow a different order
   // Split the string into halves
   // With the second half, remove first character
   // lineToInt
   std::vector<std::string> splitLine = splitString(fileContents[0], ":");
   splitLine[1] = splitLine[1].substr(1, splitLine[1].size());
   std::deque<long long> category1;
   lineToInt(splitLine[1], category1);
   for (size_t i = 0, seedsSize = category1.size(); i < seedsSize; i++)
   {
      std::cout << "Seed #" << i << " is " << category1[i] << "\n";
   }
   fileContents.pop_front();
   fileContents.pop_front();

   // This now handles the edge case of getting the seeds, making it category 1
   // While loop because it is unclear when the file will end, just keep mapping category 1 to category 2 until the filesize is 0
   while (true)
   {
      std::cout << "\nNew Category!\n" << fileContents[0] << "\n";
      fileContents.pop_front(); // Remove the text line
      // Now look at the next couple lines that have the ranges, deleting the lines after finished
      std::deque<long long> tempNewCategory1;
      for (size_t i = 0, length = countUntilEmpty(fileContents); i < length; i++)
      {
         std::deque<long long> rangeParams;
         lineToInt(fileContents[0], rangeParams);
         for (const auto& item : rangeParams)
         {
            std::cout << " Range: " << item;
         }

         std::pair<int, int> lowHighSource = { rangeParams[1], rangeParams[1] + rangeParams[2] - 1 };
         std::pair<int, int> lowHighDestin = { rangeParams[0], rangeParams[0] + rangeParams[2] - 1 };;


         // Loop over the first category to map to the ranges
         for (auto& item : category1)
         {
            // If the item is within the source range
            if (item >= lowHighSource.first && item <= lowHighSource.second)
            {
               // Map its value onto the destination range
               // Calculate the difference between the value and the start of source
               int diff = item - rangeParams[1];
               int mappedValue = rangeParams[0] + diff;

               // Add it to temporary result vector
               tempNewCategory1.push_back(mappedValue);

               // Pop it off the original as it has been mapped
               category1.pop_front();
               continue;
            }
            // If we are at the last iteration and haven't break, then we need to take the value and place it into the temp map
            if (i == length - 1)
            {
               tempNewCategory1.push_back(item);
            }
         }
         fileContents.pop_front();
         std::cout << "\n";
      }
      if (fileContents.size() == 0)
      {
         category1 = tempNewCategory1;
         break;
      }
      fileContents.pop_front();
      for (const auto& item : tempNewCategory1)
      {
         std::cout << "New Value: " << item << "\n";
      }
      category1 = tempNewCategory1;
   }

   for (const auto& item : category1)
   {
      std::cout << "New Value: " << item << "\n";
   }
}
