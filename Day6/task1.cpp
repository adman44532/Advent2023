#include <iostream>
#include <fstream>
#include <vector>
#include <string>

// Reads data.txt, pushing each line onto output
// param output: The output vector pushed onto
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

// Removes trailing white spaces from the beginning and end of string where applicable
// param stringToTrim: Modifies the given string
void trimString(std::string& stringToTrim)
{
   if (!stringToTrim.empty())
   {
      // Check the starting value for space
      if (stringToTrim[0] == ' ' && !stringToTrim.empty())
      {
         stringToTrim = stringToTrim.substr(1, stringToTrim.size());
      }
      // Check the last value for space

      if (stringToTrim.back() == ' ')
      {
         stringToTrim.pop_back();
      }
      if (stringToTrim[0] == ' ' || stringToTrim.back() == ' ')
      {
         trimString(stringToTrim);
      }
   }
}

// Converts a str line to int
// param line: The whole line to perform string split
// param output: The integers from the wordList
void lineToInt(std::string& line, std::vector<int>& output)
{
   std::vector<std::string> wordList = splitString(line, " ");
   for (auto& word : wordList)
   {
      trimString(word);
      if (!word.empty())
      {
         output.push_back(std::stoll(word));
      }
   }
}

int main()
{
   std::vector<std::string> fileContents;
   std::vector<int> times;
   std::vector<int> distances;

   readFile(fileContents);

   // Get the times
   std::vector<std::string> timesInfo = splitString(fileContents[0], ":");
   lineToInt(timesInfo[1], times);

   // Get the distances
   std::vector<std::string> distanceInfo = splitString(fileContents[1], ":");
   lineToInt(distanceInfo[1], distances);
   
   std::vector<int> waysToBeat;
   // Looping over the times will loop over the races
   for (size_t i = 0, timeSize = times.size(); i < timeSize; i++) 
   {
      // Count the number of ways to beat the race, loop over each milisecond
      int waysToBeatRecord = 0;
      for (size_t j = 0; j < times[i]; j++)
      {
         int speed = j;
         int timeLeft = times[i] - j;
         int distanceMade = speed * timeLeft;
         if (distanceMade > distances[i])
         {
            waysToBeatRecord++;
         }
      }
      if (waysToBeatRecord > 0)
      {
         waysToBeat.push_back(waysToBeatRecord);
      }
   }

   int total = waysToBeat[0];
   for (size_t i = 1, waySize = waysToBeat.size(); i < waySize; i++)
   {
      total *= waysToBeat[i];
   }

   std::cout << "The number of ways is: " << total << "\n";
}