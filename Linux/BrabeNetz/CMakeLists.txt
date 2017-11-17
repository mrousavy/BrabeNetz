cmake_minimum_required(VERSION 3.8)
project(BrabeNetz)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenMP)
if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
endif()

set(SOURCE_FILES Connection.h Connection.cpp Extensions.h Functions.h Layer.h Layer.cpp Network.h Network.cpp NetworkTopology.h NetworkTopology.cpp Neuron.h Neuron.cpp)
add_library(BrabeNetz ${SOURCE_FILES})