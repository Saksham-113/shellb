#include "shellbLoop.h"
#include "shellbRead.h"
#include "shellbParse.h"
#include "shellbBuiltins.h"
#include "shellbExecute.h"
#include <string>
#include <unistd.h>
#include <climits>

//this is the shell loop
//each line is stored in a string variable then is sepreated (parsed) and then executed

static std::string buildPrompt() {
    if (showCwd) {
        char cwd[PATH_MAX];
        if (getcwd(cwd, sizeof(cwd)) != nullptr) 
            return std::string(cwd) + " # ";
        return "? # ";
    }
    return " # ";
}

void shellb_loop() {
    std::string line;
    std::vector<std::string> args;
    int status;
    //do-while loop used to take care of the status variable
    do {
        std::cout << buildPrompt();
        //taking input
        line = shellb_read_line();
        //sepreating the commands
        args = shellb_parse(line);
        //executing the comands
        status = shellb_execute(args);
    } while (status);
}
