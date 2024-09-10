cmake_minimum_required(VERSION 3.28)
project(CellularAutomata)

include(FetchContent)
set(BUILD_SHARED_LIBS OFF)

FetchContent_Declare(
        SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.1
)
FetchContent_MakeAvailable(SFML)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED true)

add_executable(CellularAutomata src/main.cpp
        src/GameOfLife.cpp
        src/GameOfLife.hpp
)

target_link_libraries(CellularAutomata sfml-graphics sfml-system sfml-audio sfml-window sfml-network)