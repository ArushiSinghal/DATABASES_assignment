#!/bin/bash
sudo apt-get update
sudo apt-get upgrade
sudo apt-get install
sudo apt-get install vim
g++ -std=c++11 -static code.cpp
#//Attribute, duplicacy percentage, number of blocks in main memory, type_of_index
time ./a.out 3 5 100 hash
