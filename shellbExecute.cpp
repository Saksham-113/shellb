#include "shellbExecute.h"
#include "shellbBuiltins.h"
#include <cerrno>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int shellb_launch(std::vector<std::string> args) {
    pid_t pid, wpid;
    int status;

    pid = fork();
    if (pid == 0) {
        std::vector<char*> copy_args;
        for (auto& a: args) 
            copy_args.push_back(const_cast<char*>(a.c_str()));
        
        copy_args.push_back(nullptr);

        execvp(copy_args[0], copy_args.data());
        if (errno == ENOENT) {
            std::cerr << "shellb: command not found\n";
        } else {
            perror("shellb");
        }
        exit(EXIT_FAILURE);
    }
    else if (pid > 0) {
        do {
            wpid = waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }
    else {
        perror("shellb");
    }
    return 1;
}

int shellb_execute(std::vector<std::string> args) {
    if(args.empty()) {
        return 1;
    }
    
    for(int i = 0; i < shellb_num_builtins(); i++) {
        if (args[0] == builtin_str[i]) 
            return (*builtin_func[i])(args);
    }

    return shellb_launch(args);
}
