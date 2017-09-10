#include <iostream>
#include <fstream>
#include <string>
#include <iterator>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include <stdexcept>
using namespace std;
int main(int argc, char* argv[]) {
  int number_of_lines = 0;
  string line;
  ifstream myfile(argv[1]);
  while (getline(myfile, line))
  {
    ++number_of_lines;
  }
  int memory = stoi(argv[3]);
  int cal = argc - 5;
  cout << cal << '\n'; 
  return 0;
}
