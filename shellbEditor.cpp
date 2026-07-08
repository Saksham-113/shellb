#include "shellbEditor.h"
#include "shell.h"
#include <cstdio>
#include <cstdlib>
#include <string>
#include <termios.h>
#include <iostream>
#include <unistd.h>
struct termios orig_termios;

void clear_screen() {
    write(STDOUT_FILENO, "\x1b[2J", 4);
    write(STDOUT_FILENO, "\x1b[H", 3);
}

void editor_error(std::string s) {
    clear_screen();
    perror(s.c_str());
    exit(1);
}

void disable_raw_mode() {
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios) == -1)
        editor_error("tcsetattr");
}

void enable_raw_mode() {
    if (tcgetattr(STDIN_FILENO, &orig_termios) == -1) editor_error("tcgetattr");
    atexit(disable_raw_mode);

    struct termios raw = orig_termios;
    raw.c_lflag &= ~(ECHO | ICANON | ISIG);
    raw.c_cc[VMIN] = 0;
    raw.c_cc[VTIME] = 1;

    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1) editor_error("tcsetattr");
}

void display_line(std::string& line) {
    write(STDOUT_FILENO, "\r", 1);

    if (prompt_size > 0) {
        std::string seq = "\x1b[" + std::to_string(prompt_size) + "C";
        write(STDOUT_FILENO, seq.c_str(), seq.size());
    }

    write(STDOUT_FILENO, "\x1b[J", 3);
    write(STDOUT_FILENO, line.c_str(), line.size());
}

void update_cursor(int cursor_position) {
    write(STDOUT_FILENO, "\r", 1);

    std::string seq = "\x1b[" + std::to_string(prompt_size + cursor_position) + "C";
    write(STDOUT_FILENO, seq.c_str(), seq.size());
}
