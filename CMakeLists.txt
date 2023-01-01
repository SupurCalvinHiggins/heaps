cmake_minimum_required(VERSION 3.24)
project(heaps)


set(CMAKE_CXX_STANDARD 17)


include_directories(src)
add_subdirectory(lib)
add_executable(heaps main.cpp)
