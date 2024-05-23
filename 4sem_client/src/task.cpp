/**
 * @file task.cpp
 * @brief Realization of company class
 *@brief Realization of functions to interact server with JSON data
 */

#include "task.h"


void to_json(json& j, const company& c) 
	{
		int l;
		json j_vec(c.assignments);
    	j = {
				{"name", c.name},
				{"city",c.city},
				{"finances", c.finances},
				{"assignments", j_vec},
				{"id", c.id}
			};
	}

void from_json(const json& j, company& c) 
 	{
        j.at("name").get_to(c.name);
        j.at("city").get_to(c.city);
        j.at("finances").get_to(c.finances);
        j.at("assignments").get_to(c.assignments);
        j.at("id").get_to(c.id);
	}
void Generate(int n)
{
	int l, i, f, v1, v2, v3, v4;
	std::ifstream fd("datalist.json");
	std::ofstream o("company2.json");
	std::vector<json> companyv;
	std::string id;
	json datagen = json::parse(fd);
	std::vector<std::string> vec1, vec2, vec3, assignmentv;
	vec1 = datagen["companies"].get<std::vector<std::string>>();
	vec2 = datagen["cities"].get<std::vector<std::string>>();
	vec3 = datagen["assignments"].get<std::vector<std::string>>();
	for(i = 0; i < n; i++)
	{
		l = int(vec1.size());
		v1 = rand() % l;
		l = int(vec2.size());
		v2 = rand() % l;
		l = int(vec3.size());
		v3 = rand() % l + 1;
		for(int k = 0; k < v3; k++)
		{
			v4 = rand() % l;
			if (!std::count(assignmentv.begin(), assignmentv.end(), vec3[v4]))
			{
				assignmentv.push_back(vec3[v4]);
			}
		}
		f = rand() % 1000000 + 1000000;
		id = generate_id(vec1[v1], f);
		company comp = {vec1[v1], vec2[v2], f, assignmentv, id};

		json j = comp; 
		
		companyv.push_back(j);
		
		assignmentv.clear();
	}
	json j_vecres(companyv); 
	json J = {{"Company", j_vecres}}; 
	o << J.dump(4) << std::endl;
}

std::string generate_id(std::string name, int finances)
{
		std::string result = "<company><";
		result += name.substr(0, 3) + "><";
			
		int temp = finances % 1000;
		result += std::to_string(temp) + ">";
		return result;
}

json Find(std::vector<company> companylist, std::string id)
{
	company c;
	json J;
	int flag = 0;
	std::vector<json> companyv;
	for(int i = 0; i < int(companylist.size()); i++)
	{
		auto comp = companylist[i];
		if(comp.id == id)
		{
			c = companylist[i];
			J = c;
			flag = 1;
			break;
		}
	}
	if (flag == 0) J = json({});
	return J;
}


std::vector<company> input()
{
	json jj;
	std::vector<json> datain;
	std::vector<company> companylist;
	std::ifstream f("company2.json");
	f >> jj;
	datain = jj["Company"].get<std::vector<json>>();
	
	for(int i = 0; i < int(datain.size()); i++)
	{
		auto comp = datain[i].get<company>();
		companylist.push_back(comp);
	}

	return companylist;
}


json Execute(std::vector<company> companylist, int a, int b)
{
	company c;
	std::vector<company> datares;
	std::vector<json> companyv;
	for(int i = 0; i < int(companylist.size()); i++)
	{
		auto comp = companylist[i];
		if(comp.finances >= a && comp.finances <= b)
		{
			c = companylist[i];
			datares.push_back(c);

		}
	}
	for (int i = 0; i < int(datares.size()); i++)
	{
		auto comp = datares[i];
		json j = comp; 
		
		companyv.push_back(j);
	}
	json j_vecres(companyv); 
	json J = {{"Company", j_vecres}}; 
	return J;
}

