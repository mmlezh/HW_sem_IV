/**
 * @file reg.h
 * @brief Header file for the reg class.
 * 
 * This file contains the declaration of the reg class and its members, used for regular expression matching.
 */

#ifndef REG_H
#define REG_H

#include <iostream>
#include <regex>

/**
 * @class reg
 * @brief A class to check the validity of restaurant IDs.
 */
class reg{
private:
	/**
     * @brief Removed default constructor.
     */
	reg();
public:
	/**
     * @brief A regular expression used to match valid restaurant IDs.
     */
	static inline const std::regex id_regex{R"(<restaraunt><[A-Za-z]{3}><[0-9]+>)"};

	/**
     * @brief A function to check if a string matches the restaurant ID regex pattern.
     * @param string A string to be checked.
     * @return True if the string matches the regex pattern, false otherwise.
     */
	static bool check(std::string);	
};

#endif // REG_H