#!/bin/bash

echo "### BUILDING LIBRARY ##"
cmake -D CMAKE_BUILD_TYPE=Release BrabeNetz
echo "# BUILDING EXECUTABLE #"
cmake -D CMAKE_BUILD_TYPE=Release BrabeNetzConsole
echo "######## DONE #########"

