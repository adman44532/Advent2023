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

// Removes spaces from the given line
// param line: Line to remove spaces from (modifies)
void spaceRemover(std::string& line)
{
   // Erase function can take in a starting position (inclusive) and the ending position (exclusive)
   // The remove function doesn't actually "remove" the items but moves them to the end, it searches in a range (begin->end) and moves the specified character ' '
   line.erase(std::remove(line.begin(), line.end(), ' '), line.end());
}

// Converts a str line to int
// param line: The whole line to perform string split
// param output: The integers from the wordList
void lineToInt(std::string& line, long long& output)
{
   spaceRemover(line);
   if (!line.empty())
   {
      output = std::stoll(line);
   }
}

int main()
{
   std::vector<std::string> fileContents;
   long long raceTime;
   long long recordDistance;

   readFile(fileContents);

   // Get the times
   std::vector<std::string> timesInfo = splitString(fileContents[0], ":");
   lineToInt(timesInfo[1], raceTime);

   // Get the distances
   std::vector<std::string> distanceInfo = splitString(fileContents[1], ":");
   lineToInt(distanceInfo[1], recordDistance);

   // Count the number of ways to beat the race, loop over each milisecond
   long long waysToBeatRecord = 0;
   for (size_t j = 0; j < raceTime; j++)
   {
      long long speed = j;
      long long timeLeft = raceTime - j;
      long long distanceMade = speed * timeLeft;
      if (distanceMade > recordDistance)
      {
         waysToBeatRecord++;
      }
   }

   std::cout << "The number of ways is: " << waysToBeatRecord << "\n";
}