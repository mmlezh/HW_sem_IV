/**
 * @file Hash.h
 * @brief Header file for the Hash class
 * 
 * Declaration of Hash class, which provides hashing functionality for strings.
 * 
 */

#ifndef HASH_H
#define HASH_H

#include <string>

/**
 * @class Hash
 *
 * @brief Provides hashing functionality for strings.
 */
class Hash{
private:
	/**
	 * @brief A prime number used for hashing.
	 */
	static const int p = 1234567891; // prime

	/**
     * @brief Removed default constructor.
     */
	Hash();
public:
	/**
	 * @brief Computes a hash for the given string using the specified length.
	 *
	 * @param string The string to hash.
	 * @param length The length of the string to hash.
	 *
	 * @return The computed hash value.
	 */
	static int getHash(const std::string word, int k){
		int len = word.length();
		int range = len;
	    if(k < range && k > 0) range = k;
		int hash = k;

		for(int i = 0; i < range; i++){
			hash = (hash<<5)^(hash>>27)^word[i];
		}
		return hash % p;
	}
};

#endif // HASH_H