void Delete(std::vector<company> companylist, std::string name)
{
	std::vector<json> companyv;
	std::ofstream o("company2.json");
	for(int i = 0; i < int(companylist.size()); i++)
	{
		auto comp = companylist[i];
		if(comp.name == name)
		{
			companylist.erase(companylist.begin() + i);
		}
	}
	for (int i = 0; i < int(companylist.size()); i++)
	{
		auto comp = companylist[i];
		json j = comp; 
		
		companyv.push_back(j);
	}

	json j_vecres(companyv); 
	json J = {{"Company", j_vecres}}; 
	o << J.dump(4) << std::endl;
}


json Print(std::vector<company> datares)
{
	std::vector<json> companyv;
	for (int i = 0; i < int(datares.size()); i++)
	{
		auto comp = datares[i];
		json j = comp; 
		
		companyv.push_back(j);
	}
	json j_vecres(companyv); 
	json J = {{"Company", j_vecres}}; 
	return J;
}


void Add(std::vector<company> companylist, std::string name)
{
	int l, i, f, v1, v2, v3, v4;
	std::ifstream fd("datalist.json");
	std::ofstream o("company2.json");
	std::vector<json> companyv;
	json datagen = json::parse(fd);
	std::vector<std::string> vec1, vec2, vec3, assignmentv;
	vec2 = datagen["cities"].get<std::vector<std::string>>();
	vec3 = datagen["assignments"].get<std::vector<std::string>>();
	l = int(vec2.size());
	v2 = rand() % l;
	l = int(vec3.size());
	v3 = rand() % l + 1;
	for(int k = 0; k < v3; k++)
	{
		v4 = rand() % l;
		if (!std::count(assignmentv.begin(), assignmentv.end(), vec3[v4]))
		{
			assignmentv.push_back(vec3[v4]);
		}
	}
	f = rand() % 1000000 + 1000000;

	std::string id = generate_id(name, f);
	company comp = {name, vec2[v2], f, assignmentv, id};

	companylist.push_back(comp);
	
	for (i = 0; i < int(companylist.size()); i++)
	{
		auto comp = companylist[i];
		json j = comp; 
		
		companyv.push_back(j);
	}

	json j_vecres(companyv); 
	json J = {{"Company", j_vecres}}; 
	o << J.dump(4) << std::endl;
}

void req_generate(const httplib::Request& req, httplib::Response& res)
{
  std::string genAmount = req.get_param_value("count");
  int count = std::stoi(genAmount);

  std::cout << "generating " << count << " companies" << std::endl;

  Generate(count);
  std::cout << "finished " << std::endl;
}

void req_print(const httplib::Request&, httplib::Response& res)
{
  std::vector<company> datain;
  std::vector<json> companyv;
  std::string dataset;
  json J;
  datain = input();
  J = Print(datain);
  
  res.set_content(J.dump(4), "json");
}

void req_delete(const httplib::Request& req, httplib::Response& res)
{
  std::string compName = req.body;
  std::vector<company> datain;
  datain = input();
  Delete(datain, compName);
}

void req_add(const httplib::Request& req, httplib::Response& res)
{
  std::string compName = req.body;
  std::vector<company> datain;
  datain = input();
  Add(datain, compName);
}

void req_find(const httplib::Request& req, httplib::Response& res)
{
  std::string id = req.body;
  std::vector<company> datain;
  datain = input();
  if(!reg::check_v(id))
  {
    res.status = 400;
    return;
  }
  json J = Find(datain, id);
  if(J == json({}))
  {
    res.status = 404;
    return;
  }

  res.set_content(J.dump(4), "json");
}


void req_execute(const httplib::Request& req, httplib::Response& res)
{
  std::string genAmount = req.get_param_value("count");
  std::vector<company> datain;

  json J;
  int count = std::stoi(genAmount);
  datain = input();
	
  J = Execute(datain, 1000000, count);

  res.set_content(J.dump(4), "json");
}
