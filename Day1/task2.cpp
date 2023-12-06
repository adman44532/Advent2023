#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>

// This method isn't great and makes a lot of assumptions about the data set, its lucky it even worked.

int main()
{
	// Data Storage
	std::vector<std::string> fileLines;
	std::vector<int> callibrationValues;
	std::map<std::string, char> wordList;
	wordList["one"] = '1';
	wordList["two"] = '2';
	wordList["thr"] = '3';
	wordList["fou"] = '4';
	wordList["fiv"] = '5';
	wordList["six"] = '6';
	wordList["sev"] = '7';
	wordList["eig"] = '8';
	wordList["nin"] = '9';
	int finalSum = 0;

	// Read in the file
	std::ifstream inputFile("data.txt");
	if (inputFile.is_open())
	{
		std::string lineContent;
		while (inputFile.good())
		{
			// Get the current line
			inputFile >> lineContent;
			//std::cout << lineContent << "\n";

			// Initalise the first and last numbers
			char firstNum = '\0';
			char lastNum = '\0';

			// First we need to check the first character to ensure it isn't a digit
			if (isdigit(lineContent[0]) != 0) 
			{
				firstNum = lineContent[0];
			}

			// Each worded number is unique in that the first 3 letters aren't the same, create a moving window checking for those values
			// This is a poor solution as it lets in a lot of errors if the data strays in the words/characters it contains.
			// The range of this loop is brought in to avoid over/under indexing
			for (int i = 1, strSize = lineContent.size() -1; i < strSize; i++)
			{
				std::string windowStr = lineContent.substr(i - 1, 3);
				// First we check if the digit we are on is a number
				if (isdigit(windowStr[1]) != 0) {
					if (firstNum == '\0')
					{
						firstNum = windowStr[1];
					}
					else
					{
						lastNum = windowStr[1];
					}
				}
				// If it isn't a number, we check if its a word
				else
				{
					for (const auto& pair : wordList) {
						//std::cout << "Windows: " << windowStr << " Word: " << pair.first << " Compared: " << (windowStr == pair.first) << "\n";
						if (windowStr == pair.first) {
							//std::cout << "Hit!" << "\n";
							// If we find a matching word, assign based on the value in the map
							if (firstNum == '\0') {
								firstNum = pair.second;
							}
							else {
								lastNum = pair.second;
							}
							break; // Exit the loop if a match is found
						}
					}

					// If it isn't a number and isn't a word, then we continue
				}
			}

			// After all that we check if the last character is a digit
			char lastChar = lineContent.back();
			if (isdigit(lastChar) != 0)
			{
				if (firstNum == '\0')
				{
					firstNum = lastChar;
				}
				else
				{
					lastNum = lastChar;
				}
			}

			// If there is only one number, we need to copy first into last.
			if (lastNum == '\0') {
				lastNum = firstNum;
			}

			// Once through the string, we add the two characters together
			std::string calibrationValueStr;
			calibrationValueStr.push_back(firstNum);
			calibrationValueStr.push_back(lastNum);

			//std::cout << "Line Str Value: " << calibrationValueStr << "\n";

			// Parse the new value as an integer
			int calibrationValue = std::stoi(calibrationValueStr);

			// Push it onto the array
			callibrationValues.push_back(calibrationValue);

			finalSum += calibrationValue;

			std::cout << "Value: " << calibrationValue << "\n";
		}
	}
	std::cout << "The final value is: " << finalSum;
	inputFile.close();
}