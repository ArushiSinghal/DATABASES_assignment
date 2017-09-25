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
int main(int argc, char* argv[])
{
	//numberofatributes argv[1]
	//numberofrows arg[2]
	//percentage ofduplicacy argv[3]
	long long int attributes = stoi(argv[1]);
	long long int rows = stoi(argv[2]);
	long long int duplicate = (rows*(stoi(argv[3])))/100;
	long long int no_duplicate = rows - duplicate;
	for (int i=0;i<100;i++)
	{
		
		int a = rand()%1001;
		if (a==0)
			cout << "1" << "\n";
		cout << a  << "\n";
	}
	return 0;
}
