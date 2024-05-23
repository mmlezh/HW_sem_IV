#ifndef MainLib_h
#define MainLib_h

#include<iostream>
#include<vector>
#include<fstream>
#include"nlohmann/json.hpp"

using json = nlohmann::json;

struct Train
{
	int Index;
	std::vector<std::pair<std::string, double>> Freight;
	double Total;

	Train(int Ind, std::vector<std::pair<std::string, double>> Fri);

	Train(int Ind, std::vector<std::pair<std::string, double>> Fri, double Tot);

	friend std::ostream &operator<<(std::ostream &output, const Train &unit);

	~Train();};

class JSONData
{
private: 
	json Data;
	std::vector<Train> Trains;
public: 
	JSONData();

	void Input(std::istream &input);
	void Print(int key, std::ostream &output);

	~JSONData();};


#endif