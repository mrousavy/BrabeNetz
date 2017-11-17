cmake_minimum_required(VERSION 3.8)
project(BrabeNetz)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES Connection.h Connection.cpp Extensions.h Functions.h Layer.h Layer.cpp Network.h Network.cpp NetworkTopology.h NetworkTopology.cpp Neuron.h Neuron.cpp)
add_library(BrabeNetz ${SOURCE_FILES})