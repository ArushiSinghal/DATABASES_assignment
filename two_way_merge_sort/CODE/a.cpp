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
//#include <boost/algorithm/string.hpp>
using namespace std;
int arrange(split1,num1,split2,num2,&b[i],&b[j],cal,column_name,string a , int i, int j)
{
  for (int i=0;i<cal;i++)
  {
    if (split1[column_name[i]].compare(split2[column_name[i]]) > 0)
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
  if (i >= cal && b[i] > b[j])
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

int sort(string a[10000],int column_name[3],int cal,string a1,long long int num_of_record,int b[10000])
{
  string split1[100],split2[100];
  char spaceman = ' ';
  int num1,num2,k1,length;
  for (int i=0;i<num_of_record;i++) {
    length = a[i].length() - 1;
    k1 = 0;
    num1=0;
    for (int m=0;m<length;m++) {
      if(a[i][m] == spaceman && a[i][m+1] == spaceman) {
        string split1[num1] = a[i].substr(k1,m-1);
        k1 = m + 2;
        num1 += 1;
      }
    }
    for (int j=i+1;j<num_of_record;j++) {
      length = a[j].length() - 1;
      k1 = 0;
      num2=0;
      for (int m=0;m<length;m++) {
        if(a[j][m] == spaceman && a[j][m+1] == spaceman) {
          string split2[num1] = a[j].substr(k1,m-1);
          k1 = m + 2;
          num2 += 1;
        }
      }
      arrange(split1,num1,split2,num2,b,cal,column_name,a,i,j);
    }
  }
}

int main(int argc, char* argv[]) {
  int number_of_lines = 0;
  int no_of_lines = 0;
  int column_name[3];
  long long int sum_of_each_tuple = 0;
  string line,p, val[4][3];
  string a[10000];
  int b[10000];
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
  int num_of_rows = no_of_lines;
  for(int countRows = 0; countRows < num_of_rows; countRows++)
    {
        for(int countColumns = 0; countColumns < 2; countColumns++)
        {
            metafile >> val[countRows][countColumns];
            if (countColumns > 0)
            sum_of_each_tuple += stoi(val[countRows][countColumns]);
        }
    }
  metafile.close();
  int memory = stoi(argv[3]);
  int cal = argc - 5;
  for (int i = 0;i<cal;i++)
  {
    p = argv[i+5];
    for (int k=0;k<num_of_rows;k++)
    {
      if (p == val[k][0])
      {
      column_name[i] = k;
      break;
      }
    }
  }
  string a1 = "asc";
  string a2 = "desc";
  myfile.open(argv[1]);
  if (argv[4] == a2)
  {
      //column_name, sum_of_each_tuple, cal, a1, memory, number_of_lines,iteration,num_of_rocord(block);
      long long int num_of_record = memory/sum_of_each_tuple;
      long long int iteration = number_of_lines/num_of_record;
      if (number_of_lines%num_of_record != 0)
        iteration += 1;
      for (long long int l = 1; l<= iteration; l++)
      {
        for(long long int k = 0;k<num_of_record;k++)
        {
            getline(myfile, a[k], '\n');
            b[k] = k;
            cout << a[k] << "\n";
        }
        sort (a,column_name,cal,a1,num_of_record,b);
      }
  }
  else if (argv[4] == a2)
  {
    column_name, sum_of_each_tuple, cal, a2, memory, number_of_lines;
  }
  else
  {
    cout << "type correct order in which want to sort the file.\n";
    return 0;
  }
  myfile.close();
  return 0;
}
