cmake_minimum_required(VERSION 3.8)
project(BrabeNetzConsole)

set(BRABENETZ_LIB "${CMAKE_CURRENT_SOURCE_DIR}/../BrabeNetz")
set(CMAKE_CXX_STANDARD 17)

include_directories(${BRABENETZ_LIB})
#link_directories(${BRABENETZ_LIB}/cmake-build-debug)

find_package(OpenMP)
if (OPENMP_FOUND)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
endif()

set(SOURCE_FILES BrabeNetzConsole.cpp Console.h Helper.h Trainer.cpp Trainer.h)
add_executable(BrabeNetzConsole ${SOURCE_FILES})

#target_include_directories(BrabeNetzConsole PUBLIC
#        ${BRABENETZ_LIB})
target_link_libraries(BrabeNetzConsole
        ${BRABENETZ_LIB}/cmake-build-debug/libBrabeNetz.a)