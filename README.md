# FinalProject
Final Project for COP3530

# Required tools
This project requires the GNU g++ ccompiler and GNU make to compile. Other compilers will probably work, but custom build systems will have to be implemented. This shouldn't be too difficult, though.
Additionally, batch expression generation requires NodeJS, a non-browser JavaScript interpreter. This is needed to evaluate expressions, to provide a "source of truth" to compare the various algorithms' output against. Because JavaScript is interpreted, the expressions can be evaluated directly without compilation (a g++-based solution was investigated, but compile times were exorbitant).

# Expressions
Expressions can be generated using the `make expressions` command. This commmand compiles a C++ file, which generates a JavaScript file. This JavaScrip file, when executed automatically using a system call to NodeJS, outputs expression answer and expression in a CSV format to stdout. This can then redirected to a file, and used with the program. The expression generator can be seeded with a number (the default seed used by the Makefile is 5829 as a command line argument, to generate a different set of expressions.

# Usage
To compile the program, simply run `make`. The program can be executed in a standalone fashion, using simply `./main`, and presents a simple TUI which exposes expression evaluators for each algorithm and batch evaluation. It can also be run with an argument, i.e. `./main expressions.csv`, which will just run batch evaluation on that file, and then exit.

# Video
A video for the project is included in the repository (titled "FinalProjectVideo.mp4"), and can also be seen here:
http://willmccoy.xyz/FinalProjectVideo.mp4
