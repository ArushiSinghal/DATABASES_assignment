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
	for(i=0;i<number_of_blocks;i++)
	{
		ifstream myfile, myfile1;
		string name1 = "firstsort" + to_string(i);
		string name2 = "secondsort" + to_string(i);
		myfile.open(name1);
		myfile1.open(name2);
		ofstream ofs(output_file, ios_base::app | ios_base::out);
		while(1)
			{
				string line1, line2, out;
				if(myfile.eof() || myfile.peek() == EOF || myfile1.eof() || myfile1.peek() == EOF)
					break;
				getline(myfile, line1);
				streampos oldpos1 = myfile1.tellg();  // stores the position
				getline(myfile1, line2);
			  int aa, bb, cc, dd;
				string aaa, bbb, ccc, ddd;
				istringstream twonumbers,twonumbers1, stringtwo1, stringtwo2;
				stringtwo1.str(line1);
				stringtwo2.str(line2);
			  stringtwo1 >> aaa >> bbb;
				stringtwo2 >> ccc >> ddd;
				twonumbers.str(line1);
				twonumbers >> aa >> bb;
				var1 = bb;
				twonumbers1.str(line2);
				twonumbers1 >> cc >> dd;
				var2 = cc;
				if (var1 == var2)
				{
					out = aaa + " " + bbb + " " + ddd;
		  		ofs << out << "\n";
				}
				while(getline(myfile1, line2))
				{
						istringstream twonumbers3, stringtwo3;
						twonumbers3.str(line2);
					  twonumbers3 >> cc >> dd;
						stringtwo3.str(line2);
						stringtwo3 >> ccc >> ddd;
						var2 = cc;
						if (var2 == var1)
						{
							out = aaa + " " + bbb + " " + ddd;
							ofs << out << "\n";
						}
				}
				myfile1.close();
				myfile1.open(name2);
				myfile1.seekg(oldpos1);
			}
			myfile.close();
			myfile1.close();
	}
	return 0;
}
