/**
 * @file myjson.h
 * @brief Contains the definition of the myjson class for handling JSON data.
 * 
 * This class provides methods for reading data from a file or stream
 * in JSON format, manipulating the data, and writing the data back out
 * to a file or stream in JSON format.
 * 
 * @details The class uses the nlohmann::json library to handle the JSON data.
 */

#ifndef MYJSON_H
#define MYJSON_H

#include <stdio.h>
#include <fstream>
#include <nlohmann/json.hpp>

#include "restaraunt.h"

using json = nlohmann::json;

/**
 * @class myjson
 * @brief Handles JSON data for storing and manipulating restaraunts.
 */ 

class myjson{
private:
    json data;
    
public:
    /**
     * @brief Default constructor for myjson.
     */
    myjson();

    /**
     * @brief Constructor for myjson that takes a json in string format as an argument.
     * @param[in] json_string The JSON file in string format.
     */
    myjson(char*);

    /**
     * @brief Constructor for myjson that takes a file stream as an argument.
     * @param[in] file The file stream containing the JSON data.
     */
    myjson(FILE*);
    
    /**
     * @brief Reads input from the specified file stream into the JSON data.
     * @param[in] file The file stream containing the JSON data.
     */
    void Input(FILE*);

    /**
     * @brief Prints the JSON data to the console.
     */
    void Print();
    

    void Clear();

    /**
     * @brief Executes a command specified in the JSON data.
     * 
     * Sorts restaraunts which are currently stored in JSON data by menu variants and rating.
     */
    void Execute();

    /**
     * @brief Adds a restaraunt to the JSON data.
     * @param[in] restaraunt The restaraunt to add.
     */
    void Add(Restaraunt);

    /**
     * @brief Deletes the restaraunt with the specified id from the JSON data.
     * @param[in] id The id of the restaraunt to delete.
     */
    void Delete(std::string);


    void Save(std::string);

    /**
     * @brief Dumps the JSON data to a string.
     * @return A string representation of the JSON data.
     */
    std::string Dump();

    /**
     * @brief Creates a JSON object from a restaraunt object.
     * @param[in] restaraunt The restaraunt to create a JSON object from.
     * @return A JSON object representing the restaraunt.
     */
    static json CreateJSON(Restaraunt);

    /**
     * @brief Finds the restaraunt with the specified id in the JSON data.
     * @param[in] id The id of the restaraunt to find.
     * @return A JSON object representing the restaraunt, or an empty object if the restaraunt is not found.
     */
    json FindRestaraunt(std::string);
};


#endif // MYJSON_H