/*
 * CIntcodeComputer.cpp
 *
 *  Created on: 3 Dec 2019
 *      Author: nico
 */
#include <iostream>
#include <string>
#include <math.h>
#include <fstream>
#include <vector>
using namespace std;

#include "CIntcodeComputer.h"

CIntcodeComputer::CIntcodeComputer()
{
  // TODO Auto-generated constructor stub

}

CIntcodeComputer::~CIntcodeComputer()
{
  // TODO Auto-generated destructor stub
}

std::vector<int> CIntcodeComputer::getVectorCode(istream& input)
{
  string codeElement;
  std::vector<int> codeVector;

  while (getline(input, codeElement, ','))
  {
    codeVector.push_back(stoi(codeElement));
  }

//  this->debugOutVector(codeVector);

  return (codeVector);
}

std::vector<int> CIntcodeComputer::progressVectorCode(std::vector<int> vectorIntcode)
{
  int firstPos, secondPos, targetPos;
  int firstVal, secondVal;
  int opcodePos = 0;

  // Walk through given intcode in stepsize 4 until end reached
  for (std::vector<int>::const_iterator Opcode = vectorIntcode.begin(); *Opcode != OPCODE_END; Opcode += 4)
  {
    // Extract position and value
    firstPos = vectorIntcode.at(opcodePos + 1);
    secondPos = vectorIntcode.at(opcodePos + 2);
    targetPos = vectorIntcode.at(opcodePos + 3);

    firstVal = vectorIntcode.at(firstPos);
    secondVal = vectorIntcode.at(secondPos);

    switch (*Opcode)
    {
    case (OPCODE_ADD):
      vectorIntcode.at(targetPos) = firstVal + secondVal;
      break;
    case (OPCODE_MUL):
      vectorIntcode.at(targetPos) = firstVal * secondVal;
      break;
    default:
      break;
    }
    opcodePos += 4;
  }

//    this->debugOutVector(vectorIntcode);
  return (vectorIntcode);
}

int CIntcodeComputer::nounVerbResultProducedInput(std::vector<int> vectorIntcode, int targetVal)
{
  int x, y;
  bool exitLoop = false;
  std::vector<int> vectorResult;

  for(x = 0; x < OPCODE_END; x++)
  {
    for(y = 0; y < OPCODE_END; y++)
    {
      // Exchange two values
      vectorIntcode.at(1) = x;
      vectorIntcode.at(2) = y;

      // Calculate result for given noun and verb
      vectorResult = progressVectorCode(vectorIntcode);

      // Check if result equals target value
      if(vectorResult.at(0) == targetVal)
      {
        exitLoop = true;
        break; // end inner loop
      }
    }

    if (exitLoop)
    {
      break; // end outer loop
    }
  }

  return(100 * x + y);
}

void CIntcodeComputer::debugOutVector(vector<int> inVector)
{
  for (std::vector<int>::const_iterator i = inVector.begin(); i != inVector.end(); ++i)
  {
    std::cout << *i << ',' << ' ';
  }
  std::cout << std::endl;
}
