#include "shellbEditor.h"
#include "shell.h"
#include <fstream>
#include <sstream>
#include <string>
#include <unistd.h>
#include <vector>

std::vector<std::string> command_history;

void print_banner() {
    std::ifstream file("banner.txt");
    if (!file) return;

    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string banner = buffer.str();

    std::string raw_banner;
    
    raw_banner.reserve(banner.size() + 50); 

    for (char c : banner) {
        if (c == '\n') {
            raw_banner += "\r\n"; 
        } else {
            raw_banner += c;
        }
    }

    write(STDOUT_FILENO, raw_banner.c_str(), raw_banner.size());
}

void shellb_start() {
    enable_raw_mode();
    clear_screen();
    print_banner();
}
