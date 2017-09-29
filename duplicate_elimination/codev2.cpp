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
long long int distinct_tuples, tuples_one_block, total_tuples, number_of_blocks,attributes;
string filenames =  "input.csv";
string output_file = "output.csv";

/**************************** INPUT FILE GENERATION ********************************/
int input_file_generate(int  duplicate, long long int block)
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
		//if(memory > 1073741824)
		//	break;
		if(memory > 500*1024*1024)
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

class HashMap {
	unordered_map<string, bool> recordPresence;
public:
	bool search(string key) {
		if(recordPresence.find(key) == recordPresence.end()) return false;
		return true;
	}
	void insert(string key) {
		if(search(key)==false)
			recordPresence[key]=true;
	}
};
HashMap hash_;
/**************  duplicacy elimination using two phase hashing **********************************************/
int get_next_hashing(ifstream fi,ofstream log)
{
	string b,a,data;
	while(getline(fi,a))
	{
		if(hash_.search(a));
		else {
			hash_.insert(a);
			log << a << "\n";
		}	
	}
	fi.close();
	log.close();
	return 0;
}

int open(string a)
{
string check1 = "hash";
string check2 = "btree";
if (a == check1)
{
	ifstream fi;
	fi.open(filenames);
	ofstream f(output_file, ios::out | ios::trunc);
	f.close();
	ofstream log(output_file, ios_base::app | ios_base::out);
	get_next_hashing(fi,log);
}
//else if (a == check2)
//get_next_btree();
}

int main(int argc, char* argv[])
{
	//Attribute, duplicacy percentage, number of blocks in main memory, type_of_index
	attributes = stoi(argv[1]);
	input_file_generate(stoi(argv[2]), stoi(argv[3]));
	number_of_blocks = stoi(argv[3]);
	string index_type =  argv[4];
	open(index_type)
	return 0;
}
