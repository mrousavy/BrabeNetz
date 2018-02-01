cmake_minimum_required(VERSION 3.9)
project(BrabeNetzConsole)

set(BRABENETZ_LIB "${CMAKE_CURRENT_SOURCE_DIR}/../BrabeNetz")
set(CMAKE_CXX_STANDARD 14)

include_directories(${BRABENETZ_LIB})
#link_directories(${BRABENETZ_LIB}/cmake-build-debug)

find_package(OpenMP)
if (OPENMP_FOUND)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
endif()

add_executable(BrabeNetzConsole BrabeNetzConsole.cpp Helper.h Trainer.cpp Trainer.h Console.cpp Console.h)

#target_include_directories(BrabeNetzConsole PUBLIC
#        ${BRABENETZ_LIB})
target_link_libraries(BrabeNetzConsole ${BRABENETZ_LIB}/cmake-build-debug/libBrabeNetz.a)