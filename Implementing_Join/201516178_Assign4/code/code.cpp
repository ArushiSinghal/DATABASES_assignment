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
string a[6000000];
long long int b[6000000];
string leff[6000000];
long long int b1[6000000];
int flag_sort;
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
                istringstream twonumbers,twonumbers1;
                twonumbers.str(leff[k]);
                twonumbers >> aa >> bb;
		if (flag_sort == 0)
                var1 = bb;
		else
		var1 = aa;
                twonumbers1.str(leff[j]);
                twonumbers1 >> aa >> bb;
		if (flag_sort == 0)
                var2 = bb;
		else
		var2 = aa;
		if (var2 <= var1)
		{
			a[m] = leff[j];
			b[m] = b1[j];
			j++;
			m++;
		}
		else
		{
			a[m] = leff[k];
			b[m] = b1[k];
			k++;
			m++;
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
                int aa, bb;
                istringstream twonumbers,twonumbers1;
                twonumbers.str(leff[k]);
                twonumbers >> aa >> bb;
                if (flag_sort == 0)
                var1 = bb;
                else
                var1 = aa;
                twonumbers1.str(leff[j]);
                twonumbers1 >> aa >> bb;
                if (flag_sort == 0)
                var2 = bb;
                else
                var2 = aa;
		if (var2 <= var1)
		{
			a[m] = leff[j];
			j++;
			m++;
		}
		else
		{
			a[m] = leff[k];
			k++;
			m++;
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

int main_function(string input_filesname,string output_filenames ,long long int blocks) {
	long long int memory = blocks*100;
	ifstream myfile;
	myfile.open(input_filesname);
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
	long long int count;
	ofstream ofs(output_filenames, ios::out | ios::trunc);
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
		ofstream log(output_filenames, ios_base::app | ios_base::out);
		a[0] = a[0].substr(0, a[0].size());
		log << a[0] << "\n";
		getline(myfiles[b[0]], a[0], '\n');
	}
	return 0;
}


int main(int argc, char* argv[])
{
	string r_filename_path =  argv[1];
	string s_filename_path =  argv[2];
	string type = argv[3];
	string output1_sort = "output1";
	string output2_sort = "output2";
	ofstream v1(output1_sort, ios::out | ios::trunc);
        v1.close();
	ofstream v2(output1_sort, ios::out | ios::trunc);
        v2.close();
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
	string r_filename = r_filename_path.substr(i+1,var1-i-1); 
	for(i=var2-1;i>=0;i--)
        {
                if (s_filename_path[i] == '/')  
                {
                        break;
                }
        }
	string s_filename = s_filename_path.substr(i+1,var2-i-1);
	string output_file = r_filename + "_" + s_filename + "_" + "join";
	ofstream v(output_file, ios::out | ios::trunc);
	v.close();
	flag_sort = 0;
	main_function(r_filename_path, output1_sort,buff);
	flag_sort = 1;
        main_function(s_filename_path, output2_sort,buff);
	ifstream myfile,myfile1;
	myfile.open(output1_sort);
	myfile1.open(output2_sort);
	ofstream ofs(output_file, ios_base::app | ios_base::out);
	while(1)
	{
		string line1, line2, out;
		if(myfile.eof() || myfile.peek() == EOF)
    			{
				break;
			}
		if(myfile1.eof() || myfile1.peek() == EOF)
                        {
                                break;
                        }
		streampos oldpos = myfile.tellg();  // stores the position
      		getline(myfile, line1);
      		//myfile.seekg (oldpos);   // get back to the position
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
		if (var1 < var2)
		{
			myfile1.seekg(oldpos1);
		}
		else if (var2 < var1)
		{
			myfile.seekg(oldpos);
		}
		else
		{
			//out = to_string(aa) + " " + to_string(bb) + " " + to_string(dd);
			out = aaa + " " + bbb + " " + ddd;
			//ofstream ofs(output_file, ios_base::app | ios_base::out);
  			ofs << out << "\n";
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
					  //out = to_string(aa) + " " + to_string(bb) + " " + to_string(dd);
					  out = aaa + " " + bbb + " " + ddd;
					  //ofstream ofs(output_file, ios_base::app | ios_base::out);
                        		  ofs << out << "\n";
					}
				  else
					break;	
			}
			myfile1.close();
			myfile1.open(output2_sort);
			myfile1.seekg(oldpos1);	
		}
	}
	ofs.close();
	myfile.close();
	myfile1.close();
	return 0;
}
