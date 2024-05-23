/**
 * @file restaraunt.cpp
 * @brief Realization of Restaraunt class
 */

#include "restaraunt.h"

Restaraunt::Restaraunt() = default;

Restaraunt::Restaraunt(std::string Name_, double Bill_, int Menu_, std::vector<std::pair<std::string, double>> Rating_){
    name = Name_;
    bill = Bill_;
    menu = Menu_;
    rating = Rating_;
    id = getID(name, rating.size());
}

void Restaraunt::print(){
    std::cout << "Name = " << name << std::endl
            << "Bill = " << bill << std::endl
            << "Menu = " << menu << std::endl
            << "Rating : " << std::endl;

    for(int i = 0; i < rating.size(); i++){
        std::cout << i << ") Name = " << rating[i].first << " Rated = " << rating[i].second << std::endl;
    }
    std::cout << std::endl;
}

std::string Restaraunt::getID(std::string name , int hashParam){
    std::string result = "<restaraunt><";
    result += name.substr(0, idParam) + "><";

    int temp = Hash::getHash(name, hashParam);
    result += std::to_string(temp) + ">";
    
    return result;
}