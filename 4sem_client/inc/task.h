/**
 * @file task.h
 * @brief Main header file.
 *
 * These functions provide all interactions between server and JSON data in storage.
 */


#include <fstream>
#include "nlohmann/json.hpp"
#include <iostream>
#include "cpp-httplib-master/httplib.h"
#include "reg.h"

using json = nlohmann::json;

/**
 * @brief The company struct represents a company. 
 */
struct company 
{
	/**Name of company*/
	std::string name;
	
	/**City where company is located*/
	std::string city;
	
	/**Finantial indicators of company*/
    int finances;
    
    /**Assignments of company*/
    std::vector<std::string> assignments;
    
    /**Company ID*/
    std::string id;
    
    /**
	 *@briefOverloaded to_json function.
	 *@param j is Json variable as result.
	 *@param c is company object that will be transformed to Json.
	 */
    void to_json(json& j, const company& c);
    
    /**
	 *@briefOverloaded from_json function.
	 *@param j is Json variable that should be transformed to company object.
	 *@param c is company object that will be received from j.
	 */
	void from_json(const json& j, company& c);  
};


/**
     * @brief Generates n company objects and writes it to Json file.
     * @param c the amount of objects to create.
     */
void Generate(int n);

/**
     * @brief Reads input from the specified file.
     * @return a vector of company objects.
     */
std::vector<company> input();

 
 /**
     * @brief returns companies with certain finantial indicators.
     * @param companylist The list of companies.
     * @param a The low line of finantial indicators.
     * @param b The high line of finantial indicators.
     * @return json object.
     */
json Execute(std::vector<company> companylist, int a, int b);

/**
     * @brief Deletes company with given name.
     * @param companylist The list of companies.
     * @param name The name of company to delete.
     */
void Delete(std::vector<company> companylist, std::string name);


/**
     * @brief Prints json data.
     * @param companylist The list of companies.
     * @return json object.
     */
json Print(std::vector<company> datares);


/**
     * @brief Adds company with given name.
     * @param companylist The list of companies.
     * @param name The name of company to delete.
     */
void Add(std::vector<company> companylist, std::string name);

/**
     * @brief Finds company by given ID.
     * @param companylist The list of companies.
     * @param id The id of company to find.
     * @return json object.
     */
json Find(std::vector<company> companylist, std::string id);

/**
     * @brief Generates ID for the company.
     * @param name The name of company.
     * @param finances The finantial indicators of company.
     */
std::string generate_id(std::string name, int finances);


/**
     * @brief Helps server to interact with Genertate function.
     * @param request Object representing the user request
 	 * @param response Object to be sent back as the response to the user
     */
void req_generate(const httplib::Request&, httplib::Response&);

/**
     * @brief Helps server to interact with Print function.
     * @param request Object representing the user request
 	 * @param response Object to be sent back as the response to the user
     */
void req_print(const httplib::Request&, httplib::Response&);

/**
     * @brief Helps server to interact with Delete function.
     * @param request Object representing the user request
 	 * @param response Object to be sent back as the response to the user
     */
void req_delete(const httplib::Request&, httplib::Response&);

/**
     * @brief Helps server to interact with Add function.
     * @param request Object representing the user request
 	 * @param response Object to be sent back as the response to the user
     */
void req_add(const httplib::Request&, httplib::Response&);

/**
     * @brief Helps server to interact with Execute function.
     * @param request Object representing the user request
 	 * @param response Object to be sent back as the response to the user
     */
void req_execute(const httplib::Request&, httplib::Response&);

/**
     * @brief Helps server to interact with Find function.
     * @param request Object representing the user request
 	 * @param response Object to be sent back as the response to the user
     */
void req_find(const httplib::Request& req, httplib::Response& res);