#include <iostream>
#include <climits>

// Provides std::format from C++ 20.
// As of writing, we need to compile with /std:c++latest using MSVC or
// -std=c++20 on MinGW, Linux, and Mac.
// In order to get Visual Studio Code to acknowledge the existance of
// std::format, we need to set cppStandard to c++20 in the configuration
// within the c_cpp_properties.json.
#include <format>

int main()
{
    char c = 'a';
    short ns = 4;
    int ni = 4;
    long nl = 4;
    float sf = 4.250;
    double df = 4.350;

    std::cout << "C++ 20 formatting"                                     << std::endl;
    std::cout << std::format("CHAR_BIT: {}", CHAR_BIT)                   << std::endl;
    std::cout << "type    value   size"                                  << std::endl;
    std::cout << "-----------------------------"                         << std::endl;
    std::cout << std::format("char   | {:>5} | {:<5} |", c,  sizeof(c))  << std::endl;
    std::cout << std::format("short  | {:>5} | {:<5} |", ns, sizeof(ns)) << std::endl;
    std::cout << std::format("int    | {:>5} | {:<5} |", ni, sizeof(ni)) << std::endl;
    std::cout << std::format("long   | {:>5} | {:<5} |", nl, sizeof(nl)) << std::endl;
    std::cout << std::format("float  | {:>5} | {:<5} |", sf, sizeof(sf)) << std::endl;
    std::cout << std::format("double | {:>5} | {:<5} |", df, sizeof(df)) << std::endl;
    std::cout << std::endl;

    return 0;
}
