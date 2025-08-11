//
// Created by jkirc on 8/10/2025.
//

#ifndef DEMANGLE_H
#define DEMANGLE_H

#include <string>
#include <iostream>
#include <windows.h>
#include <cxxabi.h>
#include <memory>

class Demangler {
public:
    static std::string demangle(const char* name) {
        int status = -4;  // some arbitrary value to eliminate compiler warning
        std::unique_ptr<char, void(*)(void*)> res {
            abi::__cxa_demangle(name, NULL, NULL, &status),
            std::free
        };
        return (status == 0) ? res.get() : name;
    }
};

#endif //DEMANGLE_H
