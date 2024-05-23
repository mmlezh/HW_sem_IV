/**
 * @file myjson.cpp
 * @brief Realization of myjson class
 */

#include "myjson.h"

myjson::myjson(){
    data = json({});
}

myjson::myjson(char* str){
    data = json::parse(str);
}

myjson::myjson(FILE* fin){
    Input(fin);
}

void myjson::Input(FILE* fin){
    data = json::parse(fin);
}

void myjson::Print(){
    std::string temp = data.dump(2);
    std::cout << temp << std::endl;
}

void myjson::Execute(){
    int n = data["Restaraunt"].size();
    std::vector<Restaraunt> rests;
    rests.reserve(n);

    for(int i = 0; i < n; i++){

        std::string name;
        double bill;
        int menu;
        std::vector<std::pair<std::string, double>> rating;

        for(auto& [key, value] : data["Restaraunt"][i].items()){
            if(key == "Name") name = value;
            if(key == "Bill") bill = value;
            if(key == "Menu") menu = value;

            if(key == "Rating"){

                for(int j = 0; j < data["Restaraunt"][i]["Rating"].size(); j++){

                    std::pair<std::string, int> temp;
                    for(auto& [key, value] : data["Restaraunt"][i]["Rating"][j].items()){
                        if(key == "Name") temp.first = value;
                        if(key == "Value") temp.second = value;
                    }
                    rating.push_back(temp);

                }

            }
        }

        Restaraunt rest(name, bill, menu, rating);
        rests.push_back(rest);
    }

    /*
    std::cout << "Before sorting : " << std::endl;
    for(int i = 0; i < rests.size(); i++){
        rests[i].print();
    }
    */


    std::sort(rests.begin(), rests.end());
    //std::reserve(rests.begin(), rests.end()); // if descending needed

    /*
    std::cout << "After sorting : " << std::endl;
    for(int i = 0; i < rests.size(); i++){
        rests[i].print();
    }
    */

    Clear();
    for(int i = 0; i < rests.size(); i++){
        Add(rests[i]);
    }

    return;
}

void myjson::Clear(){
    data.clear();
}

void myjson::Add(Restaraunt rest){
    data["Restaraunt"] += CreateJSON(rest);
}

json myjson::CreateJSON(Restaraunt rest){
    json res;

    res["Name"] = rest.name;
    res["Bill"] = rest.bill;
    res["Menu"] = rest.menu;
    res["ID"] = rest.id;

    for(int i = 0; i < rest.rating.size(); i++){
        res["Rating"][i]["Name"] = rest.rating[i].first;
        res["Rating"][i]["Value"] = rest.rating[i].second;
    }

    return res;
}

void myjson::Delete(std::string id){
    for(int i = 0; i < data["Restaraunt"].size(); i++){
        if(data["Restaraunt"][i]["ID"] == id){
            data["Restaraunt"].erase(i);
        }
    }
}

json myjson::FindRestaraunt(std::string id){
    std::string name;
    int bill, menu;
    std::vector<std::pair<std::string, double>> rating; 

    bool flag = false;

    for(int i = 0; i < data["Restaraunt"].size(); i++){
        if(data["Restaraunt"][i]["ID"] == id){
            name = data["Restaraunt"][i]["Name"];
            bill = data["Restaraunt"][i]["Bill"];
            menu = data["Restaraunt"][i]["Menu"];

            for(int j = 0; j < data["Restaraunt"][i]["Rating"].size(); j++){
                std::pair<std::string, int> temp;
                for(auto& [key, value] : data["Restaraunt"][i]["Rating"][j].items()){
                    if(key == "Name") temp.first = value;
                    if(key == "Value") temp.second = value;
                }
                rating.push_back(temp);
            }
            flag = true;
            break;
        }
    }
    if(flag){
        Restaraunt result(name, bill, menu, rating);
        return CreateJSON(result);
    }else{
        return nlohmann::json({});
    }
    return nlohmann::json({});
}

std::string myjson::Dump(){
    return data.dump(4, ' ');
}

void myjson::Save(std::string filename){
    std::ofstream fout(filename);
    fout << Dump();
    fout.close();
}