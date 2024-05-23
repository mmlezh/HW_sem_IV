/**
 * @file generator.h
 * @brief Header file for the Generator class.
 * 
 * Declaration of Generator class, which provides an ability to generate JSON files.
 * 
 */

#ifndef GENERATOR_H
#define GENERATOR_H

#include "restaraunt.h"

#include <stdio.h>
#include <fstream>
#include <ctime>

/**
 * @class Generator
 * @brief Generates random JSON file filled with random Restaraunts.
 *
 * This class generates random Restaraunt objects using the data read from files.
 */
class Generator{
private:

	/** The maximum number of menu items a Restaraunt can have. */
	int maxMenu = 10;

	/** The maximum amount of cash a Restaraunt can have. */
	int maxCash = 1000;

	/** The maximum rating a Restaraunt can have. */
	int maxRating = 101;

	/** The vector of Restaraunt names. */
	std::vector<std::string> restNames;

	/** The vector of rating names. */
	std::vector<std::string> ratingNames;
public:
	/**
	 * @brief Default constructor for the Generator class.
	 *
	 * Initializes the random seed for generating random Restaraunts.
	 */
	Generator();

	/**
	 * @brief Reads data from files.
	 * @param restFile The file containing the Restaraunt names.
	 * @param ratingFile The file containing the rating names.
	 */
	void readFiles(std::string, std::string);

	/**
	 * @brief Generates random Restaraunts.
	 * @param filename The file to write the generated Restaraunts to.
	 * @param number The number of Restaraunts to generate.
	 */
	void generate(std::string, int);

	/**
	 * @brief Prints the Restaraunts in the vector.
	 *
	 * This function is for testing purposes only.
	 */
	void print();

	/**
	 * @brief Generates a random Restaraunt.
	 * @return A randomly generated Restaraunt.
	 */
	Restaraunt genRestaraunt();
};

#endif // GENERATOR_H