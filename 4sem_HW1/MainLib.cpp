//================================================================================

#include"MainLib.h"

//================================================================================
Train::Train(int Ind, std::vector<std::pair<std::string, double>> Fri): Index(Ind)
{
	double total = 0;
	Freight = Fri;

	for(int i = 0; i < Fri.size(); i++)
	{
		total+= Fri[i].second;
	}
	Total = total;}

Train::Train(int Ind, std::vector<std::pair<std::string, double>> Fri, double Tot): Index(Ind), Total(Tot)
{
	Freight = Fri;}

std::ostream &operator<<(std::ostream &output, const Train &unit)
{
	output << "Index = " << unit.Index << std::endl
		<< "Total = "<< unit.Total << std::endl
		<< "Freight: " << std::endl;
	for(int i = 0; i < unit.Freight.size(); i++)
	{
		output << i+1 << ". Type: \"" << unit.Freight[i].first << "\"\t Weight = "
		<< unit.Freight[i].second << std::endl;
	}
	output << std::endl;
	return output;}

Train::~Train(){}
//================================================================================

JSONData::JSONData()
{
	Data = json({});}

void JSONData::Input(std::istream &input)
{
	Data = json::parse(input);

	int size = Data["Train"].size();
	std::vector<Train> trains;

	trains.reserve(size);

	for(int i = 0; i < size; i++)
	{
		std::cout << "z nen";
		int index; 
		std::vector<std::pair<std::string, double>> freight;
		double total;

		for(auto& [key, value]: Data["Train"][i].items())
		{
			if(key == "Index")
				index = value;
			if(key == "Total")
				total == value;
			if(key  == "Freight")
			{
				for(int j = 0; j < Data["Train"][i]["Freight"].size(); j++)
				{
					std::pair<std::string, double> temp;
					for(auto& [key, value]: Data["Train"][i]["Freight"][j].items())
					{
						if(key == "Type")
							temp.first = value;
						if(key == "Weight")
							temp.second = value;
					}
					freight.push_back(temp);
				}
			}
		}
		Train train(index, freight, total);
		trains.push_back(train);
	}
	Trains = trains;}

void JSONData::Print(int key, std::ostream &output)
{
	if(key)
	{
		std::string output = Data.dump(2);
		std::cout << output << std::endl;
	}else{
		std::cout << Trains.size();
		for(int i = 0; i < Trains.size(); i++)
		{
			std::cout << i+1 << ") Train: " << Trains[i];
		}
	}}


JSONData::~JSONData(){};