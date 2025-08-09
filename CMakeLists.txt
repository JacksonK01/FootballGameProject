cmake_minimum_required(VERSION 3.30)
project(FootballGameProject)

set(CMAKE_CXX_STANDARD 20)


add_subdirectory(external/SFML)

add_executable(FootballGameProject
        src/main.cpp
        src/util/Logger.h
        src/Game.h
        src/util/math/Vector2D.h
        src/scene/Scene.h
        src/scene/TestScene.h
)

target_link_libraries(FootballGameProject PRIVATE sfml-graphics)
target_include_directories(FootballGameProject PRIVATE external/SFML/include)

