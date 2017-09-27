
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
int input_file_generate(int attributes,int  duplicate)
{
	int j,i;
	string A[100];
	string filenames =  "input.csv";
	ofstream ofs(filenames, ios::out | ios::trunc);
	while(1)
	{
		ifstream in(filenames, ifstream::ate | ifstream::binary);
		long long int memory = in.tellg();
		if(memory > 1073741824)
			break;
		ofstream log(filenames, std::ios_base::app | std::ios_base::out);
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
	return 0;
}
int main(int argc, char* argv[])
{
	input_file_generate(stoi(argv[1]),stoi(argv[2]));
	return 0;
}
