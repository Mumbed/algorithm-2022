cmake_minimum_required(VERSION 3.21)
project(C)

set(CMAKE_C_STANDARD 99)

add_library(library.c cmake-build-debug/test.cpp wontest.c)
