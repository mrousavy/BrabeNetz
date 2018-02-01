#!/bin/bash

echo "### BUILDING LIBRARY ##"
cd BrabeNetz
cmake -D CMAKE_BUILD_TYPE=Release CMakeLists.txt
make
cd ..
echo "# BUILDING EXECUTABLE #"
cd BrabeNetzConsole
cmake -D CMAKE_BUILD_TYPE=Release CMakeLists.txt
make
cd ..
echo "######## DONE #########"
echo "Output File is located at $PWD/BrabeNetzConsole/bin/"

