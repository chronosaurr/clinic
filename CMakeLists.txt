cmake_minimum_required(VERSION 3.29)
project(clinic2_0)

set(CMAKE_CXX_STANDARD 20)

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(clinic2_0 main.cpp
        menu.cpp
        menu.h)
