cmake_minimum_required(VERSION 3.9)
project(BrabeNetzConsole)
set(CMAKE_CXX_STANDARD 14)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(BRABENETZ_LIB "${CMAKE_CURRENT_SOURCE_DIR}/../BrabeNetz")

include_directories(${BRABENETZ_LIB})

find_package(OpenMP)
if (OPENMP_FOUND)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
endif()

add_executable(BrabeNetzConsole BrabeNetzConsole.cpp Helper.h Trainer.cpp Trainer.h Console.cpp Console.h stdafx.h)

target_link_libraries(BrabeNetzConsole ${BRABENETZ_LIB}/cmake-build-debug/libBrabeNetz.a)
