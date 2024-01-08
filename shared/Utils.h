#pragma once

#include <vector>
#include <string>

typedef std::vector<std::string> fileOutputStr;
typedef std::vector<std::string> wordList;

namespace Utils
{
   /**
    * Reads a text file and returns its contents as a vector of strings.
    *
    * Each line of the file is read and stored as a separate string. If the file
    * cannot be opened, an empty vector is returned.
    *
    * \param   fileName       The name and path of the file to read.
    * \return  fileOutputStr  A vector of strings with each string representing a line from the file;
    *                         an empty vector is returned if the file is inaccessible.
    */
   fileOutputStr ReadInput(std::string& fileName);

   /**
    * Splits a given string by the passed delimeter, by hand method without std::getline
    *
    * \param   stringToSplit  The string to be split
    * \param   delim          The delimeter to split by
    * \return  wordList       A vector of strings with each string being a word found when split
    */
   wordList SplitStringPos(std::string stringToSplit, std::string& delim);

   /**
    * Splits a given string by the passed delimeter, using std::getline method
    *
    * \param   stringToSplit The string to be split
    * \param   delim         The delimeter to split by
    * \return  wordList     A vector of strings with each string being a word found when split
    */
   wordList SplitString(std::string& stringToSplit, char& delim);
}