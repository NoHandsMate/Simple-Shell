#! /bin/zsh

export LS_DIR="/home/lorenzo/Programming/SimpleShell/commands_src/ls/bin/ls"
export CAT_DIR="/home/lorenzo/Programming/SimpleShell/commands_src/cat/bin/cat"
g++ *.cpp -Wall -Wextra -Wpedantic -fsanitize=address -std=c++20 -o shell
