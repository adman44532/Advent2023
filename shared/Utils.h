#pragma once

#include <vector>
#include <string>

typedef std::vector<std::string> fileOutputStr;

namespace Utils {
	/**
	 * Reads a text file and returns its contents as a vector of strings.
	 *
	 * Each line of the file is read and stored as a separate string. If the file
	 * cannot be opened, an empty vector is returned.
	 *
	 * @param fileName The name and path of the file to read.
	 * @return fileOutputStr A vector of strings with each string representing a line from the file;
	 *                       an empty vector is returned if the file is inaccessible.
	 */
	 fileOutputStr readInput(std::string &fileName);
}