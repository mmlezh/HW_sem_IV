#ifndef Inter_h
#define Inter_h

#include<iostream>
#include<fstream>

#define INPUT 1
#define PRINT 2
#define EXE 3
#define ADD 4
#define DELETE 5

void Manual(std::ostream &output);

void Interface(std::istream &input, std::istream &jsonfile ,std::ostream &output, std::ostream &jsonout);

#endif