cmake_minimum_required(VERSION 3.8)
project(BrabeNetz)

set(CMAKE_CXX_STANDARD 14)

OPTION (USE_OpenMP "Use OpenMP" ON)
IF(USE_OpenMP)
    FIND_PACKAGE(OpenMP)
    IF(OPENMP_FOUND)
        SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
        SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    ENDIF()
ENDIF()

set(SOURCE_FILES Connection.cpp Connection.h Extensions.cpp Extensions.h Functions.cpp Functions.h Layer.cpp Layer.h Network.cpp Network.h NetworkTopology.cpp NetworkTopology.h Neuron.cpp Neuron.h)
add_library(BrabeNetz ${SOURCE_FILES})