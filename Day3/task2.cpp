#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <tuple>

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
   std::vector<char> symbolList = { '*' }; // Shorten list for only gears
   // Representing a single found number in a cell, to then follow for the whole value 
   // tuple (x, y, direction) with direction being keys around S on keyboard 'W' 'X 'A' 'D' - 'Q' 'E' 'Z' 'C'
   std::vector<std::tuple<int, int, char>> singleNumberPositions;
   std::vector<int> allGears; // Collection of gears (even to be done in pairs)

   long finalSum = 0;

   readFile(fileContents);

   // Identify all the digits that are adjacent to a symbol, storing them in singleNumberPositions
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
               // If we hit a symbol (only '*' in list), then we need to keep track of how many numbers we get
               int gearNumCount = 0;

               // From here, we know we have found a symbol, therefore we need to check which cells exist

               // To find the diagonals, you need to check for two borders, in addition ensure that there is no overlap with a up/down detection
               bool isAbove = false, isBelow = false; // If we hit a up or down, ignore the diagonals as it will become apart of up/downs value

               // Up
               // Need a check for if at the top, so when i != 0, run if exists

               if (i != 0)
               {
                  // Check if the cell contains a number
                  if (isdigit(fileContents[i - 1][j]) != 0)
                  {
                     //std::cout << "Number above! " << fileContents[i - 1][j] << "\n";
                     isAbove = true;
                     // Now that we know that there is a cell and a digit value, we need to find the whole number, but outside this loop
                     singleNumberPositions.push_back(std::make_tuple(i - 1, j, 'W'));
                     gearNumCount++;
                  }
               }

               // Down
               // Need a check for if we are at the last line, i != rowSize -1, run if exists
               if (i != rowSize - 1)
               {
                  // Check if the cell contains a number
                  if (isdigit(fileContents[i + 1][j]) != 0)
                  {
                     //std::cout << "Number down! " << fileContents[i + 1][j] << "\n";
                     isBelow = true;
                     // Now that we know that there is a cell and a digit value, we need to find the whole number, but outside this loop
                     singleNumberPositions.push_back(std::make_tuple(i + 1, j, 'X'));
                     gearNumCount++;
                  }
               }

               // Left
               // Need to check for if we are at the start of a row j != 0, run if exists
               if (j != 0)
               {
                  // Check if the cell contains a number
                  if (isdigit(fileContents[i][j - 1]) != 0)
                  {
                     //std::cout << "Number Left! " << fileContents[i][j - 1] << "\n";
                     // Now that we know that there is a cell and a digit value, we need to find the whole number, but outside this loop
                     singleNumberPositions.push_back(std::make_tuple(i, j - 1, 'A'));
                     gearNumCount++;
                  }
               }

               // Right
               // Need a check for if we are at the end of a row, so if j != colSize -1, run if exists
               if (j != colSize - 1)
               {
                  // Check if the cell contains a number
                  if (isdigit(fileContents[i][j + 1]) != 0)
                  {
                     //std::cout << "Number Right! " << fileContents[i][j + 1] << "\n";
                     // Now that we know that there is a cell and a digit value, we need to find the whole number, but outside this loop
                     singleNumberPositions.push_back(std::make_tuple(i, j + 1, 'D'));
                     gearNumCount++;
                  }
               }

               // Diagonal Checks
               // Top Left
               if (isAbove == false && i != 0 && j != 0)
               {
                  if (isdigit(fileContents[i - 1][j - 1]) != 0)
                  {
                     //std::cout << "Number top left! " << fileContents[i - 1][j - 1] << "\n";
                     singleNumberPositions.push_back(std::make_tuple(i - 1, j - 1, 'Q'));
                     gearNumCount++;
                  }
               }
               // Top-right
               if (isAbove == false && i != 0 && j != colSize - 1)
               {
                  if (isdigit(fileContents[i - 1][j + 1]) != 0)
                  {
                     //std::cout << "Number top right! " << fileContents[i - 1][j + 1] << "\n";
                     singleNumberPositions.push_back(std::make_tuple(i - 1, j + 1, 'E'));
                     gearNumCount++;
                  }
               }

               // Bottom-left
               if (isBelow == false && i != rowSize - 1 && j != 0)
               {
                  if (isdigit(fileContents[i + 1][j - 1]) != 0)
                  {
                     //std::cout << "Number bottom left! " << fileContents[i + 1][j - 1] << "\n";
                     singleNumberPositions.push_back(std::make_tuple(i + 1, j - 1, 'Z'));
                     gearNumCount++;
                  }
               }

               // Bottom-right
               if (isBelow == false && i != rowSize - 1 && j != colSize - 1)
               {
                  if (isdigit(fileContents[i + 1][j + 1]) != 0)
                  {
                     //std::cout << "Number bottom right! " << fileContents[i + 1][j + 1] << "\n";
                     singleNumberPositions.push_back(std::make_tuple(i + 1, j + 1, 'C'));
                     gearNumCount++;
                  }
               }

               std::cout << "Number of gears for symbol: " << gearNumCount << "\n";

               // We have now added positions to check to the list, however we need to remove those if we don't have EXACTLY 2 gears
               if (gearNumCount != 2)
               {
                  //std::cout << "Popping gears off list\n";
                  //std::cout << "Before prune, after detect: (" << std::get<0>(singleNumberPositions.back()) << ", " << std::get<1>(singleNumberPositions.back()) << ")\n";
                  // Pop the gears found off the list
                  for (size_t gear = 0; gear < gearNumCount; gear++)
                  {
                     singleNumberPositions.pop_back();
                  }
                  //std::cout << "After prune: (" << std::get<0>(singleNumberPositions.back()) << ", " << std::get<1>(singleNumberPositions.back()) << ")\n";
               }
            }
         }
      }
   }

   std::cout << "Number of positions: " << singleNumberPositions.size() << "\n";
   // To get the full numbers, we take a position from the tuple, and read in the direction it specifies until the number is complete
   for (size_t i = 0, posSize = singleNumberPositions.size(); i < posSize; i++)
   {
      // Exit flag to know if we reach '.'
      bool atEnd = false;
      // Get the starting position for the row
      int yCord = std::get<0>(singleNumberPositions[i]);
      int xCord = std::get<1>(singleNumberPositions[i]);
      std::string foundNumberStr;
      // Switch for which direction to move in
      switch (std::get<2>(singleNumberPositions[i]))
      {
      case 'W': case 'X': // Up & Down - Same logic as its restricted to 1 line
         // Add the direct above
         foundNumberStr.push_back(fileContents[yCord][xCord]);
         // Add the left values
         xCord--; // Push away from centre
         while (atEnd == false)
         {
            // Check if the loop doesn't hit a wall
            if (xCord < 0)
            {
               atEnd = true;
               break; // If it does, we don't want to run th rest
            }
            // If the value is a digit, push it to the string
            if (isdigit(fileContents[yCord][xCord]) != 0)
            {
               foundNumberStr = fileContents[yCord][xCord] + foundNumberStr; // Acounts that its read backwards
            }
            // If the value isn't a digit e.g. '$' or '.', then we exit
            else
            {
               atEnd = true;
            }
            xCord--; // Moves left
         }
         // Add the right values
         xCord = std::get<1>(singleNumberPositions[i]) + 1; // Place to first character on right
         atEnd = false;
         while (atEnd == false)
         {
            // Check if the loop doesn't hit a wall
            if (xCord > fileContents[yCord].size())
            {
               atEnd = true;
               break; // If it does, we don't want to run th rest
            }
            // If the value is a digit, push it to the string
            if (isdigit(fileContents[yCord][xCord]) != 0)
            {
               foundNumberStr.push_back(fileContents[yCord][xCord]);
            }
            // If the value isn't a digit e.g. '$' or '.', then we exit
            else
            {
               atEnd = true;
            }
            xCord++; // Moves right
         }
         break;
      case 'A': case 'Q': case 'Z': // Left hand movements
         // Loop through the string looking for characters
         while (atEnd == false)
         {
            // Check if the loop doesn't hit a wall
            if (xCord < 0)
            {
               atEnd = true;
               break; // If it does, we don't want to run th rest
            }
            // If the value is a digit, push it to the string
            if (isdigit(fileContents[yCord][xCord]) != 0)
            {
               foundNumberStr = fileContents[yCord][xCord] + foundNumberStr; // Acounts that its read backwards
            }
            // If the value isn't a digit e.g. '$' or '.', then we exit
            else
            {
               atEnd = true;
            }
            xCord--; // Moves left
         }
         break;
      case 'D': case 'E': case 'C': // Right hand movements
         // Loop through the string looking for characters
         while (atEnd == false)
         {
            // Check if the loop doesn't hit a wall
            if (xCord > fileContents[yCord].size())
            {
               atEnd = true;
               break; // If it does, we don't want to run th rest
            }
            // If the value is a digit, push it to the string
            if (isdigit(fileContents[yCord][xCord]) != 0)
            {
               foundNumberStr.push_back(fileContents[yCord][xCord]);
            }
            // If the value isn't a digit e.g. '$' or '.', then we exit
            else
            {
               atEnd = true;
            }
            xCord++; // Moves right
         }
         break;
      default:
         break;
      }

      // Now that we have found the word, we process it into a integer and add it to the list of gears
      int foundNumber = std::stoi(foundNumberStr);
      allGears.push_back(foundNumber);
   }

   // Loop over to generate gear ratios, iterate by 2 to do the process in pairs
   for (size_t i = 0, allGearSize = allGears.size(); i < allGearSize; i += 2)
   {
      //std::cout << allGears[i] << " * " << allGears[i + 1] << "\n";
      int gearRatio = allGears[i] * allGears[i + 1];
      finalSum += gearRatio;
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