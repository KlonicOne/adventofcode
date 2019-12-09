/*
 * day2.cpp
 */

#include <iostream>
#include <string>
#include <math.h>
#include <fstream>
#include "CIntcodeComputer.h"
using namespace std;

int main()
{
  std::ifstream ifile("input.txt");
  std::vector<int> codeVector, preparedCodeVector;
  CIntcodeComputer intcodeComp;

  // Get string to vector
  codeVector = intcodeComp.getVectorCode(ifile);
  // exchange positions
  preparedCodeVector = codeVector;
  // Progress new code vector
  preparedCodeVector = intcodeComp.progressVectorCode(preparedCodeVector);
}

