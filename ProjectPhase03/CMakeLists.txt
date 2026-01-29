cmake_minimum_required(VERSION 3.10)
project(ProjectPhase03)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(ProjectPhase03
        main.cpp
        testExp.cpp
        expr.cpp
        cmdline.cpp
)
