#include "shellbLoop.h"
#include "shell.h"
#include "shellbRead.h"
#include "shellbParse.h"
#include "shellbEditor.h"
#include "shellbBuiltins.h"
#include "shellbExecute.h"
#include <string>
#include <climits>
#include <cstring>
#include <unistd.h>
#include <iostream>

//this is the shell loop
//each line is stored in a string variable then is sepreated (parsed) and then executed

int prompt_size = 0;

void buildPrompt() {
    if (showCwd) {
        char cwd[PATH_MAX];

        if (getcwd(cwd, sizeof(cwd)) != nullptr) {
            prompt_size = strlen(cwd) + 3;

            write(STDOUT_FILENO, cwd, strlen(cwd));
            write(STDOUT_FILENO, " # ", 3);
            return;
        }

        prompt_size = 4;
        write(STDOUT_FILENO, "? # ", 4);
        return;
    }

    prompt_size = 3;
    write(STDOUT_FILENO, " # ", 3);
}

void shellb_loop() {
    std::string line;
    std::vector<std::string> args;
    int status;
    //do-while loop used to take care of the status variable
    do {
        buildPrompt();
        update_cursor();
        //taking input
        line = shellb_read_line();
        //sepreating the commands
        args = shellb_parse(line);
        //executing the comands
        status = shellb_execute(args);
    } while (status);
}
