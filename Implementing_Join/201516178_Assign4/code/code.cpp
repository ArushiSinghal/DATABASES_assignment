#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <string>
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
int main(int argc, char* argv[])
{
	string r_filename_path =  argv[1];
	string s_filename_path =  argv[2];
	string type = argv[3];
	long long int buff  = stoi(argv[4]);
	long long int var1 = r_filename_path.length();
	long long int var2 = s_filename_path.length();
	int i;
	for(i=var1-1;i>=0;i--)
	{
		if (r_filename_path[i] == '/')	
		{
			break;
		}
	}
	cout << i << endl;
	string r_filename = r_filename_path.substr(i+1,var1-i-1); 
	for(i=var2-1;i>=0;i--)
        {
                if (s_filename_path[i] == '/')  
                {
                        break;
                }
        }
	cout << i << endl;
	string s_filename = s_filename_path.substr(i+1,var2-i-1);
	string output_file = s_filename + "_" + r_filename + "_" + "join";
	cout << output_file << endl; 
	return 0;
}
