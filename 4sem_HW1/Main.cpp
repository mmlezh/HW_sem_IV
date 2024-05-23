#include"Interface.h"

int main(int argc, char **argv)
{
    std::ifstream ifs;
    //std::ofstream ofs;
    ifs.open(argv[1], std::ifstream::in);
    //ofs.open(argv[1], std::ofstream::out);
    
    Interface(std::cin, ifs, std::cout, std::cout);

    return 0;
}