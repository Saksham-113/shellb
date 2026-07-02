#include "shellbParse.h"
#include <sstream>
#include <string>
#include <vector>

std::vector<std::string> shellb_parse(std::string s) {
    std::stringstream ss(s);
    std::vector<std::string> inputParsed;
    std::string word;
    
    while(ss >> word) {
        inputParsed.push_back(word);
    }
    return inputParsed;
}
