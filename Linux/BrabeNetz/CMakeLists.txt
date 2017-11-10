cmake_minimum_required(VERSION 3.8)
project(BrabeNetz)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES Connection.cpp Connection.h Extensions.cpp Extensions.h Functions.cpp Functions.h Layer.cpp Layer.h Network.cpp Network.h NetworkTopology.cpp NetworkTopology.h Neuron.cpp Neuron.h)
add_library(BrabeNetz ${SOURCE_FILES})