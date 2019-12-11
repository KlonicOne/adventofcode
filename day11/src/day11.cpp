/*
 * day11.cpp
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
  std::ifstream ifile("input.txt");
  std::vector<long long> codeVector;

  CIntcodeComputer intcodeComp;

  // Get string to vector
  codeVector = intcodeComp.getVectorCode(ifile);
  long long programSize = codeVector.size();

  // extend vector as it will happen that we write behind the program
  codeVector.resize(INIT_SIZE);

  // Set input
  intcodeComp.setInput(1);

  // Progress new code vector
  codeVector = intcodeComp.progressVectorCode(codeVector, programSize);

  // output
  std::cout << "Output: " << intcodeComp.getOuput() << std::endl;
}

