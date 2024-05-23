/**
 * @file server2.cpp
 * @brief Server realisation
 * 
 * Realisation of a server to work with company JSON data remotely.
 * 
 */

#include "task.h"

int main()
{
  
  httplib::Server server;

  server.Post("/generate", [&](const httplib::Request& req, httplib::Response& res){
    req_generate(req, res);
  });

  server.Get("/print", [&](const httplib::Request& req, httplib::Response& res){
    std::cout << "print request reveived" << std::endl;
    req_print(req, res);
    std::cout << "finished" << std::endl;
  });

  server.Post("/execute", [&](const httplib::Request& req, httplib::Response& res){
    std::cout << "execute request reveived" << std::endl;
    req_execute(req, res);
    std::cout << "finished" << std::endl;
  });

  server.Post("/delete", [&](const httplib::Request& req, httplib::Response& res){
    std::cout << "delete request reveived" << std::endl;
    req_delete(req, res);
    std::cout << "finished" << std::endl;
  });

  server.Post("/add", [&](const httplib::Request& req, httplib::Response& res){
    std::cout << "add request received" << std::endl;
    req_add(req, res);
    std::cout << "finished" << std::endl;
  });
  
  server.Post("/find", [&](const httplib::Request& req, httplib::Response& res){
    std::cout << "find request reveived" << std::endl;
    req_find(req, res);
    std::cout << "finished" << std::endl;
  });
  
  server.Post("/stop", [&](const httplib::Request& req, httplib::Response& res){
    server.stop();
    std::cout << "servet stoped" << std::endl;
  });


  std::cout << "server started" << std::endl;

  server.listen("localhost", 8080); 

  return 0;
}

