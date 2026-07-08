# shellb
A Unix shell built from scratch in C++, implementing core shell behavior including built-in commands, external command execution, a customizable prompt, and a raw-mode line editor with arrow-key navigation.
## Features
- **Built-in commands:**
  - `cd` — change directory (supports `cd` with no args → home directory)
  - `help` — list available built-in commands
  - `exit` — exit the shell
  - `showpath` — show the current working directory in the prompt
  - `hidepath` — hide the current working directory from the prompt
  - `history` — list previously run commands
- **External command execution** — runs any standard system command (e.g. `ls`, `grep`, `cat`) via `fork`/`exec`
- **Custom line editor (raw terminal mode):**
  - Arrow key navigation — move the cursor left/right within a line
  - Command history recall — Up/Down arrows cycle through previous commands
  - Backspace, in-place line editing
- Modular codebase separating parsing, execution, I/O, editor, and built-ins into distinct files
## Tech Stack
- C++17
- POSIX system calls (`fork`, `exec`, `chdir`, `getcwd`, `termios`)
## Project Structure
```
main.cpp               # entry point
shellbStart.cpp/.h     # startup, raw mode setup, banner
shellbLoop.cpp/.h      # main read-eval loop, prompt logic
shellbRead.cpp/.h      # reads raw input, handles keypresses and history navigation
shellbEditor.cpp/.h    # raw terminal mode, cursor control, line redraw
shellbParse.cpp/.h     # tokenizes input into commands/arguments
shellbExecute.cpp/.h   # dispatches to builtins or forks external processes
shellbBuiltins.cpp/.h  # implementations of cd, help, exit, showpath, hidepath, history
```
## Build & Run
**Requirements:** a C++17-compatible compiler (`g++` or `clang++`), macOS/Linux (POSIX APIs).
```bash
make
./shell
```
To clean build artifacts:
```bash
make clean
```
## Usage Example
```
/Users/you/Documents # ls
Report.pdf   Notes.txt
/Users/you/Documents # hidepath
# cd ..
# pwd
/Users/you
# history
1  ls
2  hidepath
3  cd ..
4  pwd
# exit
```
## Author
Saksham Bhadani
