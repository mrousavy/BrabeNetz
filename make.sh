#!/bin/bash

echo "### BUILDING LIBRARY ##"
cd BrabeNetz
cmake -D CMAKE_BUILD_TYPE=Release CMakeLists.txt
cd ..
echo "# BUILDING EXECUTABLE #"
cd BrabeNetzConsole
cmake -D CMAKE_BUILD_TYPE=Release CMakeLists.txt
cd ..
echo "######## DONE #########"

