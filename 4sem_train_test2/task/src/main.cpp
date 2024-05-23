/**
 * @file main.cpp
 * @brief Main file for offline usage
 */

#include "myjson.h"
#include "generator.h"

int main(){
    Generator gen;
    myjson data;

    int com_number = 0;
    bool exit = false;
    while(!exit){
        std::cout << "Available commands : " << std::endl;
        std::cout << "0. Exit" << std::endl;
        std::cout << "1. Generate data.json file" << std::endl;
        std::cout << "2. Print data.json file" << std::endl;
        std::cout << "3. Sort data.json" << std::endl;
        std::cout << "4. Delete record" << std::endl;
        std::cout << "Enter the number of command : ";
        std::cin >> com_number;
        if(com_number < 0 || com_number > 4){
            std::cout << "error : wrong command number" << std::endl << std::endl;
            continue;
        }

        switch(com_number){
            case 0:
            {
                exit = true;
                break;
            }
            case 1:
            {
                int numbers = 10;
                std::cout << "Enter the number of restaraunts to generate : " << std::endl;
                std::cin >> numbers;
                if(numbers <= 0){
                    std::cout << "error : number of restaraunts to generate less than zero" << std::endl;
                    break;
                }

                gen.readFiles("restNames.txt", "restRatings.txt");
                gen.generate("data.json", numbers);
                data.Clear();
                FILE* fin = fopen("data.json", "r");
                data.Input(fin);
                break;
            }
            case 2:
            {
                data.Print();
                break;
            }
            case 3:
            {
                data.Execute();
                break;
            }
            case 4:
            {
                std::string name;
                std::cout << "Enter the name of the restaraunt to delete : " << std::endl;
                std::cin >> name;
                data.Delete(name);
                break;
            }
        }
    }
    

    return 0;
}
