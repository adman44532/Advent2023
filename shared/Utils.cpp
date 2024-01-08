#include "Utils.h"
#include "fstream"
#include <iostream>
#include <sstream>

fileOutputStr Utils::ReadInput(std::string& fileName)
{
   fileOutputStr output;
   std::ifstream file(fileName);

   if ( file.is_open() )
   {
      while ( file.good() )
      {
         std::string line;
         std::getline(file, line);
         output.push_back(line);
      }
   }
   else
   {
      std::cout << "Unable to open file: " << fileName << std::endl;
   }
   file.close();
   return output;
}

wordList Utils::SplitStringPos(std::string stringToSplit, std::string& delim)
{
   wordList words;
   size_t pos = 0;
   const size_t delimSize = delim.size();

   // Loop while there are still characters in possibly split, stringToSplit's size changes each iteration
   while ( pos < stringToSplit.size() )
   {
      if ( stringToSplit[0] == delim[0] )
      {
         stringToSplit.erase(0, 1);
      }
      // Get the position of the next delimeter
      pos = stringToSplit.find(delim);
      // Everything up to the delimeter is now a word, push it onto the return vector
      words.push_back(stringToSplit.substr(0, pos));
      // Erase the characters up to and includeing the delimeter.
      stringToSplit.erase(0, pos + delimSize);
   }

   // For strings that are reduced to below the position, we add the rest of the string as the final value
   if ( words.back() != stringToSplit )
   {
      words.push_back(stringToSplit);
   }

   return words;
}

wordList Utils::SplitString(std::string& stringToSplit, char& delim)
{
   wordList words;
   std::string temp;
   std::stringstream ss(stringToSplit);

   while ( std::getline(ss, temp, delim) )
   {
      words.push_back(temp);
   }

   return words;
}