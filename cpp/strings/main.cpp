#include <iostream>
#include <string>

// It's best to pass strings as references so we don't make a copy of them
// when calling a function.
// In this case, we use const to indicate the original string will not be
// modified.
void ReadOnlyStringOperation(const std::string &str)
{
    std::cout << str << std::endl;
}

int main()
{
    std::string name = std::string("Potato") + " Salad";
    std::cout << "Example string: " << name << std::endl;

    // Check the length of the string.
    std::cout << "Example string length: " << name.length() << std::endl;

    // Check if a string contains a substring.
    std::cout << "Example string contains \"to\": " << (name.find("to") != std::string::npos ? "yes" : "no") << std::endl;
    std::cout << "Example string contains \"do\": " << (name.find("do") != std::string::npos ? "yes" : "no") << std::endl;

    ReadOnlyStringOperation(name);

    // If a C style string is declared, it must be const.
    // char* incorrect = "c string";
    // const char* correct = "c string";

    return 0;
}