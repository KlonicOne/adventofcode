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

std::vector<int> CIntcodeComputer::getVectorCode(istream &input)
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
  int opcodePos = 0;
  int stepSize = 0;

  // Walk through given intcode in stepsize based on command until end reached
  for (std::vector<int>::const_iterator Opcode = vectorIntcode.begin(); *Opcode != OPCODE_END; Opcode += stepSize, opcodePos += stepSize)
  {
    switch (*Opcode)
    {
    case (OPCODE_ADD):
    {
      // Extract position and value for the opcode
      int firstPos = vectorIntcode.at(opcodePos + 1);
      int secondPos = vectorIntcode.at(opcodePos + 2);
      int targetPos = vectorIntcode.at(opcodePos + 3);
      // get Values for the opcode
      int firstVal = vectorIntcode.at(firstPos);
      int secondVal = vectorIntcode.at(secondPos);
      // Operation
      vectorIntcode.at(targetPos) = firstVal + secondVal;
      stepSize = 4; // Step size for this operation
      break;
    }

    case (OPCODE_MUL):
    {
      // Extract position and value for the opcode
      int firstPos = vectorIntcode.at(opcodePos + 1);
      int secondPos = vectorIntcode.at(opcodePos + 2);
      int targetPos = vectorIntcode.at(opcodePos + 3);
      // get Values for the opcode
      int firstVal = vectorIntcode.at(firstPos);
      int secondVal = vectorIntcode.at(secondPos);
      // Operation
      vectorIntcode.at(targetPos) = firstVal * secondVal;
      stepSize = 4; // Step size for this operation
      break;
    }

    case (OPCODE_IN):
    {
      int targetPos = vectorIntcode.at(opcodePos + 1);
      int inVal = 0;
      std::cout << "Input value: " << std::endl;
      std::cin >> inVal;
      // Operation
      vectorIntcode.at(targetPos) = inVal;
      stepSize = 2; // Step size for this operation
      break;
    }

    case (OPCODE_OUT):
    {
      int outVal = vectorIntcode.at(opcodePos + 1);
      // Operation
      std::cout << "Output value: " << outVal << std::endl;
      stepSize = 2; // Step size for this operation
      break;
    }

    default:
      break;
    }
  }

//    this->debugOutVector(vectorIntcode);
  return (vectorIntcode);
}

int CIntcodeComputer::nounVerbResultProducedInput(std::vector<int> vectorIntcode, int targetVal)
{
  int x, y;
  bool exitLoop = false;
  std::vector<int> vectorResult;

  for (x = 0; x < OPCODE_END; x++)
  {
    for (y = 0; y < OPCODE_END; y++)
    {
      // Exchange two values
      vectorIntcode.at(1) = x;
      vectorIntcode.at(2) = y;

      // Calculate result for given noun and verb
      vectorResult = progressVectorCode(vectorIntcode);

      // Check if result equals target value
      if (vectorResult.at(0) == targetVal)
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

  return (100 * x + y);
}

void CIntcodeComputer::debugOutVector(vector<int> inVector)
{
  for (std::vector<int>::const_iterator i = inVector.begin(); i != inVector.end(); ++i)
  {
    std::cout << *i << ',' << ' ';
  }
  std::cout << std::endl;
}
