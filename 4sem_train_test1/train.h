#ifndef Tools_h
#define Tools_h

#include <vector>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

struct Train
{
    int Index;
    double Total;
    std::vector<std::pair<std::string, double>> Freight;

    Train();
    void Input(std::istream &input);
    void Print();
    void JsonToTrain(json Data);};

#endif