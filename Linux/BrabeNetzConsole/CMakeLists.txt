cmake_minimum_required(VERSION 3.8)
project(BrabeNetzConsole)

set(CMAKE_CXX_STANDARD 14)

OPTION (USE_OpenMP "Use OpenMP" ON)
IF(USE_OpenMP)
    FIND_PACKAGE(OpenMP)
    IF(OPENMP_FOUND)
        SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
        SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    ENDIF()
ENDIF()

set(SOURCE_FILES BrabeNetzConsole.cpp Console.cpp Console.h Helper.h Trainer.cpp Trainer.h)
add_executable(BrabeNetzConsole ${SOURCE_FILES})