cmake_minimum_required(VERSION 3.31)
project(connectFourAI
        LANGUAGES C CXX
)

add_compile_options(-O3)

add_executable(connectFourAI main.cpp
        GameState.cpp
        GameState.h
        cfai.cpp
        cfai.h
        eval.c
        eval.h)

target_compile_features(connectFourAI PRIVATE cxx_std_20)
target_compile_features(connectFourAI PRIVATE c_std_17)

target_link_libraries(connectFourAI PRIVATE tensorflow)