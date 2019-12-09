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
      // Add operation
      stepSize = this->opcodeAdd(&vectorIntcode, opcodePos);
      break;
    }

    case (OPCODE_MUL):
    {
      stepSize = this->opcodeMul(&vectorIntcode, opcodePos);
      break;
    }

    case (OPCODE_IN):
    {
      stepSize = this->opcodeIn(&vectorIntcode, opcodePos);
      break;
    }

    case (OPCODE_OUT):
    {
      stepSize = this->opcodeOut(&vectorIntcode, opcodePos);
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

int CIntcodeComputer::opcodeAdd(std::vector<int> *vectorIntcode, int pos)
{
  int firstPos = vectorIntcode->at(pos + 1);
  int secondPos = vectorIntcode->at(pos + 2);
  int targetPos = vectorIntcode->at(pos + 3);

  // get Values for the opcode
  int firstVal = vectorIntcode->at(firstPos);
  int secondVal = vectorIntcode->at(secondPos);

  // Operation
  vectorIntcode->at(targetPos) = firstVal + secondVal;

  return(4);
}

int CIntcodeComputer::opcodeMul(std::vector<int> *vectorIntcode, int pos)
{
  // Extract position and value for the opcode
  int firstPos = vectorIntcode->at(pos + 1);
  int secondPos = vectorIntcode->at(pos + 2);
  int targetPos = vectorIntcode->at(pos + 3);

  // get Values for the opcode
  int firstVal = vectorIntcode->at(firstPos);
  int secondVal = vectorIntcode->at(secondPos);

  // Operation
  vectorIntcode->at(targetPos) = firstVal * secondVal;

  return(4);
}

int CIntcodeComputer::opcodeIn(std::vector<int> *vectorIntcode, int pos)
{
  int targetPos = vectorIntcode->at(pos + 1);
  int inVal = 0;

  // Get in value
  std::cout << "Input value: " << std::endl;
  std::cin >> inVal;
  // Operation
  vectorIntcode->at(targetPos) = inVal;

  return(2);
}

int CIntcodeComputer::opcodeOut(std::vector<int> *vectorIntcode, int pos)
{
  int outVal = vectorIntcode->at(pos + 1);
  // Operation
  std::cout << "Output value: " << outVal << std::endl;

  return(2);
}
