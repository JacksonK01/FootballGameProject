#pragma once

#include <string>
#include <iostream>
#include <windows.h>
#include <cxxabi.h>
#include <typeinfo>

#include "Demangler.h"


//Class based on logging
class Logger {
public:
    static void log(const std::string& message) {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
        std::cout << message << "\n";
    };

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

    //Prints the class that sent the message. Get "const std::type_info&" by doing typeid(*<class>).
    static void initialize(const std::string& message, const std::type_info& givenClass) {
        std::string className = Demangler::demangle(givenClass.name());

        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
        std::cout << "[" << className << "]: ";

        initialize(message);
    }

    static void warn(const std::string& message, const std::type_info& givenClass) {
        std::string className = Demangler::demangle(givenClass.name());

        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
        std::cout << "[" << className << "]: ";

        warn(message);
    }

    static void error(const std::string& message, const std::type_info& givenClass) {
        std::string className = Demangler::demangle(givenClass.name());

        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
        std::cout << "\n[" << className << "]: ";

        error(message);
    }

    static void log(const std::string& message, const std::type_info& givenClass) {
        std::string className = Demangler::demangle(givenClass.name());

        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
        std::cout << "[" << className << "]: ";

        log(message);
    }
};

