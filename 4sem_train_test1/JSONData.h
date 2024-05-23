#ifndef JSONData_h
#define JSONData_h

#include <stdio.h>
#include <ctime>
#include <math.h>
#include <fstream>
#include <nlohmann/json.hpp>
#include <iostream>
#include <vector>
#include <algorithm>

#define GENER 0
#define INPUT 1
#define PRINT 2
#define EXE 3
#define ADD 4
#define DELETE 5

#define EPS 2e-12

using json = nlohmann::json;

//=========================================================================================
class JSONData
{
private:
    json Data;
    
public:

    JSONData();
    
    void Input(std::istream &fin);
    void Print(std::ostream &fout);

    double FindMax();

    void Execute(double tot, std::ostream &output);

    void Add(Train add);
    void Delete(int ind);
    void Clear();};
#endif