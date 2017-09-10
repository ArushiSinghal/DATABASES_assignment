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
  string line;
  ifstream myfile(argv[1]);
  ifstream metafile;
  metafile.open("metadata.txt");
  int num = 0;
  while (getline(myfile, line))
  {
    ++number_of_lines;
  }
  while (getline(metafile, line))
  {
    ++no_of_lines;
  }
  metafile.close();
  metafile.open("metadata.txt");
  int num_of_rows = no_of_lines;
  int num_of_col = 2;
  string val[100][2];
  for(int countRows = 0; countRows < num_of_rows; countRows++)
    {
        for(int countColumns = 0; countColumns < num_of_col; countColumns++)
        {
            metafile >> val[countRows][countColumns];
            cout << val[countRows][countColumns] << '\n';
        }
    }
  metafile.close();
  int memory = stoi(argv[3]);
  int cal = argc - 5;
  cout << cal << '\n';
  return 0;
}
