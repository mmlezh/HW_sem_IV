/**
 * @file client.cpp
 * @brief Client realisation
 * 
 * Realisation of a client to work with restaraunt JSON data remotely.
 * 
 */

#include "httplib.h"
#include <iostream>
#include <nlohmann/json.hpp>

using namespace std;

const int SLEEP = 500;

int main(){
	// HTTP
	httplib::Client cli("localhost", 8080);
	
	int com_number = 0;
    bool exit = false;
    while(!exit){
        std::cout << "Available commands : " << std::endl;
        std::cout << "0. Exit" << std::endl;
        std::cout << "1. Generate data.json file" << std::endl;
        std::cout << "2. Print data.json file" << std::endl;
        std::cout << "3. Sort data.json" << std::endl;
        std::cout << "4. Add restaraunt" << std::endl;
        std::cout << "5. Find restaraunt by ID" << std::endl;
        std::cout << "6. Save current data" << std::endl;
        std::cout << "Enter the number of command : ";
        std::cin >> com_number;
        if(com_number < 0 || com_number > 6){
            std::cout << "error : wrong command number" << std::endl << std::endl;
            continue;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP));

        switch(com_number){
            case 0:
            {
                exit = true;
                int killServer = -1;
                std::cout << "Do you want to kill the server process?" << std::endl;
                std::cout << "'0' - to kill the process" << std::endl;
                std::cout << "'1' or any other symbol to keep the server alive" << std::endl;
                std::cin >> killServer;
                if(killServer == 0){
                    auto res = cli.Post("/shutdown");
                    if(res && res->status == 200){
                        std::cout << "Successfully killed server" << std::endl;
                        std::cout << "Now exiting..." << std::endl;
                    }else{
                        std::cout << "Failed to kill server" << std::endl;
                        std::cout << "error status : " << res->status << std::endl;
                    }
                }
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
                std::string req = "/generate?count=" + std::to_string(numbers);
                std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP));
                auto res = cli.Post(req.c_str());
                if(res && res->status == 200){
                    std::cout << "Successfully generated " << numbers << " restaraunts" << std::endl;
                }else{
                    std::cout << "Failed to generate restaraunts" << std::endl;
                    std::cout << "error : " << res.error() << std::endl;
                    std::cout << "status : " << res->status << std::endl;
                }
                break;
            }
            case 2:
            {
                auto res = cli.Get("/print");
                std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP));
                if(res && res->status == 200){
                    std::cout << "data.json :" << std::endl;
                    nlohmann::json response_json = nlohmann::json::parse(res->body);
                    std::cout << std::setw(4) << response_json << std::endl;
                }else{
                    std::cout << "Failed to print" << std::endl;
                    std::cout << "error : " << res.error() << std::endl;
                    std::cout << "status : " << res->status << std::endl;
                }
                break;
            }
            case 3:
            {
            	std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP));
                auto res = cli.Post("/execute");
                if(res && res->status == 200){
                    std::cout << "Successfully executed" << std::endl;
                }else{
                    std::cout << "Failed to execute function" << std::endl;
                    std::cout << "error status : " << res->status << std::endl;
                }
                break;
            }
            case 4:
            {   
                std::string restName;
                std::cout << "Enter restaraunt name : ";
                std::cin >> restName;
                
                std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP));
                auto res = cli.Post("/add", restName, "text/plain");

                if(res && res->status == 200){
                    std::cout << "Added successfully" << std::endl;
                }else{
                    std::cout << "Failed to add a new restaraunt" << std::endl;
                    std::cout << "error status : " << res->status << std::endl;
                }

                break;
            }
            case 5:
            {
                std::string ID;
                std::cout << "Enter ID : " << std::endl;
                std::cin >> ID;

                std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP));
                auto res = cli.Post("/find", ID, "text/plain");
                if(res && res->status == 200){
                    std::cout << "Successfully found" << std::endl;
                    nlohmann::json response_json = nlohmann::json::parse(res->body);
                    std::cout << std::setw(4) << response_json << std::endl;

                    std::cout << "Type '0' to delete this record" << std::endl;
                    std::cout << "Type '1' or any other symbol to keep this record" << std::endl;
                    int action = -1;
                    std::cin >> action;

                    if(action == 0){
                        std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP));
                        auto res2 = cli.Post("/delete", ID, "text/plain");
                        if(res2 && res2->status == 200){
                            std::cout << "Successfully deleted" << std::endl;
                        }else{
                            std::cout << "Failed to delete the record" << std::endl;
                            std::cout << "error status : " << res2->status << std::endl;
                        }
                    }

                }else{
                    std::cout << "Failed to find a restaraunt" << std::endl;
                    std::cout << "error status : " << res->status << std::endl;
                }
                break;
            }
            case 6:
            {
                std::string filename;
                std::cout << "Enter file name to save data : ";
                std::cin >> filename;

                std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP));

                auto res = cli.Post("/save", filename, "text/plain");
                if(res && res->status == 200){
                    std::cout << "Successfully saved" << std::endl;
                }else{
                    std::cout << "Failed to save data.json to " << filename << std::endl; 
                    std::cout << "error status : " << res->status << std::endl;
                }
            }
        }
    }

	return 0;
}