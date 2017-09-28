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
using namespace std;
long long int distinct_tuples, tuples_one_block, total_tuples, number_of_blocks;
string filenames =  "input.csv";
string output_file = "output.csv";

/**************************** INPUT FILE GENERATION ********************************/
int input_file_generate(int attributes,int  duplicate, long long int block)
{
	int j,i;
	string A[100];
	filenames =  "input.csv";
	ofstream ofs(filenames, ios::out | ios::trunc);
	long long int count = 0;
	while(1)
	{
		ifstream in(filenames, ifstream::ate | ifstream::binary);
		long long int memory = in.tellg();
		if(memory > 1073741824)
			break;
		ofstream log(filenames, std::ios_base::app | std::ios_base::out);
		count += 1;
		for(i=0;i<(100-duplicate);i++)
		{
			int a;
			if(attributes == 1)
			{
				a = rand()%1001;
				log << a << "\n";
				A[i] = to_string(a);
			}
			else
			{
				a = rand()%1001;
				log << a << ",";
				A[i] = to_string(a) + ",";
				for(j=2;j<=attributes-1;j++)
				{
					a = rand()%1001;
					log << a << ",";
					A[i] = A[i] + to_string(a) + ",";
				}
				a = rand()%1001;
				log << a << "\n";
				A[i] = A[i] + to_string(a);
			}
		}
		for(i=0;i<duplicate;i++)
		{
			int val = rand()%(100-duplicate);
			log << A[val] << "\n";
		}
	}
	distinct_tuples = count*100- duplicate*count;
	tuples_one_block = distinct_tuples/block;
	total_tuples = count *100;
	ofs.close();
	return 0;
}

/**************  duplicacy elimination using two phase hashing **********************************************/
int hashing(long long int attributes)
{
	ifstream input_file(filenames);
	long long int i,j;
	string data;
	ifstream fi;
	fi.open(filenames);
	string b,a;
	ifstream myfile;
	for(int i=0;i<number_of_blocks;i++)
	{
		string file = "firstsort" + to_string(i) + ".csv";
		myfile.open(file);
		ofstream files(file, ios::out | ios::trunc);
		file = "secondsort" + to_string(i) + ".csv";
		myfile.open(file);
		ofstream fil(file, ios::out | ios::trunc);
	}
	for(i=0;i<total_tuples;i++)
	{
		getline(fi, a, '\n');
		long long int count = 0;
		for(j=0;j<attributes-1;j++)
		{
			getline(input_file, data, ',');
			count  += stoi(data);
		}
		getline(input_file, data);
		count += stoi(data);
		count = count%(number_of_blocks);
		string file = "firstsort" + to_string(count) + ".csv";
		ofstream log(file, ios_base::app | ios_base::out);
		log << a << "\n";
	}
	fi.close();

	for(int i=0;i<number_of_blocks;i++)
	{
		string file = "firstsort" + to_string(i) + ".csv";
		ifstream file_check(file);
		string p,c;
		while(!file_check.eof())
		{
			getline(file_check, p, '\n');
			string dupl_file = "secondsort" + to_string(i) + ".csv";
			ifstream no_duplicate(dupl_file);
			int  k =0;
			while(!no_duplicate.eof())
			{
				getline(no_duplicate, c, '\n');
				if (p==c)
				{
					k = 1;
					break;
				}
			}
			if (k==0)
			{
				string file = "secondsort" + to_string(i) + ".csv";
				ofstream log(file, ios_base::app | ios_base::out);
				log << p << "\n";
			}
		}
	}
	return 0;
}
int btree()
{
	return 0;
}

int main(int argc, char* argv[])
{
	//Attribute, duplicacy percentage, number of blocks in main memory, type_of_index
	input_file_generate(stoi(argv[1]),stoi(argv[2]), stoi(argv[3]));
	number_of_blocks = stoi(argv[3]);
	string index_type =  argv[4];
	string a = "hash";
	if (a == index_type)
		hashing(stoi(argv[1]));
	else
		btree();
	return 0;
}
