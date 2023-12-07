#include <iostream>
#include <vector>
#include <string>
#include <fstream>

// Reads the data.txt file, altering the parameter vector
// param output - the vector to output each line in the file to
void readFile(std::vector<std::string>& output)
{
	std::ifstream engineSchematic("data.txt");

	if (engineSchematic.is_open())
	{
		while (engineSchematic.good())
		{
			std::string line;
			engineSchematic >> line;
			output.push_back(line);
		}
	}
}

int main()
{
	// Store a 2D Matrix, each string being a row and each vector item a column.
	std::vector<std::string> fileContents;
	std::vector<char> symbolList = { '!', '@','#', '$', '%', '^', '&', '*', '(', ')','-', '+' };

	int finalSum = 0;

	readFile(fileContents);

	// Loop through each row (Vector Item)
	for (size_t i = 0, rowSize = fileContents.size(); i < rowSize; i++)
	{
		std::cout << fileContents[i] << "\n";
		// Loop through each col (String in Vector)
		for (size_t j = 0, colSize = fileContents[i].size(); j < colSize; j++)
		{
			// Get the current row
			std::string row = fileContents[i];
			// Compare the current char to the chars in the symbolList
			for (size_t k = 0, symbolListSize = symbolList.size(); k < symbolListSize; k++)
			{
				// Check to see if the current cell matches any of the symbols
				if (row[j] == symbolList[k]) 
				{
					std::cout << "Symbol Hit!" << "\n";
				}
			}
		}
	}


	// Open the file
		// Read a lines from the file
		// Loop over the elements in the line
		// The contents of the file is placed on a vector<string> which can act as a 2D matrix
			// [ ][ ][ ][ ][ ]
			// [ ][ ][1][4][3]
			// [1][8][X][ ][ ]
			// [ ][ ][ ][2][1]
			// [ ][ ][ ][ ][ ]
			// Checking each of the spots around the symbol for a value
			// If a number is within reach, find the number appropriately
				// X is the symbol, to get numbers we check all the points around,
				// For diagonal movements, the up/down needs to be checked first to ensure diags down double count the numbers.
				// Up/Down    - Move left until '.', rearrange order then move right until '.', then combine the final number
				// Left       - Move left until '.', rearrange the left values in the right order
				// Right      - Move right until '.', no rearrange required.
				// Diag Right - Move right until '.', no rearrange required.
				// Diag Left  - Move left until '.', rearrange required
		// Numbers found get added to a finalSum

	std::cout << "The final sum is... " << finalSum << "\n";
}