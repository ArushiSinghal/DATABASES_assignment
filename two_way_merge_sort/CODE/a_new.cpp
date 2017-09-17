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

int arrange(string split1[100],string split2[100],long long int cal,long long int column_name[1000],long long int i, long long int j, string a1)
{
  string aa = "asc";
  string bb = "desc";
  int l1 = i;
  int l2 = j;
  if (a1 == aa)
  {
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
  }
  else
  {
    for (int i=0;i<cal;i++)
    {
      if (split1[column_name[i]].compare(split2[column_name[i]]) < 0 || (split1[column_name[i]].compare(split2[column_name[i]]) == 0 && i==cal-1 &&  b[l1] > b[l2]))
      {
        string m = a[l2];
        a[l2] = a[l1];
        a[l1] = m;
        int p = b[l2];
        b[l2] = b[l1];
        b[l1] = p;
        return 1;
      }
      else if (split1[column_name[i]] > split2[column_name[i]])
      {
        return 0;
      }
    }
  }
  return 0;
}


void sort_phase(long long int column_name[1000],long long int cal,string a1,long long int num_of_record,string val[20][3],long long int num_rows)
{
  string split1[100],split2[100];
  char spaceman = ' ';
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

void sort(long long int column_name[1000],long long int cal,string a1,long long int num_of_record,string val[20][3],long long int num_rows)
{
  string split1[100],split2[100];
  char spaceman = ' ';
  long long int num1,num2;
  for (long long int i=0;i<num_of_record;i++) {
    int count11 = 0;
    for (long long int f = 0;f<num_rows;f++)
    {
      split1[f] = a[i].substr(2*f+count11,stoi(val[f][1]));
      count11 += stoi(val[f][1]);
    }
    num1 = num_rows;
    for (long long int j=i+1;j<num_of_record;j++) {
      int count11 = 0;
      for (long long int f = 0;f<num_rows;f++)
      {
        split2[f] = a[j].substr(2*f+count11,stoi(val[f][1]));
        count11 += stoi(val[f][1]);
      }
      num2 = num_rows;
	int flag = arrange(split1,split2,cal,column_name,i,j,a1);
      if (flag == 1)
      {
        for (int m=0;m<num2;m++)
          split1[m] = split2[m];
      }
      }
    }
  return;
}

int main(int argc, char* argv[]) {
  long long int number_of_lines = 0;
  long long int no_of_lines = 0;
  long long int column_name[1000],num_of_rows,iteration;
  long long int sum_of_each_tuple = 0;
  string line, p, val[4][3];
  long long int memory = stoi(argv[3])*1048576;
  long long int cal = argc - 5;
  long long int var = 0;
  long long int new_num_record;
  ifstream myfile,metafile;
  myfile.open(argv[1]);
  metafile.open("metadata.txt");
  if (!metafile || !myfile)
    {
      cout << "There was an error opening the file.\n";
      return 0;
    }
  while (getline(myfile, line))
    ++number_of_lines;
  while (getline(metafile, line))
    ++no_of_lines;
  metafile.close();
  myfile.close();

  metafile.open("metadata.txt");
  num_of_rows = no_of_lines;
  for(int countRows = 0; countRows < num_of_rows; countRows++)
    {
        for(int countColumns = 0; countColumns < 2; countColumns++)
        {
            metafile >> val[countRows][countColumns];
            if (countColumns == 1)
            sum_of_each_tuple += stoi(val[countRows][countColumns]);
        }
    }
  sum_of_each_tuple = sum_of_each_tuple + 2*(num_of_rows-1) + 2;
  metafile.close();

  for (int i = 0;i<cal;i++)
  {
    p = argv[i+5];
    for (int k=0;k<num_of_rows;k++)
    {
      if (p == val[k][0])
      {
      column_name[i] = k;
      var += 1;
      break;
      }
    }
  }
  if (var != cal || cal <= 0)
  {
    cout << "column name is not matching with metadata\n";
    return 0;
  }

  ////////////////////////PHASE 1//////////////////////////////////////////////
  //ofstream ofs("output1.txt", ios::out | ios::trunc);
  //ofs.close ();
  string a1 = "asc";
  string a2 = "desc";
  myfile.open(argv[1]);
  if (argv[4] == a2 or argv[4] == a1)
  {

      long long int num_of_record = memory/sum_of_each_tuple;
      new_num_record = num_of_record;
      iteration = number_of_lines/num_of_record;
      if (number_of_lines%num_of_record != 0)
        iteration += 1;
      for (long long int l = 1; l<= iteration; l++)
      {
        if (num_of_record*l > number_of_lines)
        num_of_record = number_of_lines - (l-1)*num_of_record;
        for(long long int k = 0;k<num_of_record;k++)
        {
            getline(myfile, a[k], '\n');
            b[k] = k;
        }
	sort (column_name,cal,argv[4],num_of_record,val,no_of_lines);
          string filenames = "firstsort";
          filenames = filenames + to_string(l);
          filenames =  filenames + ".txt";
          ofstream ofs(filenames, ios::out | ios::trunc);
          for (long long int i= 0;i<num_of_record;i++)
          {
            ofstream log(filenames, std::ios_base::app | std::ios_base::out);
            a[i] = a[i].substr(0, a[i].size());
            log << a[i] << "\n";
          }
      }
  }
  else
  {
    cout << "type correct order in which you want to sort the file.\n";
    return 0;
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
    if( !myfiles[i].eof())
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
  cout << a[0] << "\n";
  ofstream log(argv[2], ios_base::app | ios_base::out);
  a[0] = a[0].substr(0, a[0].size());
  log << a[0] << "\n";
  getline(myfiles[b[0]], a[0], '\n');
}
	return 0;
}
