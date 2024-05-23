#include"train.h"

Train::Train() = default;

void Train::Input(std::istream &input)
{
    std::pair<std::string, double> temp;
    char c;
    int amount;
    double total = 0;
    std::cout << " Введите Index: ";
    input >> Index;
    std::cout << " Введите длину Freight: ";
    input >> amount;
    for(int i = 0; i < amount; i++)
    {
        std::cout << " Weight: ";
        std::cin >> temp.second;
        total += temp.second;
        std::cin.get(c);
        std::cout << " Type: ";
        std::getline(std::cin, temp.first);
        Freight.push_back(temp);
    }
    Total = total;}

void Train::Print()
{
    std::cout << "Index = " << Index << std::endl
            << "Total = " << Total << std::endl
            << "Freight: " << std::endl;

    for(int i = 0; i < Freight.size(); i++){
        std::cout << i << ") Type = " << Freight[i].first << "\t Weight = " << Freight[i].second << std::endl;
    }
    std::cout << std::endl;}

void Train::JsonToTrain(json Data)
{
    for(auto& [key, value]: Data.items())
    {
        if(key == "Index")
            Index = value;
        if(key  == "Freight")
        {
            for(int j = 0; j < Data["Freight"].size(); j++)
            {
                std::pair<std::string, double> temp;
                for(auto& [key, value]: Data["Freight"][j].items())
                {
                    if(key == "Type")
                        temp.first = value;
                    if(key == "Weight")
                        temp.second = value;
                }
                Freight.push_back(temp);
            }
        }
        if(key == "Total") 
            Total = value;
    }}
