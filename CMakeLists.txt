cmake_minimum_required(VERSION 3.31)
project(connectFourAI)

set(CMAKE_CXX_STANDARD 20)

add_compile_options(-O3)

add_executable(connectFourAI main.cpp
        GameState.cpp
        GameState.h
        cfai.cpp
        cfai.h)
