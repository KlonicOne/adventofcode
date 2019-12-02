// --------------------------
// file : day1.cpp
// --------------------------

#include <iostream>
#include <string>
#include <math.h>
#include <fstream>
using namespace std;

int main()
{
  int sum = 0; // overall sum
  std::ifstream ifile("input.txt");
  std::string iline;

  // For eachline sum up
  while (std::getline(ifile, iline))
  {
    // calculate the fuel and sum
    sum += floor(std::stod(iline) / 3.0) - 2;
  }
  // result out
  std::cout << "Sum = " << sum << '\n';
}
