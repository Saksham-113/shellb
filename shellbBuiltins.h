#pragma once
#include <string>
#include <vector>

extern bool showCwd;

int shellb_num_builtins();
int shellb_cd(const std::vector<std::string>& args);
int shellb_help(const std::vector<std::string>& args);
int shellb_exit(const std::vector<std::string>& args);
int shellb_showpath(const std::vector<std::string>& args);
int shellb_hidepath(const std::vector<std::string>& args);

extern std::vector<std::string> builtin_str;

extern int (*builtin_func[]) (const std::vector<std::string>&);
