/**
 * @file restaraunt.h
 * @brief Header file for the Restaraunt struct.
 * This struct represents a restaurant and contains its name, bill, menu, rating and ID. It also contains functions to get the ID and print the details of the restaurant.
 */

#ifndef RESTARAUNT_H
#define RESTARAUNT_H

#include "Hash.h"

#include <iostream>
#include <vector>
#include <algorithm>


/**
 * @brief The Restaraunt struct represents a restaraunt. 
 */
struct Restaraunt{
    /** The ID parameter value*/
    static const int idParam = 3;

    /**The name of the restaraunt*/
    std::string name;

    /**The average bill of the restaraunt*/
    double bill;

    /**Number of variants in restaraunt's menu*/
    int menu;

    /**Pairs <Name of the rating, rating>*/
    std::vector<std::pair<std::string, double>> rating;

    /**The ID of the restaraunt*/
    std::string id;

    /**
     * @brief Default constructor for Restaraunt.
     */
    Restaraunt();

    /**
     *@brief Constructor for Restaraunt.
     *@param Name_ The name of the restaurant.
     *@param Bill_ The bill amount of the restaurant.
     *@param Menu_ The menu of the restaurant.
     *@param Rating_ The rating of the restaurant.
     */
    Restaraunt(std::string, double, int, std::vector<std::pair<std::string, double>>);

    /**
     *@brief Print the details of the restaraunt
     */
    void print();

    /**
     *@brief Overloading less than operator for Restaraunt.
     *@param a The first restaraunt to be compared.
     *@param b The second restaraunt to be compared.
     *@return true if a is less than b, false otherwise.
     */
    friend bool operator<(Restaraunt const&a, Restaraunt const&b){
        double avg_a = 0, avg_b = 0;
        int count = 0;

        for(int i = 0; i < a.rating.size(); i++){
            for(int j = 0; j < b.rating.size(); j++){
                if(a.rating[i].first == b.rating[j].first){
                    avg_a += a.rating[i].second;
                    avg_b += b.rating[j].second;
                    count++;
                }
            }
        }

        avg_a /= count;
        avg_b /= count;

        if(a.menu == b.menu){
            return avg_a < avg_b;
        }else{
            return a.menu < b.menu;
        }
    }

    /**
     *@brief Generate ID of the restaraunt.
     *@param name The name of the restaraunt
     *@param hashParam The hash parameter value
     *@return The ID of the restaraunt
     */
    static std::string getID(std::string, int);
};

#endif // RESTARAUNT_H