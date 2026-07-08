#include "shellbRead.h"
#include "shell.h"
#include "shellbEditor.h"
#include <cerrno>
#include <cstdio>
#include <string>
#include <cstdlib>
#include <iostream>
#include <unistd.h>
#include <cstddef>

enum class KeyPress {
    CHAR,
    ESC,
    ENTER,
    CTRL_C,
    ARROW_UP,
    ARROW_DOWN,
    ARROW_LEFT,
    ARROW_RIGHT,
    BACKSPCE,
    UNKNOWN,
};

KeyPress read_keypress(char& c) {
    int nread;
    while ((nread = read(STDIN_FILENO, &c, 1)) != 1) {
        if (nread == -1 && errno != EAGAIN) {
            editor_error("read");
            return KeyPress::UNKNOWN; 
        }
    }

    if (c == '\x1b') {
        char seq[2];

        int r0;
        while ((r0 = read(STDIN_FILENO, &seq[0], 1)) != 1) {
            if (r0 == -1 && errno != EAGAIN) return KeyPress::ESC;
            if (r0 == 0) return KeyPress::ESC; // real EOF
        }

        int r1;
        while ((r1 = read(STDIN_FILENO, &seq[1], 1)) != 1) {
            if (r1 == -1 && errno != EAGAIN) return KeyPress::ESC;
            if (r1 == 0) return KeyPress::ESC;
        }

        if (seq[0] == '[' || seq[0] == '0') {
            if (seq[1] == 'A') return KeyPress::ARROW_UP;
            else if (seq[1] == 'B') return KeyPress::ARROW_DOWN;
            else if (seq[1] == 'C') return KeyPress::ARROW_RIGHT;
            else if (seq[1] == 'D') return KeyPress::ARROW_LEFT;
            else return KeyPress::UNKNOWN;
        }
        else return KeyPress::UNKNOWN;
    }
    else if (c == '\n') return KeyPress::ENTER;
    else if (c == 3) return KeyPress::CTRL_C;
    else if (c == 127 || c == 8) return KeyPress::BACKSPCE;
    else if (c >= 32 && c <= 126) return KeyPress::CHAR;
    return KeyPress::UNKNOWN;
}

std::string shellb_read_line() {
    char c;
    std::string line;
    std::size_t cursor_position = 0, history_position = command_history.size();
    std::string arrow_handling;

    while (true) {
        KeyPress k = read_keypress(c);
        switch (k) {
            case KeyPress::CHAR:
                line.insert(cursor_position, 1, c);
                display_line(line);
                cursor_position++;
                update_cursor(cursor_position);
                break;

            case KeyPress::BACKSPCE:
                if (cursor_position > 0) {
                    cursor_position--;
                    line.erase(cursor_position, 1);
                    display_line(line);
                    update_cursor(cursor_position);
                }
                break;

            case KeyPress::ENTER:
                write(STDOUT_FILENO, "\r\n", 2);
                if (!line.empty()) command_history.push_back(line);
                return line;

            case KeyPress::ARROW_RIGHT:
                if (cursor_position < line.length()) cursor_position++;
                update_cursor(cursor_position);
                break;

            case KeyPress::ARROW_LEFT:
                if (cursor_position > 0) cursor_position--;
                update_cursor(cursor_position);
                break;

            case KeyPress::ARROW_UP:
                if (history_position > 0) {
                    if (history_position == command_history.size()) {
                        arrow_handling = line;   
                    }
                    history_position--;
                    line = command_history[history_position];
                    display_line(line);
                    cursor_position = line.size();
                    update_cursor(cursor_position);
                }
                break;

            case KeyPress::ARROW_DOWN:
                if (history_position < command_history.size()) {
                    history_position++;
                    if (history_position == command_history.size()) {
                        line = arrow_handling;                      
                    } else {
                        line = command_history[history_position];
                    }
                    display_line(line);
                    cursor_position = line.size();
                    update_cursor(cursor_position);
                }
                break;

            case KeyPress::CTRL_C:
                write(STDOUT_FILENO, "^C\r\n", 4); 
                line.clear();
                cursor_position = 0;
                history_position = command_history.size();
                return line;

            case KeyPress::ESC:
                break;

            default:
                break;
        }
    }
}   
