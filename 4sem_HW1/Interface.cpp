#include"Interface.h"
#include"MainLib.h"

void Manual(std::ostream &output)
{   output << "\n Коды действий: \n";
    output << "\t \"a-z\": Exit()\n";
    output << "\t \"1\": Input()\n";
    output << "\t \"2\": Print()\n";
    output << "\t \"3\": Execute()\n";
    output << "\t \"4\": Add()\n";
    output << "\t \"5\': Delete()\n";
    output << "Если хотите получить что-то осмысленное вводите ЦИФРЫ\n";}

void Interface(std::istream &input, std::istream &jsonin, std::ostream &output, std::ostream &jsonout)
{   Manual(output);
    int Comm = 0;
    JSONData data;
    while(input >> Comm)
    {
        if((Comm > 5) || (Comm < 1))
            output << "\n Error: такого кода нет\n";
        switch(Comm)
        {
            case INPUT:
                output << "\n Вызван Input()\n";
                data.Input(jsonin);
                break;
            case PRINT:
                output << "\n Вызван Print()\n";
                int mode;
                input >> mode;
                data.Print(mode,jsonout);
                break;
            case EXE:
                output << "\n Вызыван Execute()\n";
                break;
            case ADD:
                output << "\n Вызван Add()\n";
                break;
            case DELETE:
                output << "\n Вызван Delete()\n";
                break;
        }      
    }
    output << "\n Программа завершает свою работу.\n";}
