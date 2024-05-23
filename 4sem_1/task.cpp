#include <iostream>
#include <fstream>
#include <iterator>
#include <string>
#include <regex>
 //дописать
int main(int argc, char **argv)
{
    std::ifstream ifs;
    std::ofstream ofs;

    ifs.open(argv[1], std::ifstream::in);
    ofs.open(argv[2], std::ofstream::out);

    std::string s;
    getline(ifs, s);
 	std::string new_s = s;

    std::string word;
	std::getline(std::cin, word);
	std::regex self_regex(word);
 
    std::regex word_regex("(\\w+)");
    auto words_begin = std::sregex_iterator(s.begin(), s.end(), word_regex);
    auto words_end = std::sregex_iterator();

    std::cout << "Words with " << word << " in it:\n";
    for (std::sregex_iterator i = words_begin; i != words_end; ++i) {
        std::smatch match = *i;
        std::string match_str = match.str();
        if (std::regex_search(match_str, self_regex)) {
            std::cout << "  " << match_str << '\n';
            
            int lenth = match_str.size();
            
            std::string repl = "";
            
            for(int j = 0; j < lenth; j++)
            {
                repl.push_back('#');
            }

            std::cout << "  " << repl << '\n';

            std::regex replac(match_str);

            new_s = std::regex_replace(new_s, replac, repl);
        }
    }
    ofs << new_s << '\n';

    ofs.close();
    ifs.close();
    return 0;
}

