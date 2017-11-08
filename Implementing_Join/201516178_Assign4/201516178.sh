#!/bin/bash
sudo apt-get update
sudo apt-get upgrade
sudo apt-get install
sudo apt-get install vim
g++ -std=c++11 -static code/code.cpp
time ./a.out
#time ./a.out /home/seema/DBMS/Implementing_Join/201516178_Assign4/input/R /home/seema/DBMS/Implementing_Join/201516178_Assign4/input/S hash 100
