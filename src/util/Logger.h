#ifndef LOGGER_H
#define LOGGER_H
#include <string>
#include <iostream>
#include <windows.h>

//Class based on logging
class Logger {
public:
    static void initialize(const std::string& message) {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_BLUE);
        std::cout << message << "\n";
    };

    static void warn(const std::string& message) {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN);
        std::cout << message << "\n";
    };

    static void error(const std::string& message) {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
        std::cout << message << "\n";
        throw std::runtime_error("Exited via logger");
    };
};

#endif //LOGGER_H
