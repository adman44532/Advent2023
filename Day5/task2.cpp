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
void lineToInt(std::string& line, std::vector<long long>& output)
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

void mapItem(std::vector<std::pair<std::pair<long long, long long>, std::pair<long long, long long>>> map, long long& seed)
{
   // Run through the ranges within the map
   bool isMapped = false;
   for (const auto& range : map)
   {
      // Check if the seed is within the range
      if (isMapped == false)
      {
         if (seed >= range.first.first && seed <= range.first.second)
         {
            int diff = seed - range.first.first;
            seed = range.second.first + diff;
            isMapped = true;
         }
      }
   }
   // The value will remain unchanged if the item is not within the source range, therefore automatically 1:1 maps
}

int main()
{
   std::deque<std::string> fileContents;

   // Read in the file contents
   readFile(fileContents);

   // Firstly get the seeds from the first line
   std::vector<long long> seeds;
   std::vector<std::string> seedsStrRaw;
   seedsStrRaw = splitString(fileContents[0], ":");
   std::vector<std::string> seedsStr;
   seedsStr = splitString(seedsStrRaw[1], " ");
   for (const auto& str : seedsStr)
   {
      seeds.push_back(std::stoll(str));
   }
   // Place file at start of maps
   fileContents.pop_front();
   fileContents.pop_front();

   

   // Now with a list of seeds, we can now form a list of maps
   // All the maps (Contains multiple maps)
   // -> Single Map (Contains multiple ranges)
   //    -> Source range (Start and End) as pair         <| Makes a range
   //    -> Destinartion range (Start and End) as pair   <|
   std::vector<std::vector<std::pair<std::pair<long long, long long>, std::pair<long long, long long>>>> maps;
   std::vector<std::pair<std::pair<long long, long long>, std::pair<long long, long long>>> tempMap;
   for (int i = 1, fileContentsSize = fileContents.size(); i < fileContentsSize; i++)
   {
      // If the line is empty when we are at the end of the ranges, adding to the map list
      if (fileContents[i].empty())
      {
      }
      // If the first character is not a digit then we want to count it as a new map
      else if (isdigit(fileContents[i][0]) == 0 || i == fileContentsSize - 1)
      {
         maps.push_back(tempMap);
         tempMap.clear(); // Might be unessesary
      }
      // Then we know any other values is a range to be added to the tempMap
      else
      {
         std::pair<long long, long long> tempSource;
         std::pair<long long, long long> tempDest;
         // Split the line into the 3 parameters for a range
         std::vector<long long> rangeParams;
         lineToInt(fileContents[i], rangeParams);
         // Assign the source and destination pairs their starting and ending values
         tempSource = { rangeParams[1], rangeParams[1] + rangeParams[2] - 1 };
         tempDest = { rangeParams[0], rangeParams[0] + rangeParams[2] - 1 };
         std::pair<std::pair<long long, long long>, std::pair<long long, long long>> range = { tempSource, tempDest };
         tempMap.push_back(range);
         // We now have placed a range in a map onto the tempMap
      }
   }

   // Print a list of all the maps
   /*
   int index = 0;
   for (const auto& map : maps)
   {
      std::cout << "\nMap #" << index << "\n";
      for (const auto& range : map)
      {
         std::cout << "Range:\n";
         std::cout << "Source Start: " << range.first.first << "\n";
         std::cout << "Source End: " << range.first.second << "\n";
         std::cout << "Destination Start: " << range.second.first << "\n";
         std::cout << "Destination End: " << range.second.second << "\n\n";
      }
      index++;
   }
   */
   // Now we place the seeds and their lengths into another pair that links its inital value to itself
   std::pair<long long, long long> lowestPair;
   for (size_t i = 0, seedsSize = seeds.size(); i < seedsSize; i += 2)
   {
      std::vector<std::pair<long long, long long>> seedsPairs;
      // Get a batch of seeds
      long long length = seeds[i + 1];
      for (size_t j = 0, copyLength = seeds[i + 1]; j < copyLength; j++)
      {
         seedsPairs.push_back({ seeds[i], seeds[i] + j });
      }

      // With a list of maps we can map each seed individually through the maps
      for (auto& seed : seedsPairs)
      {
         long long ogSeed = seed.second;
         for (const auto& map : maps)
         {
            mapItem(map, seed.second); // Constantly alter the seed through all the maps
         }
         //std::cout << "Seed #" << ogSeed << " has been mapped to location: " << seed.second << "\n";
      }

      // We now have location values, find the lowest value in the vector
      // If we are on the first iteration, we need to set the lowestPair, if not we ignore cause its already set
      if (i == 0)
      {
         lowestPair = seedsPairs[0];
      }
      for (const auto& location : seedsPairs)
      {
         if (location.second < lowestPair.second)
         {
            lowestPair = location;
         }
      }

      // Clear pairs
      seedsPairs.clear();
      std::cout << "\n";
   }

   

   std::cout << "The lowest location is: " << lowestPair.first << " with a value of " << lowestPair.second << "\n";
}