#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <fstream>
/*
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

int main()
{
	// The bag and what it holds
	std::map<std::string, int> bag;
	bag["red"] = 12;
	bag["green"] = 13;
	bag["blue"] = 14;

	// What games are possible
	std::vector<int> possibleGames;

	// Read the file
	std::ifstream gameFile("data.txt");
	if (gameFile.is_open())
	{
		// Loop over each game (each game is 1 line ending \n)
		std::string lineContent;
		int red = 0;
		int green = 0;
		int blue = 0;
		bool hasGameFailed = false;
		while (gameFile.good())
		{
			// Get the current line
			std::getline(gameFile, lineContent);
			std::cout << lineContent << "\n";

			int highestRed = 0;
			int highestGreen = 0;
			int highestBlue = 0;

			hasGameFailed = false;

			// TODO Split the string
			// First by colon to get gameInfo & gameData
			std::vector<std::string> gameLine = splitString(lineContent, ":");

			// Get the gameID, split the first side of gameLine "Game #" by ' ', then get the last element "#" and convert to integer.
			int gameID = std::stoi(splitString(gameLine[0], " ").back());

			// Then split the 2nd side of gameLine to get the draws
			std::vector<std::string> gameDraws = splitString(gameLine[1], ";");


			// Iterate over each game draw, counting the colours and comparing
			for (int i = 0, gameDrawSize = gameDraws.size(); i < gameDrawSize; i++)
			{
				// Reset the values of RGB
				red = 0;
				green = 0;
				blue = 0;
				// Remove the starting space
				//std::string trimmedDraw = gameDraws[i].substr(1, gameDraws[i].back());
				std::vector<std::string> colours = splitString(gameDraws[i], ",");
				// Then interate over the colours to compare and add
				for (int j = 0, coloursSize = colours.size(); j < coloursSize; j++)
				{
					colours[j] = colours[j].substr(1, colours[j].back());
					// This could be a pair/map but that changes the function (value, colour)
					std::vector<std::string> keyValues = splitString(colours[j], " ");
					if (keyValues[1] == "red") {
						red += std::stoi(keyValues[0]);
					}
					else if (keyValues[1] == "green") {
						green += std::stoi(keyValues[0]);
					}
					else if (keyValues[1] == "blue") {
						blue += std::stoi(keyValues[0]);
					}
				}

				//std::cout << "RED: " << red << "\n";
				//std::cout << "GREEN: " << green << "\n";
				//std::cout << "BLUE: " << blue << "\n";

				// Once done with the draw, we compare the totals of RGB to the cap in the bag
				if (red <= bag["red"] && green <= bag["green"] && blue <= bag["blue"]) {
					std::cout << "PASSED\n\n";
				}
				else
				{
					std::cout << "FAILED\n\n";
					hasGameFailed = true;
				}
			}

			if (hasGameFailed == false)
			{
				possibleGames.push_back(gameID); // Adding any possible games to the list
			}
		}
		gameFile.close();
	}
	else
	{
		gameFile.close();
	}

	int sum = 0;
	std::cout << "Possible Games include:\n";
	for (size_t i = 0, gameSize = possibleGames.size(); i < gameSize; i++)
	{
		sum += possibleGames[i];
		std::cout << "Game #" << possibleGames[i] << "\n";
	}
	std::cout << "Final Sum: " << sum << "\n";
}
*/