/*
 * day2.cpp
 */

#include <iostream>
#include <string>
#include <math.h>
#include <fstream>
#include "CIntcodeComputer.h"
using namespace std;

#define INIT_SIZE (10000000)

int main()
{
  long long programSize;
  std::ifstream ifile("input.txt");
  std::vector<long long> codeVector;
  CIntcodeComputer intcodeComp;

  // Get string to vector
  codeVector = intcodeComp.getVectorCode(ifile);
  programSize = codeVector.size();

  // extend vector as it will happen that we write behind the program
  codeVector.resize(INIT_SIZE);

//  intcodeComp.debugOutVector(codeVector);

  // Progress new code vector
  codeVector = intcodeComp.progressVectorCode(codeVector, programSize);
}

