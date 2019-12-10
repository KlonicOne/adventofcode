/*
 * day2.cpp
 */

#include <iostream>
#include <string>
#include <math.h>
#include <fstream>
#include "CIntcodeComputer.h"
using namespace std;

#define INIT_SIZE (10000)

int main()
{
  long long programSize;
  std::ifstream ifile("input.txt");
  std::vector<long long> codeVector;
  CIntcodeComputer intcodeComp;

  // Get string to vector
  codeVector = intcodeComp.getVectorCode(ifile);
  programSize = codeVector.size();

  // extend vector
  codeVector.resize(INIT_SIZE);
//  std::cout << codeVector.size() << std::endl;
//  std::cout << programSize << std::endl;

//  intcodeComp.debugOutVector(codeVector);

  // Progress new code vector
  codeVector = intcodeComp.progressVectorCode(codeVector, programSize);
}

