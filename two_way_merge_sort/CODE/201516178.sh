#!/bin/bash
sudo apt-get update
sudo apt-get upgrade
sudo apt-get install
sudo apt-get install vim
./gensort -a 100 input.txt
g++ -std=c++11 -static a.cpp
./a.out input.txt output.txt 100 desc c0 c1 c2
