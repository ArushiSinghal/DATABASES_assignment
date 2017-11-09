#!/bin/bash
sudo apt-get update
sudo apt-get upgrade
sudo apt-get install
sudo apt-get install vim

g++ -std=c++11 -static code/av2.cpp 
#input file (R) , output file(sorted R) , number of blocks in main memory
./a.out input.txt output.txt 100

g++ -std=c++11 -static code/av3.cpp
#input file (S) , output file(sorted S) , number of blocks in main memory
./a.out input1.txt output1.txt 100 

g++ -std=c++11 -static code/code.cpp
time ./a.out
#time ./a.out /home/seema/DBMS/Implementing_Join/201516178_Assign4/input/R /home/seema/DBMS/Implementing_Join/201516178_Assign4/input/S hash 100
