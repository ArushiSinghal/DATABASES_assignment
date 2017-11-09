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
using namespace std;
string a[6000000];
long long int b[6000000];
string leff[6000000];
long long int b1[6000000];
int Merge_second(long long int ini,long long int mid,long long int fin)
{
	for(long long int i=ini;i<=fin;i++)
	{
		leff[i] = a[i];
		b1[i] = b[i];
	}
	long long int k =  ini;
	long long int j = mid + 1;
	long long int m = ini;
	while(k<=mid && j<=fin)
	{
		long long int var1, var2;
		int aa, bb;
		istringstream twonumbers;
		twonumbers.str(leff[k]);
		twonumbers >> aa >> bb;
		var1 = bb;
		twonumbers.str(leff[j]);
		twonumbers >> aa >> bb;
		var2 = bb;
		if (var2 <= var1)
		{
			a[m] = leff[j];
			b[m] = b1[j];
			j++;
			m++;
			break;
		}
		else
		{
			a[m] = leff[k];
			b[m] = b1[k];
			k++;
			m++;
			break;
		}
	}
	while (k<=mid)
	{
		a[m] = leff[k];
		b[m] = b1[k];
		m++;
		k++;
	}
	while (j<=fin)
	{
		a[m] = leff[j];
		b[m] = b1[j];
		m++;
		j++;
	}
	return 0;
}

int Merge(long long int ini,long long int mid,long long int fin)
{
	for(long long int i=ini;i<=fin;i++)
	{
		leff[i] = a[i];
	}
	long long int k =  ini;
	long long int j = mid + 1;
	long long int m = ini;
	while(k<=mid && j<=fin)
	{
		long long int var1, var2;
		string a, b;
		istringstream twonumbers (leff[k]);
		twonumbers.str(leff[k]);
		twonumbers >> a >> b;
		var1 = stoi(b);
		twonumbers.str(leff[j]);
		twonumbers >> a >> b;
		var2 = stoi(b);
		if (var2 <= var1)
		{
			a[m] = leff[j];
			j++;
			m++;
			break;
		}
		else
		{
			a[m] = leff[k];
			k++;
			m++;
			break;
		}
	}
	while (k<=mid)
	{
		a[m] = leff[k];
		m++;
		k++;
	}
	while (j<=fin)
	{
		a[m] = leff[j];
		m++;
		j++;
	}
	return 0;
}
void sorting(long long int num_of_record,long long int initial, int flag)
{
	if(initial == num_of_record-1)
		return;
	long long int mid = (initial+num_of_record-1)/2;
	sorting(mid+1,initial,flag);
	sorting(num_of_record,mid+1,flag);
	if (flag == 0)
		Merge(initial,mid,num_of_record-1);
	else
		Merge_second(initial,mid,num_of_record-1);
	return;
}

int main(int argc, char* argv[]) {
	long long int memory = stoi(argv[3])*100;
	ifstream myfile;
	myfile.open(argv[1]);
	long long int buffer = 0;
	string line;
	while (getline(myfile, line))
	{
		a[0] = line;
		long long int count = 1;
		while (getline(myfile, line))
		{
			a[count] = line;
			count += 1;
			if (count == memory)
				break;
		}
		sorting(count,0,0);
		string filenames = "firstsort";
		filenames = filenames + to_string(buffer);
		filenames =  filenames + ".txt";
		ofstream ofs(filenames, ios::out | ios::trunc);
		for (long long int i= 0;i<count;i++)
		{
			ofstream log(filenames, std::ios_base::app | std::ios_base::out);
			a[i] = a[i].substr(0, a[i].size());
			log << a[i] << "\n";
		}
		buffer += 1;
	}
	myfile.close();
	////////////////////////////////second phase///////////////////////
	ifstream myfiles[2000];
	for(int i=0;i< buffer;i++)
	{
		string file = "firstsort" + to_string(i) + ".txt";
		myfiles[i].open(file);
	}
	int count;
	ofstream ofs(argv[2], ios::out | ios::trunc);
	while(1)
	{
		count = 0;
		for(int i=0;i< buffer;i++)
		{
			if(myfiles[i].eof() || myfiles[i].peek() == EOF)
				{
					int p;
				}
			else
			{
				streampos oldpos = myfiles[i].tellg();  // stores the position
				getline(myfiles[i], a[count], '\n');
				myfiles[i].seekg (oldpos);   // get back to the position
				b[count] = i;
				count +=1;
			}
		}
		if (count == 0)
			break;
		sorting(count,0,1);
		ofstream log(argv[2], ios_base::app | ios_base::out);
		a[0] = a[0].substr(0, a[0].size());
		log << a[0] << "\n";
		getline(myfiles[b[0]], a[0], '\n');
	}
	return 0;
}
