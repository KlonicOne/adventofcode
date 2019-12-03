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
  std::vector<int> codeVector;
  CIntcodeComputer intcodeComp;

  codeVector = intcodeComp.getVectorCode(ifile);
  codeVector = intcodeComp.progressVectorCode(codeVector);

}

