#include "shellbBuiltins.h"
#include "shell.h"
#include "shellbEditor.h"
#include <vector>
#include <iostream>
#include <ostream>
#include <unistd.h>
#include <cstdio>
#include <cstdlib>
#include <string>

std::vector<std::string> builtin_str = {
    "cd",
    "help",
    "exit",
    "showpath",
    "hidepath",
    "history",
    "clear"
};

int (*builtin_func[]) (const std::vector<std::string>&) = {
    &shellb_cd,
    &shellb_help,
    &shellb_exit,
    &shellb_showpath,
    &shellb_hidepath,
    &shellb_history,
    &shellb_clear
};

bool showCwd = true;

int shellb_num_builtins() {
    return builtin_str.size();
}

int shellb_cd(const std::vector<std::string> &args) {
    std::string target;

    if (args.size() < 2) {
        const char* home = getenv("HOME");
        if (home == nullptr) {
            fprintf(stderr, "shellb: Home not set\n");
            return 1;
        }
        target = home;
    }
    else if (args[1] == "~") {
        const char* home = getenv("HOME");
        target = home ? home : "/";
    }
    else {
        target = args[1];
    }

    if (chdir(target.c_str()) != 0) {
        perror("shellb");
    }
    return 1;
}

int shellb_hidepath(const std::vector<std::string> &args) {
    showCwd = false;
    return 1;
}

int shellb_showpath(const std::vector<std::string> &args) {
    showCwd = true;
    return 1;
}

int shellb_exit(const std::vector<std::string> &args) {
    return 0;
}

int shellb_help(const std::vector<std::string> &args) {
    int i;
    std::cout << "Saksham Bhadani's ShellB\n";
    std::cout << "Type program names and arguments, and hit enter.\n";
    std::cout << "The following are built in:\n";

    for (i = 0; i < shellb_num_builtins(); i++) {
        std::cout << builtin_str[i] << std::endl;
    }

    printf("Use the man command for information on other programs.\n");
    return 1;
}

int shellb_history(const std::vector<std::string> &args) {
    for (std::string s : command_history) {
        std::cout << s << std::endl;
    }
    return 1;
}

int shellb_clear(const std::vector<std::string> &args) {
    clear_screen();
    return 1;
}
