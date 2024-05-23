/**
 * @file reg.cpp
 * @brief Realization of reg class
 */


#include "reg.h"

bool reg::check_v(std::string str)
{
	return std::regex_match(str, id);
}