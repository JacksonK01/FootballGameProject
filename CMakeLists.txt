cmake_minimum_required(VERSION 3.30)
project(FootballGameProject)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(external/SFML)

add_executable(FootballGameProject src/main.cpp
        src/Game.cpp)
