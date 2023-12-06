#include <iostream>
#include <fstream>
#include <vector>
#include <string>

/*
int main()
{
	// Data Storage
	std::vector<std::string> fileLines;
	std::vector<int> callibrationValues;
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
			std::cout << lineContent << "\n";

			// Initalise the first and last numbers
			char firstNum = '\0';
			char lastNum  = '\0';

			// Loop over each character within the string
			for (int i = 0, strSize = lineContent.size(); i < strSize; i++) 
			{
				char readingChar = lineContent[i];
				// Check whether the character is a digit
				if (isdigit(readingChar) != 0) 
				{
					// If the firstNum is still zero, then we haven't got a number yet
					if (firstNum == 0) 
					{
						firstNum = readingChar;
					}
					// If we have the firstNum, then any other number becomes the last number
					else 
					{
						lastNum = readingChar;
					}
				}
			}

			// Check for if there is only one number, to duplicate it to be first and last
			if (lastNum == '\0') {
				lastNum = firstNum;
			}

			// Once through the string, we add the two characters together
			std::string calibrationValueStr;
			calibrationValueStr.push_back(firstNum);
			calibrationValueStr.push_back(lastNum);

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
*/