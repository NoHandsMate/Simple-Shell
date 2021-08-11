#! /bin/bash

g++ *.cpp -Wall -Wextra -Wpedantic -fsanitize=address -std=c++20 -o shell
