/**
 * @file server.cpp
 * @brief Server realisation
 * 
 * Realisation of a server to work with restaraunt JSON data remotely.
 * 
 */

#include <csignal>

#include "myjson.h"
#include "generator.h"
#include "httplib.h"
#include "reg.h"

/**
 * @brief Function to randomly generate a JSON data with a given number of Restaraunts
 * @param request Object representing the user request
 * @param response Object to be sent back as the response to the user
 * @param data Object representing the current state of the data structure
 * @param generator Object used to generate new elements
 */
void req_generate(const httplib::Request&, httplib::Response&, myjson&, Generator&);

/**
 * @brief Function to print the contents of the data structure
 * @param request Object representing the user request
 * @param response Object to be sent back as the response to the user
 * @param data Object representing the current state of the data structure
 */
void req_print(const httplib::Request&, httplib::Response&, myjson&);

/**
 * @brief Function to delete an element from the data structure based on user input
 * @param request Object representing the user request
 * @param response Object to be sent back as the response to the user
 * @param data Object representing the current state of the data structure
 */
void req_delete(const httplib::Request&, httplib::Response&, myjson&);

/**
 * @brief Function to add a new element to the data structure based on user input (ID)
 * @param request Object representing the user request
 * @param response Object to be sent back as the response to the user
 * @param data Object representing the current state of the data structure
 * @param generator Object used to generate new elements
 */
void req_add(const httplib::Request&, httplib::Response&, myjson&, Generator&);

/**
 * @brief Function to find an element in the data structure based on user input (ID)
 * @param request Object representing the user request
 * @param response Object to be sent back as the response to the user
 * @param data Object representing the current state of the data structure
 */
void req_find(const httplib::Request&, httplib::Response&, myjson&);

/**
 * @brief Function to save the current state of the data structure to a file
 * @param request Object representing the user request
 * @param response Object to be sent back as the response to the user
 * @param data Object representing the current state of the data structure
 * @param generator Object used to generate new elements
 */
void req_save(const httplib::Request&, httplib::Response&, myjson&);

/**
 * @brief Function to shutdown the server
 * @param request Object representing the user request
 * @param response Object to be sent back as the response to the user
 */
void req_shutdown(const httplib::Request&, httplib::Response&);

int main()
{
  myjson data;
  Generator gen;
  gen.readFiles("restNames.txt", "restRatings.txt");

  // HTTP
  httplib::Server server;

  server.Post("/generate", [&](const httplib::Request& req, httplib::Response& res){
    req_generate(req, res, data, gen);
  });

  server.Get("/print", [&](const httplib::Request& req, httplib::Response& res){
    std::cout << "print request reveived" << std::endl;
    req_print(req, res, data);
    std::cout << "finished" << std::endl;
  });

  server.Post("/execute", [&](const httplib::Request& req, httplib::Response& res){
    std::cout << "execute request reveived" << std::endl;
    data.Execute();
    std::cout << "finished" << std::endl;
  });

  server.Post("/delete", [&](const httplib::Request& req, httplib::Response& res){
    std::cout << "delete request reveived" << std::endl;
    req_delete(req, res, data);
    std::cout << "finished" << std::endl;
  });

  server.Post("/add", [&](const httplib::Request& req, httplib::Response& res){
    std::cout << "add request received" << std::endl;
    req_add(req, res, data, gen);
    std::cout << "finished" << std::endl;
  });

  server.Post("/find", [&](const httplib::Request& req, httplib::Response& res){
    std::cout << "find request reveived" << std::endl;
    req_find(req, res, data);
    std::cout << "finished" << std::endl;
  });

  server.Post("/save", [&](const httplib::Request& req, httplib::Response& res){
    std::cout << "save request received" << std::endl;
    req_save(req, res, data);
    std::cout << "finished" << std::endl;
  });

  server.Get("/shutdown", [&](const httplib::Request& req, httplib::Response& res){
    std::cout << "shutdown request received" << std::endl;
    server.stop();
  });

  std::cout << "server started" << std::endl;

  server.listen("localhost", 8080);

  return 0;
}

void req_generate(const httplib::Request& req, httplib::Response& res, myjson& data, Generator& gen){
  std::string genAmount = req.get_param_value("count");
  int count = std::stoi(genAmount);

  std::cout << "generating " << count << " restaraunts" << std::endl;

  gen.generate("data.json", count);
  data.Clear();
  FILE* fin = fopen("data.json", "r");
  data.Input(fin);

  std::cout << "finished " << std::endl;
}

void req_print(const httplib::Request&, httplib::Response& res, myjson& data){
  res.set_content(data.Dump(), "json");
}

void req_delete(const httplib::Request& req, httplib::Response&, myjson& data){
  std::string id = req.body;
  data.Delete(id);
}

void req_add(const httplib::Request& req, httplib::Response&, myjson& data, Generator& gen){
  std::string restName = req.body;
  Restaraunt toAdd = gen.genRestaraunt();
  toAdd.name = restName;
  toAdd.id = Restaraunt::getID(restName, toAdd.rating.size());
  data.Add(toAdd);
}

void req_find(const httplib::Request& req, httplib::Response& res, myjson& data){
  std::string id = req.body;
  if(!reg::check(id)){
    res.status = 400;
    return;
  }
  json resJson = data.FindRestaraunt(id);
  if(resJson == json({})){
    res.status = 404;
    return;
  }
  res.set_content(resJson.dump(4, ' '), "json");
}

void req_save(const httplib::Request& req, httplib::Response&, myjson& data){
  std::string filename = req.body;
  data.Save(filename);
}

void req_shutdown(const httplib::Request& req, httplib::Response& res){
  std::raise(SIGINT);
  res.set_content("Shutting down server", "text/plain");
}
