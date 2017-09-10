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
using namespace std;
int main(int argc, char* argv[]) {
  int number_of_lines = 0;
  int no_of_lines = 0;
  int column_name[3];
  long long int sum_of_each_tuple = 0;
  string line,p, val[4][3];
  ifstream myfile,metafile;
  ifstream metafile;
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
  if (argv[4] == a1)
  {
      //column_name, sum_of_each_tuple, cal, a1, memory, number_of_lines,iteration,num_of_rocord(block);
      long long int num_of_record = memory/sum_of_each_tuple;
      long long int iteration = number_of_lines/num_of_record;
      if (number_of_lines%num_of_record != 0)
        iteration += 1;
      for (long long int l = 1; l<= iteration; l++)
      {
        /*
         for(int countRows = 0; countRows < num_of_rows; countRows++)
          {
              for(int countColumns = 0; countColumns < num_of_col; countColumns++)
              {
                  metafile >> val[countRows][countColumns];
                  if (countColumns > 0)
                  sum_of_each_tuple += stoi(val[countRows][countColumns]);
              }
          }
        */
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
  return 0;
}
