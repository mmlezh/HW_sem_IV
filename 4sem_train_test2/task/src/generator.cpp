/**
 * @file generator.cpp
 * @brief Realization of Generator class
 */

#include "generator.h"

Generator::Generator(){
	std::srand(std::time(NULL));
	maxMenu = std::rand() % 1000 + maxMenu;
	maxCash = std::rand() % 10000 + maxCash;
}

void Generator::readFiles(std::string names, std::string ratings){
	std::ifstream rest;
	rest.open(names);
	std::ifstream rating;
	rating.open(ratings);

	std::string word;
	restNames.clear();
	ratingNames.clear();

	while(std::getline(rest, word)){
		restNames.push_back(word);
	}
	while(std::getline(rating, word)){
		ratingNames.push_back(word);
	}

	rest.close();
	rating.close();
}

void Generator::print(){
	std::cout << "NAMES : " << std::endl;
	for(auto it = restNames.begin(); it != restNames.end(); it++){
		std::cout << *it << std::endl;
	}
	std::cout << std::endl << "RATINGS : " << std::endl;
	for(auto it = ratingNames.begin(); it != ratingNames.end(); it++){
		std::cout << *it << std::endl;
	}
	std::cout << std::endl;
}

void Generator::generate(std::string fname, int generateAmount){
	std::ofstream fin; fin.open(fname);

	fin << "{\n\t\"Restaraunt\":\n\t[\n";

	for(int i = 0; i < generateAmount; i++){
		fin << "\t\t{\n";

		int len = std::rand() % 5 + 1;

		// NAME
		std::string temp = restNames[std::rand() % restNames.size()];
		fin << "\t\t\t\"ID\":\"" << Restaraunt::getID(temp, len) << "\",\n";
		fin << "\t\t\t\"Name\":\"" << temp << "\",\n";
		fin << "\t\t\t\"Bill\":" << std::rand() % maxCash + 1 << ",\n";
		fin << "\t\t\t\"Menu\":" << std::rand() % maxMenu + 1 << ",\n";
		fin << "\t\t\t\"Rating\":[\n";

		for(int j = 0; j < len; j++){
			fin << "\t\t\t\t{\n";
			fin << "\t\t\t\t\t\"Name\":\"" << ratingNames[std::rand() % ratingNames.size()] << "\",\n";
			fin << "\t\t\t\t\t\"Value\":" << std::rand() % maxRating << "\n";
			if(j == len-1) fin << "\t\t\t\t}\n";
			else fin << "\t\t\t\t},\n";
		}

		fin << "\t\t\t]\n";
		if(i == generateAmount - 1) fin << "\t\t}\n";
		else fin << "\t\t},\n";
	}


	fin << "\t]\n}";
	fin.close();
}

Restaraunt Generator::genRestaraunt(){
	std::string name = "temp";
	std::vector<std::pair<std::string, double>> rating;
	int bill = std::rand() % maxCash + 1;
	int menu = std::rand() % maxMenu + 1;
	int len = std::rand() % 5 + 1;
	rating.reserve(len);

	for(int i = 0; i < len; i++){
		rating.push_back({ratingNames[std::rand() % ratingNames.size()], std::rand() % maxRating});
	}

	Restaraunt result(name, bill, menu, rating);
	return result;

}