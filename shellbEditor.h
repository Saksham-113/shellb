#pragma once

#include <string>

void shellb_die(std::string s);
void enable_raw_mode();
void clear_screen();
void shellb_start();
void shellb_end();
void editor_error(std::string s);
void display_line(std::string& line);
void update_cursor(int cursor_position = 0);
void disable_raw_mode();
