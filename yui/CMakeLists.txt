#[[make file using cmake -S . -B build/]]
#[[then run cmake --build build/]]
#[[then ./build/yui]]
cmake_minimum_required(VERSION 3.20)

project(yui)

set(CMAKE_CXX_STANDARD 20)

add_executable(yui src/main.cpp)