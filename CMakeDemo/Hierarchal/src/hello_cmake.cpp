// hello_cmake.cpp

#include <iostream>
#include <string>
#include "helper.h"
#include "../libs/hello_lib/hello_lib.h"

auto putl = [] { std::cout << "\n"; };

int main() {
    std::cout << "\n  Hello CMake";
    std::cout << "\n  " << do_help("a string argument");
    std::cout << "\n  " << lib_help();
    putl(); 
}