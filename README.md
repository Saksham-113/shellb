# shellb

A Unix shell built from scratch in C++, implementing core shell behavior including built-in commands, external command execution, and a customizable prompt.

## Features

- **Built-in commands:**
  - `cd` — change directory (supports `cd` with no args → home directory)
  - `help` — list available built-in commands
  - `exit` — exit the shell
  - `showpath` — show the current working directory in the prompt
  - `hidepath` — hide the current working directory from the prompt
- **External command execution** — runs any standard system command (e.g. `ls`, `grep`, `cat`) via `fork`/`exec`
- Modular codebase separating parsing, execution, I/O, and built-ins into distinct files

## Tech Stack

- C++17
- POSIX system calls (`fork`, `exec`, `chdir`, `getcwd`)

## Project Structure

```
main.cpp              # entry point
shellbLoop.cpp/.h      # main read-eval loop, prompt logic
shellbRead.cpp/.h      # reads raw input from the user
shellbParse.cpp/.h     # tokenizes input into commands/arguments
shellbExecute.cpp/.h   # dispatches to builtins or forks external processes
shellbBuiltins.cpp/.h  # implementations of cd, help, exit, showpath, hidepath
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
# exit
```

## Author

Saksham Bhadani
