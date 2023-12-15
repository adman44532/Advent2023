#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <map>

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

std::map<char, int> getCharFrequenies(const std::string& hand)
{
   std::map<char, int> freqMap;
   for (const char& c : hand)
   {
      freqMap[c]++;
   }
   return freqMap;
}

int pokerCharToInt(const char& value)
{
   int pokerValue = 0;
   // If the value is not true, then we have a letter
   if (isdigit(value) == 0)
   {
      // Therefore we need to check against the different poker cards to assign the value of it
      if (value == 'T')
      {
         pokerValue = 10;
      }
      else if (value == 'J')
      {
         pokerValue = 11;
      }
      else if (value == 'Q')
      {
         pokerValue = 12;
      }
      else if (value == 'K')
      {
         pokerValue = 13;
      }
      else if (value == 'A')
      {
         pokerValue = 14;
      }
   }
   // We have a number
   else
   {
      pokerValue = value - '0';
   }
   return pokerValue;
}

int main()
{
   std::vector<std::string> fileContents;
   std::vector<std::pair<std::string, int>> hands;

   readFile(fileContents);

   // Break down the file into its hands for sorting
   for (const auto& line : fileContents)
   {
      std::vector<std::string> handData = splitString(line, " ");
      int bid = std::stoi(handData[1]);
      hands.push_back({ handData[0], bid });
   }

   // Firstly they need to be sorted by their type, requiring to know the frequency of each character
   std::vector<std::vector<std::pair<std::string, int>>> typeSort(6, std::vector<std::pair<std::string, int>>());

   for (const auto& hand : hands)
   {
      //std::cout << "Hand: " << hand.first << " and bid " << hand.second << "\n";
      std::map<char, int> freq = getCharFrequenies(hand.first);
      //for (const auto& pair : freq)
      //{
      //   std::cout << "Item: " << pair.first << ", Frequency: " << pair.second << "\n";
      //}

      // Detmine the type from frequency
      int largestFrequency = 0;
      int secondLargestFreq = 0;
      for (const auto& f : freq)
      {
         if (f.second > largestFrequency)
         {
            largestFrequency = f.second;
         }
         else if (f.second > secondLargestFreq)
         {
            secondLargestFreq = f.second;
         }
      }

      // None of a kind
      if (largestFrequency == 0)
      {
         typeSort[0].push_back(hand);
      }
      // None of a kind
      else if (largestFrequency == 1)
      {
         typeSort[1].push_back(hand);
      }
      // None of a kind
      else if (largestFrequency == 2)
      {
         typeSort[2].push_back(hand);
      }
      // None of a kind
      else if (largestFrequency == 3)
      {
         typeSort[3].push_back(hand);
      }
      // None of a kind
      else if (largestFrequency == 3 && secondLargestFreq == 2)
      {
         typeSort[4].push_back(hand);
      }
      // None of a kind
      else if (largestFrequency == 4)
      {
         typeSort[5].push_back(hand);
      }
      // None of a kind
      else if (largestFrequency == 5)
      {
         typeSort[6].push_back(hand);
      }
   }

   // Print the Types
   int index = 0;
   //for (const auto& type : typeSort)
   //{
   //   std::cout << "Type: " << index << "\n";
   //   for (const auto& hand : type)
   //   {
   //      std::cout << "Hand: " << hand.first << "\n";
   //   }
   //   std::cout << "\n";
   //   index++;
   //}

   // Now they are sorted into their types, you need to sort the types by the highest and earlier character
   for (auto& type: typeSort)
   {
      // For each type, get the current hand and the next hand, run through their chars, if the current hand is greater than the next, swap
      if (!type.empty())
      {
         for (size_t j = 0, typeSize = type.size() - 1; j < typeSize; j++)
         {

            bool isHigher = false;
            for (size_t k = 0, handSize = type[j].first.size(); k < handSize; k++)
            {
               if (isHigher == false)
               {
                  // The type contains a list of hands, so get the current and next hands, giving the values of the char at position in string
                  int prevHand1Position;
                  int prevHand2Position;
                  if (k == 0)
                  {
                     prevHand1Position = pokerCharToInt(type[j].first[0]);
                     prevHand2Position = pokerCharToInt(type[j + 1].first[0]);
                  }
                  else
                  {
                     prevHand1Position = pokerCharToInt(type[j].first[k - 1]);
                     prevHand2Position = pokerCharToInt(type[j + 1].first[k - 1]);
                  }
                  int hand1Position = pokerCharToInt(type[j].first[k]);
                  int hand2Position = pokerCharToInt(type[j + 1].first[k]);

                  // If the current hand has a value greater than the 2nd, then we swap the values
                  if (prevHand1Position == prevHand2Position && hand1Position > hand2Position)
                  {
                     auto tempHand = type[j];
                     type[j] = type[j + 1];
                     type[j + 1] = tempHand;
                     isHigher = true;
                  }
               }
            }
         }
      }
   }

   // Print the Types
   index = 0;
   for (const auto& type : typeSort)
   {
      std::cout << "Type: " << index << "\n";
      for (const auto& hand : type)
      {
         std::cout << "Hand: " << hand.first << "\n";
      }
      std::cout << "\n";
      index++;
   }

   std::vector<std::pair<std::string, int>> handsSorted;
   // A bit unessesary but place all the types back into the list of hands
   for (const auto& type : typeSort)
   {
      for (const auto& hand : type)
      {
         handsSorted.push_back(hand);
      }
   }

   int finalWinnings = 0;
   for (size_t i = 0, handSize = handsSorted.size(); i < handSize; i++)
   {
      finalWinnings += handsSorted[i].second * (i + 1);
      //std::cout << "F: " << handsSorted[i].first << " S: " << handsSorted[i].second << " R: " << i + 1 << " W: " << handsSorted[i].second * (i + 1) << " T: " << finalWinnings << "\n";
   }

   std::cout << "The final winnings are: $" << finalWinnings << "\n";
}

