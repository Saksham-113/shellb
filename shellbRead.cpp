#include "shellbRead.h"
#include <cstdlib>
#include <iostream>

std::string shellb_read_line() {
    std::string line;
    if (!std::getline(std::cin, line)) {
        if (std::cin.eof()) exit(EXIT_SUCCESS);
        else {
            std::cerr << "readline";
            exit(EXIT_FAILURE);
        }
    }
    return line;
}
