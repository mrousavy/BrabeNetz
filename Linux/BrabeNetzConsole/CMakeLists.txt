cmake_minimum_required(VERSION 3.8)
project(BrabeNetzConsole)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenMP)
if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
endif()

set(SOURCE_FILES BrabeNetzConsole.cpp Console.h Helper.h Trainer.cpp Trainer.h)
add_executable(BrabeNetzConsole ${SOURCE_FILES})