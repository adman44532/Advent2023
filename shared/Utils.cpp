#include "Utils.h"
#include "fstream"
#include <iostream>

fileOutputStr Utils::readInput(std::string &fileName)
{
    fileOutputStr output;
    std::ifstream file(fileName);

    if (file.is_open())
    {
        while (file.good())
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