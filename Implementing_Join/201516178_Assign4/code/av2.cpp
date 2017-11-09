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

int arrange(string split1[100],string split2[100],long long int cal,long long int column_name[1000],long long int i, long long int j, string a1)
{
	string aa = "asc";
	int l1 = i;
	int l2 = j;
	for (int i=0;i<cal;i++)
	{
		if (split1[column_name[i]].compare(split2[column_name[i]]) > 0 || (split1[column_name[i]].compare(split2[column_name[i]]) == 0 && i==cal-1 &&  b[l1] > b[l2]))
		{
			string m = a[l2];
			a[l2] = a[l1];
			a[l1] = m;
			int p = b[l2];
			b[l2] = b[l1];
			b[l1] = p;
			return 1;
		}
		else if (split1[column_name[i]] < split2[column_name[i]])
		{
			return 0;
		}
	}
	return 0;
}

void sort_phase(long long int num_of_record)
{
	long long int num2;
	int count11 = 0;
	for (long long int f = 0;f<num_rows;f++)
	{
		split1[f] = a[0].substr(2*f+count11,stoi(val[f][1]));
		count11 += stoi(val[f][1]);
	}
	for (long long int j=1;j<num_of_record;j++) {
		count11 = 0;
		for (long long int f = 0;f<num_rows;f++)
		{
			split2[f] = a[j].substr(2*f+count11,stoi(val[f][1]));
			count11 += stoi(val[f][1]);
		}
		num2 = num_rows;
		int flag = arrange(split1,split2,cal,column_name,0,j,a1);
		if (flag == 1)
		{
			for (int m=0;m<num2;m++)
				split1[m] = split2[m];
		}
	}
	return;
}

int Merge(long long int ini,long long int mid,long long int fin)
{
	for(long long int i=ini;i<=mid;i++)
	{
		leff[i] = a[i];
	}
	for(long int i=mid+1;i<=fin;i++)
	{
		leff[i] = a[i];
	}
	long long int k =  ini;
	long long int j = mid + 1;
	long long int m = ini;
		while(k<=mid && j<=fin)
		{
				int var1, var2;
				string a, b;
				istringstram twonumbers (leff[k]);
				twonumbers >> a >> b;
				long long int var1 = stoi(b);
				twonumbers(leff[j]);
                                twonumbers >> a >> b;
                                long long int var2 = stoi(b);	
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
void sort_first_merge(long long int num_of_record,long long int initial)
{
	if(initial == num_of_record-1)
		return;
	long long int mid = (initial+num_of_record-1)/2;
	sort_first_merge(mid+1,initial);
	sort_first_merge(num_of_record,mid+1);
	Merge(initial,mid,num_of_record-1);
	return;
}

int main(int argc, char* argv[]) {
	long long int memory = stoi(argv[3])*100;
	ifstream myfile;
	myfile.open(argv[1]);
	long long int buffer = 0;
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
		sort_first_merge(count,0);
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
	for(int i=1;i<=iteration;i++)
	{
		string file = "firstsort" + to_string(i) + ".txt";
		myfiles[i].open(file);
	}
	int count;
	ofstream ofs(argv[2], ios::out | ios::trunc);
	while(1)
	{
		count = 0;
		for(int i=1;i<=iteration;i++)
		{
			if(myfiles[i].eof() || myfiles[i].peek() == EOF)
			{
				count +=1;
				count = count -1;
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
		sort_phase(column_name,cal,argv[4],count,val,no_of_lines);
		//cout << a[0] << "\n";
		ofstream log(argv[2], ios_base::app | ios_base::out);
		a[0] = a[0].substr(0, a[0].size());
		log << a[0] << "\n";
		getline(myfiles[b[0]], a[0], '\n');
	}
	return 0;
}
