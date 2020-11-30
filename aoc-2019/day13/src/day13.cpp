/*
 * day13.cpp
 */

#include <iostream>
#include <string>
#include <math.h>
#include <fstream>
#include "CIntcodeComputer.h"
using namespace std;

#define INIT_SIZE (100000)

int main()
{
  std::ifstream ifile("input.txt");
  std::vector<long long> codeVector;

  CIntcodeComputer intcodeComp;

  // Init
  intcodeComp.initScreenMap();
  intcodeComp.initStatisticsVectorScreenMap();

  // Get string to vector
  codeVector = intcodeComp.getVectorCode(ifile);
  // Set orignal size
  long long programSize = codeVector.size();
  intcodeComp.setProgramSizeInputCode(programSize);

  // extend vector as it will happen that we write behind the program
  codeVector.resize(INIT_SIZE);

  // Progress new code vector for screen map
  intcodeComp.progressVectorCode(codeVector);

  // output
  intcodeComp.printScreenMap();
}

