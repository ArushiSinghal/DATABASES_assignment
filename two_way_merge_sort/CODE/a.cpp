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
using namespace std;

void arrange(string split1[100],string split2[100],long long int b[10000],long long int cal,long long int column_name[1000],string a ,long long int i, long long int j, string a1)
{
  string aa = "asc";
  string bb = "desc";
  if (a1 == aa)
  {
    for (int i=0;i<cal;i++)
    {
      if (split1[column_name[i]].compare(split2[column_name[i]]) > 0 || (split1[column_name[i]].compare(split2[column_name[i]]) == 0 && i==cal-1 &&  b[i] > b[j]))
      {
        string m = a[i];
        a[j] = a[i];
        a[i] = m;
        int p = b[i];
        b[j] = b[i];
        b[i] = p;
        break;
      }
    }
  }
  else
  {
    for (int i=0;i<cal;i++)
    {
      if (split1[column_name[i]].compare(split2[column_name[i]]) < 0 || (split1[column_name[i]].compare(split2[column_name[i]]) == 0 && i==cal-1 &&  b[i] > b[j]))
      {
        string m = a[i];
        a[j] = a[i];
        a[i] = m;
        int p = b[i];
        b[j] = b[i];
        b[i] = p;
        break;
      }
    }
  }
  return;
}
void sort(string a[10000],long long int column_name[1000],long long int cal,string a1,long long int num_of_record,long long int b[10000])
{
  string split1[100],split2[100];
  char spaceman = ' ';
  long long int num1,num2,k1,length;
  for (long long int i=0;i<num_of_record;i++) {
    length = a[i].length() - 1;
    k1 = 0;
    num1=0;
    for (int m=0;m<length;m++) {
      if(a[i][m] == spaceman && a[i][m+1] == spaceman) {
        split1[num1] = a[i].substr(k1,m-1);
        k1 = m + 2;
        num1 += 1;
      }
    }
    for (long long int j=i+1;j<num_of_record;j++) {
      length = a[j].length() - 1;
      k1 = 0;
      num2=0;
      for (int m=0;m<length;m++) {
        if(a[j][m] == spaceman && a[j][m+1] == spaceman) {
          split2[num2] = a[j].substr(k1,m-1);
          k1 = m + 2;
          num2 += 1;
        }
      }
      arrange(split1,split2,b,cal,column_name,a,i,j,a1);
    }
  }
  return;
}


int main(int argc, char* argv[]) {
  long long int number_of_lines = 0;
  long long int no_of_lines = 0;
  long long int column_name[1000],b[10000],num_of_rows;
  long long int sum_of_each_tuple = 0;
  string line, p, val[4][3], a[10000];
  long long int memory = stoi(argv[3]);
  long long int cal = argc - 5;
  long long int var = 0;

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
  string a1 = "asc";
  string a2 = "desc";
  myfile.open(argv[1]);
  if (argv[4] == a2 or argv[4] == a1)
  {

      long long int num_of_record = memory/sum_of_each_tuple;
      long long int iteration = number_of_lines/num_of_record;
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
        sort (a,column_name,cal,argv[4],num_of_record,b);
        for (long long int i= 0;i<num_of_record;i++)
        {
          ofstream file; // out file stream
          file.open("output1.txt",ofstream::out | ofstream::app);
          cout << a[i] << '\n';
          file << a[i];
        }
      }
  }
  else
  {
    cout << "type correct order in which you want to sort the file.\n";
    return 0;
  }

//  myfile.close();
///////////////////////////////phase2//////////////////////////////////////
  return 0;
}
