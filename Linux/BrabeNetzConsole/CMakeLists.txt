cmake_minimum_required(VERSION 3.8)
project(BrabeNetzConsole)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES BrabeNetzConsole.cpp Console.h Helper.h Trainer.cpp Trainer.h)
add_executable(BrabeNetzConsole ${SOURCE_FILES})