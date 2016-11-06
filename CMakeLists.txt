cmake_minimum_required (VERSION 2.6)

project (simpleSO)

add_executable(simpleSO WIN32
    src/main.cpp
    src/dispatcher.cpp
    src/process.cpp
)

add_definitions(-std=c++11)
