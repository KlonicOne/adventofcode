// --------------------------
// file : day1.cpp
// --------------------------

#include <iostream>
#include <string>
#include <math.h>
#include <fstream>
#include "fuelcalculator.h"
using namespace std;


int main()
{
  int sum = 0; // overall sum
  std::ifstream ifile("input.txt");
  std::string iline;

  CFuelCalculator cFuelCalc;

  // For eachline sum up
  while (std::getline(ifile, iline))
  {
    // calculate the fuel and sum
    sum += cFuelCalc.getFuelOfModule(stoi(iline));
  }
  // result out
  std::cout << "Sum = " << sum << '\n';
}
