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
	//string r_filename_path =  argv[1];
	//string s_filename_path =  argv[2];
	//string type = argv[3];
	//long long int buff  =argv[4];
	long long int var1 = strlen(r_filename);
	long long int var2 = strlen(s_filename);
	for(int i=var1-1;i>=0;i++)
	{
		if (r_filename == '\')	
		{
			break;
		}
	}
	string r_filename = str.substr(i+1,var1-i-1); 
	for(int i=var2-1;i>=0;i++)
        {
                if (r_filename == '\')  
                {
                        break;
                }
        }
	string s_filename = str.substr(i+1,var2-i-1);
	cout << r_filename << endl; // file.ext
	cout << s_filename << endl;     // file 

	return 0;
}
