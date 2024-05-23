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

const int SLEEP = 1000;

int main(){
	// HTTP
	httplib::Client cli("localhost", 8080);
	
	int com_number = 0;
    bool exit = false;
    while(!exit){
        std::cout << "Commands : " << std::endl;
        std::cout << "0. Exit" << std::endl;
        std::cout << "1. Generate data" << std::endl;
        std::cout << "2. Print data" << std::endl;
        std::cout << "3. Delete company" << std::endl;
        std::cout << "4. Add company" << std::endl;
        std::cout << "5. Execute companies with financial indicators" << std::endl;
		std::cout << "6. Find company by id" << std::endl;
		std::cout << "7. Stop server" << std::endl;  
        std::cout << "Enter the number of command : ";
        std::cin >> com_number;
        if(com_number < 0 || com_number > 6){
            std::cout << "error : invalid number" << std::endl << std::endl;
            continue;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP));

        switch(com_number){
            case 0:
            {
                exit = true;
                break;
            }
            case 1:
            {
                int numbers = 10;
                std::cout << "Enter the number of companies to generate: " << std::endl;
                std::cin >> numbers;
                if(numbers <= 0)
				{
                    std::cout << "error: invalid number" << std::endl;
                    break;
                }
                std::string req = "/generate?count=" + std::to_string(numbers);
                std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP));
                auto res = cli.Post(req.c_str());
                if(res && res->status == 200)
				{
                    std::cout << "generated " << numbers << " companies" << std::endl;
                }
				else
				{
                    std::cout << "error: " << res.error() << std::endl;
                    std::cout << "status: " << res->status << std::endl;
                }
                break;
            }
            case 2:
            {
                auto res = cli.Get("/print");
                std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP));
                nlohmann::json response_json = nlohmann::json::parse(res->body);
                std::cout << std::setw(4) << response_json << std::endl;

                break;
            }
            case 3:
            {   
                std::string compName;
                std::cout << "Enter company name: ";
                std::cin >> compName;
                
                std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP));
                auto res = cli.Post("/delete", compName, "text/plain");

                if(res && res->status == 200)
				{
                    std::cout << "success" << std::endl;
                }
				else
				{
                    //std::cout << "error : " << res->error << std::endl;
                    std::cout << "error status : " << res->status << std::endl;
                }

                break;
            }
            case 4:
            {   
                std::string compName;
                std::cout << "Enter company name: ";
                std::cin >> compName;
                
                std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP));
                auto res = cli.Post("/add", compName, "text/plain");

                if(res && res->status == 200)
				{
                    std::cout << "success" << std::endl;
                }
				else
				{
                    //std::cout << "error : " << res->error << std::endl;
                    std::cout << "error status : " << res->status << std::endl;
                }

                break;
            }
            case 5:
            {
            	int numbers = 10;
                std::cout << "Enter the finantial indicators of companies: " << std::endl;
                std::cin >> numbers;
                std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP));
                auto res = cli.Post("/execute?count=" + std::to_string(numbers));
                std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP));
            	nlohmann::json response_json = nlohmann::json::parse(res->body);
            	std::cout << std::setw(4) << response_json << std::endl;
                break;
            }
            case 6:
            {
            	std::string id;
                std::cout << "Enter company id: " << std::endl;
                std::cin >> id;
                std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP));
                auto res = cli.Post("/find", id, "text/plain");
                std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP));
                if(res && res->status == 200)
				{
                    std::cout << "success" << std::endl;
                }
				else
				{
                    //std::cout << "error : " << res->error << std::endl;
                    std::cout << "error status : " << res->status << std::endl;
                    break;
                }
            	nlohmann::json response_json = nlohmann::json::parse(res->body);
            	std::cout << std::setw(4) << response_json << std::endl;
                break;
            }
            case 7:
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP));
                auto res = cli.Post("/stop" + std::to_string(numbers));
                std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP));
                if(res && res->status == 200)
				{
                    std::cout << "success" << std::endl;
                }
                break;
            }
        }
    }

	return 0;
}