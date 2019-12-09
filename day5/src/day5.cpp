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
  CDecodePW intcodeComp;

  // Get string to vector
  codeVector = intcodeComp.getVectorCode(ifile);
  // exchange positions
  preparedCodeVector = codeVector;
  preparedCodeVector.at(1) = 12;
  preparedCodeVector.at(2) = 2;
  // Progress new code vector
  preparedCodeVector = intcodeComp.progressVectorCode(preparedCodeVector);

  // First result
  std::cout << "Result1: " << preparedCodeVector.at(0) << std::endl;

  // Second result
  int resultTwo = intcodeComp.nounVerbResultProducedInput(codeVector, 19690720);
  std::cout << "Result2: " << resultTwo << std::endl;
}

