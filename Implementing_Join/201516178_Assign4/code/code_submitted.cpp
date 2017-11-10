#include <unordered_map>
#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <string>
#include <iterator>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include <stdexcept>
#include <vector>
#include <sstream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <ios>
#include <ctime>
#include <cstdio>
using namespace std;
long long int number_of_blocks;
ifstream input_file;
string filenames;

void first_phase_r()
{
	long long int i,j;
	string a,data;
	for(int i=0;i<number_of_blocks;i++)
	{
		string file = "firstsort" + to_string(i);
		ofstream files(file, ios::out | ios::trunc);
		files.close();
	}
	while(getline(myfile, line))
	{

                long long int aa, bb;
                istringstream twonumbers;
                twonumbers.str(line);
                twonumbers >> aa >> bb;
		long long int data = bb%number_of_blocks;
		string file = "firstsort" + to_string(data);
		ofstream log(file, ios_base::app | ios_base::out);
                log << line << "\n";
	}
	fi.close();
	return;
}
void first_phase_s()
{
        long long int i,j;
        string a,data;
        for(int i=0;i<number_of_blocks;i++)
        {
                string file = "secondsort" + to_string(i);
                ofstream files(file, ios::out | ios::trunc);
                files.close();
        }
        while(getline(myfile, line))
        {

                long long int aa, bb;
                istringstream twonumbers;
                twonumbers.str(line);
                twonumbers >> aa >> bb;
                long long int data = aa%number_of_blocks;
                string file = "secondsort" + to_string(data);
                ofstream log(file, ios_base::app | ios_base::out);
                log << line << "\n";
        }
        fi.close();
        return;
}

int hash_join(string input_filename, long long int num_blocks ,int hash_flag)
{
	filenames =  input_filename;
	number_of_blocks = num_blocks;
	input_file.open(filenames);
	if (hash_flag == 0)
		first_phase_r();
	else
		first_phase_s();
	input_file.close();
	for(i=0;i<num_blocks;i++)
	{
		ifstream myfile1, myfile2;
		string name1 = "firstsort" + to_string(i);
		string name2 = "secondsort" + to_string(i);
		myfile1.open(name1);
		myfile2.open(name2);
		while(1)
			{




			}

	}
	return 0;
}
