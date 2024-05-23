#include "Tools.h"

//=========================================================================================
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

//=========================================================================================
JSONData::JSONData()
{
    Data = json({});}

void JSONData::Input(std::istream &fin)
{
    Data = json::parse(fin);}

void JSONData::Print(std::ostream &fout)
{
    std::string temp = Data.dump(4, ' ');
    fout << temp << std::endl;}

double JSONData::FindMax()
{
    double Max = 0;
    for(int i = 0; i < Data["Train"].size(); i++)
    {
        for(auto& [key, value] : Data["Train"][i].items()){
            if(key == "Total"){
                double temp = value;
                if(temp - Max > EPS)
                {
                    Max = value;
                }
            }
        }
    }
    return Max;}

void JSONData::Execute(double tot, std::ostream &output) //работает
{
    double max = 0;

    max = FindMax();
    
    if(tot - max < EPS) // tmp < tot < max  
    {
        JSONData data;

        for(int i = 0; i < Data["Train"].size(); i++)
        {
            for(auto& [key, value] : Data["Train"][i].items()){
                if(key == "Total"){
                    double tmp = value;
                    Train unit;
                    if((tmp - tot > EPS) || (fabs(tmp - tot) < EPS))
                    {
                        std::cout << tmp << std::endl;
                        unit.JsonToTrain(Data["Train"][i]);
                        unit.Print();
                        data.Add(unit);
                    }
                }
            }
        }
        data.Print(output);
        data.Clear();
    } else
    {
        output << "\n{ }\n" << std::endl;
    };}

void JSONData::Add(Train train)
{
    json add;

    add["Index"] = train.Index;

    for(int i = 0; i < train.Freight.size(); i++){
        add["Freight"][i]["Type"] = train.Freight[i].first;
        add["Freight"][i]["Weight"] = train.Freight[i].second;
    }
    add["Total"] = train.Total;

    Data["Train"] += add;}

void JSONData::Delete(int ind)
{
    for(int i = 0; i < Data["Train"].size(); i++){
        if(Data["Train"][i]["Index"] == ind){
            Data["Train"].erase(i);
        }
    }}

void JSONData::Clear()
{
    Data.clear();}
//=========================================================================================

Generator::Generator()
{
    std::srand(std::time(NULL));}

void Generator::Input(std::string types, std::string inds, std::string weights)
{
    std::ifstream type;
    type.open(types);
    std::ifstream ind;
    ind.open(inds);
    std::ifstream weight;
    weight.open(weights);

    std::string word;
    Types.clear();
    Indexes.clear();
    Weights.clear();

    while(std::getline(type, word)){
        Types.push_back(word);
    }
    int tmp;
    while(ind >> tmp){
        Indexes.push_back(tmp);
    }
    double temp;
    while(weight >> temp){
        Weights.push_back(temp);
    }

    type.close();
    ind.close();
    weight.close();}

void Generator::Create(std::string FileName, int Amount)
{
    std::ofstream Result; Result.open(FileName);
    Result << "{\n\t\"Train\":\n\t[\n";

    for(int i = 0; i < Amount; i++){
        Result << "\t\t{\n";

        Result << "\t\t\t\"Index\":" << Indexes[i] << ",\n";
        Result << "\t\t\t\"Freight\":[\n";

        int size = std::rand() % 10+1;
        double total = 0;
        for(int j = 0; j < size; j++){
            double tmp = Weights[std::rand() % Weights.size()]; 
            total += tmp;
            Result << "\t\t\t\t{\n";
            Result << "\t\t\t\t\t\"Type\":\"" << Types[std::rand() % Types.size()] << "\",\n";
            Result << "\t\t\t\t\t\"Weight\":" << tmp << "\n";
            if(j == size-1) Result << "\t\t\t\t}\n";
            else Result << "\t\t\t\t},\n";
        }

        Result << "\t\t\t],\n";
        Result << "\t\t\t\"Total\":" << total << "\n";
        if(i == Amount - 1) Result << "\t\t}\n";
        else Result << "\t\t},\n";
    }


    Result << "\t]\n}";
    Result.close();}
//=========================================================================================
void Manual(std::ostream &output)
{   output << " Коды действий: \n";
    output << "\t \"a-z\": Exit()\n";
    output << "\t \"0\": Generator()\n";
    output << "\t \"1\": Input()\n";
    output << "\t \"2\": Print()\n";
    output << "\t \"3\": Execute()\n";
    output << "\t \"4\": Add()\n";
    output << "\t \"5\': Delete()\n";
    output << "Если хотите получить что-то осмысленное вводите ЦИФРЫ\n";
    output << "|====================================================|\n";}

void Interface(std::istream &input, std::ostream &output, JSONData &Data)
{   
    Manual(output);
    int Comm;
    Generator gen;
    std::string name = "data.json";
    output << " Введите команду: ";
    while(input >> Comm)
    {

        if((Comm > 5) || (Comm < 0))
        {
            output << "Error: такого кода нет \n";
            output << "|====================================================|\n";
        }
        switch(Comm)
        {
            case GENER:
            {
                int Amount = 1;
                std::cout << "Введите кол-во данных для генерации: " << std::endl;
                std::cin >> Amount;
                if(Amount <= 0){
                    std::cout << "Error: Amount должен быть положительным" << std::endl;
                    break;
                }

                gen.Input("Types.txt", "Indexes.txt", "Weights.txt");
                gen.Create("data.json", Amount);
                std::cout << "Json файл \"" << name <<"\" успешно сгенирирован.\n";
                output << "|====================================================|\n";
                break;
            }
            case INPUT:
            {
                std::ifstream fin;
                //std::string fil;
                //std::getline(input, fil);
                Data.Clear();
                fin.open("data.json");
                Data.Input(fin);
                std::cout << "Json файл \"" << name <<"\" успешно прочитан.\n";
                output << "|====================================================|\n"; 
                fin.close();
                break;
            }
            case PRINT:
            {
                Data.Print(output);
                output << "|====================================================|\n";
                break;
            }
            case EXE:
            {
                double tot;
                output << " Введите граничное значение Total: ";
                input >> tot;
                Data.Execute(tot, output);
                output << "|====================================================|\n";
                break;
            }
            case ADD:
            {
                Train add;
                add.Input(input);
                Data.Add(add);
                output << "|====================================================|\n";   
                break;
            }
            case DELETE:
            { 
                output << " Введите значение Index: ";
                int index;
                std::cin >> index;
                Data.Delete(index);
                output << "|====================================================|\n";
                break;
            }
        }
        output << " Введите комаду: ";  
    }
    output << " Программа завершает свою работу.\n";}
