cmake_minimum_required(VERSION 3.9)
project(Linux)

set(CMAKE_CXX_STANDARD 14)

add_library(Linux BrabeNetz.cpp Functions.h Network.h Neuron.cpp BrabeNetz.h Connection.cpp Layer.cpp NetworkTopology.cpp Neuron.h Connection.h Layer.h Network.cpp NetworkTopology.h Properties.h)