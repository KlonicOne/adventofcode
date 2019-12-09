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

#define OPCODE_RANGE (100)

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
  int relativePos = 0;
  int opcode = 0;
  unsigned mode = 0;

  // Walk through given intcode in stepsize based on command until end reached
  for (std::vector<int>::const_iterator opcodeIt = vectorIntcode.begin(); *opcodeIt != OPCODE_END;
      opcodeIt += relativePos, opcodePos += relativePos)
  {
    opcode = (*opcodeIt) % OPCODE_RANGE;
    mode = (unsigned) (*opcodeIt / OPCODE_RANGE);

    switch (opcode)
    {
    case (OPCODE_ADD):
    {
      // Add operation
      relativePos = this->opcodeAdd(&vectorIntcode, opcodePos, mode);
      break;
    }

    case (OPCODE_MUL):
    {
      relativePos = this->opcodeMul(&vectorIntcode, opcodePos, mode);
      break;
    }

    case (OPCODE_IN):
    {
      relativePos = this->opcodeIn(&vectorIntcode, opcodePos, mode);
      break;
    }

    case (OPCODE_OUT):
    {
      relativePos = this->opcodeOut(&vectorIntcode, opcodePos, mode);
      break;
    }

    case (OPCODE_JIT):
    {
      relativePos = this->opcodeJiT(&vectorIntcode, opcodePos, mode);
      break;
    }

    case (OPCODE_JIF):
    {
      relativePos = this->opcodeJiF(&vectorIntcode, opcodePos, mode);
      break;
    }

    case (OPCODE_LESSTHAN):
    {
      relativePos = this->opcodeLessThan(&vectorIntcode, opcodePos, mode);
      break;
    }

    case (OPCODE_EQUALS):
    {
      relativePos = this->opcodeEquals(&vectorIntcode, opcodePos, mode);
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

int CIntcodeComputer::opcodeAdd(std::vector<int> *vectorIntcode, int pos, unsigned mode)
{
  int modePar1 = (int) ((mode / 1) & 1);
  int modePar2 = (int) ((mode / 10) & 1);
//  int modePar3 = (int)((mode / 100) & 1);

// Get values or addresses
  int firstPos = vectorIntcode->at(pos + 1);
  int secondPos = vectorIntcode->at(pos + 2);
  int targetPos = vectorIntcode->at(pos + 3);

  int firstVal = 0;
  int secondVal = 0;

// get Values for the opcode
  if (modePar1 == MODE_IMMEDIATE)
  {
    firstVal = firstPos;
  }
  else
  {
    firstVal = vectorIntcode->at(firstPos);
  }

  if (modePar2 == MODE_IMMEDIATE)
  {
    secondVal = secondPos;
  }
  else
  {
    secondVal = vectorIntcode->at(secondPos);
  }

// Operation
  vectorIntcode->at(targetPos) = firstVal + secondVal;

  return (4);
}

int CIntcodeComputer::opcodeMul(std::vector<int> *vectorIntcode, int pos, unsigned mode)
{
  int modePar1 = (int) ((mode / 1) & 1);
  int modePar2 = (int) ((mode / 10) & 1);
//  int modePar3 = (int)((mode / 100) & 1);

// Get values or addresses
  int firstPos = vectorIntcode->at(pos + 1);
  int secondPos = vectorIntcode->at(pos + 2);
  int targetPos = vectorIntcode->at(pos + 3);

  int firstVal = 0;
  int secondVal = 0;

  // get Values for the opcode
  if (modePar1 == MODE_IMMEDIATE)
  {
    firstVal = firstPos;
  }
  else
  {
    firstVal = vectorIntcode->at(firstPos);
  }

  if (modePar2 == MODE_IMMEDIATE)
  {
    secondVal = secondPos;
  }
  else
  {
    secondVal = vectorIntcode->at(secondPos);
  }

// Operation
  vectorIntcode->at(targetPos) = firstVal * secondVal;

  return (4);
}

int CIntcodeComputer::opcodeIn(std::vector<int> *vectorIntcode, int pos, unsigned mode)
{
  int targetPos = vectorIntcode->at(pos + 1);
  int inVal = 0;

// Get in value
  std::cout << "Input value: " << std::endl;
  std::cin >> inVal;
// Operation
  vectorIntcode->at(targetPos) = inVal;

  return (2);
}

int CIntcodeComputer::opcodeOut(std::vector<int> *vectorIntcode, int pos, unsigned mode)
{
  int modePar1 = (int) ((mode / 1) & 1);
  int outPos = vectorIntcode->at(pos + 1);
  int outVal = 0;

  if (modePar1 == MODE_IMMEDIATE)
  {
    outVal = outPos;
  }
  else
  {
    outVal = vectorIntcode->at(outPos);
  }

  vectorIntcode->at(outPos);
// Operation
  std::cout << "Output value: " << outVal << std::endl;

  return (2);
}

int CIntcodeComputer::opcodeJiT(std::vector<int> *vectorIntcode, int pos, unsigned mode)
{
  int retPos = 3;
  int modePar1 = (int) ((mode / 1) & 1);
  int modePar2 = (int) ((mode / 10) & 1);

  // Get values or addresses
  int firstPos = vectorIntcode->at(pos + 1);
  int secondPos = vectorIntcode->at(pos + 2);

  int firstVal = 0;
  int secondVal = 0;

  // get Values for the opcode
  if (modePar1 == MODE_IMMEDIATE)
  {
    firstVal = firstPos;
  }
  else
  {
    firstVal = vectorIntcode->at(firstPos);
  }

  if (modePar2 == MODE_IMMEDIATE)
  {
    secondVal = secondPos;
  }
  else
  {
    secondVal = vectorIntcode->at(secondPos);
  }

  if (firstVal != 0)
  {
    retPos = secondVal - pos; // I used relative jumps
  }

  return (retPos);
}

int CIntcodeComputer::opcodeJiF(std::vector<int> *vectorIntcode, int pos, unsigned mode)
{
  int retPos = 3;
  int modePar1 = (int) ((mode / 1) & 1);
  int modePar2 = (int) ((mode / 10) & 1);

  // Get values or addresses
  int firstPos = vectorIntcode->at(pos + 1);
  int secondPos = vectorIntcode->at(pos + 2);

  int firstVal = 0;
  int secondVal = 0;

  // get Values for the opcode
  if (modePar1 == MODE_IMMEDIATE)
  {
    firstVal = firstPos;
  }
  else
  {
    firstVal = vectorIntcode->at(firstPos);
  }

  if (modePar2 == MODE_IMMEDIATE)
  {
    secondVal = secondPos;
  }
  else
  {
    secondVal = vectorIntcode->at(secondPos);
  }

  if (firstVal == 0)
  {
    retPos = secondVal - pos; // I used relative jumps
  }

  return (retPos);
}

int CIntcodeComputer::opcodeLessThan(std::vector<int> *vectorIntcode, int pos, unsigned mode)
{
  int modePar1 = (int) ((mode / 1) & 1);
  int modePar2 = (int) ((mode / 10) & 1);

  int firstPos = vectorIntcode->at(pos + 1);
  int secondPos = vectorIntcode->at(pos + 2);
  int targetPos = vectorIntcode->at(pos + 3);

  int firstVal = 0;
  int secondVal = 0;

  // get Values for the opcode
  if (modePar1 == MODE_IMMEDIATE)
  {
    firstVal = firstPos;
  }
  else
  {
    firstVal = vectorIntcode->at(firstPos);
  }

  if (modePar2 == MODE_IMMEDIATE)
  {
    secondVal = secondPos;
  }
  else
  {
    secondVal = vectorIntcode->at(secondPos);
  }

  // Operation
  if (firstVal < secondVal)
  {
    vectorIntcode->at(targetPos) = 1;
  }
  else
  {
    vectorIntcode->at(targetPos) = 0;
  }

  return (4);
}

int CIntcodeComputer::opcodeEquals(std::vector<int> *vectorIntcode, int pos, unsigned mode)
{
  int modePar1 = (int) ((mode / 1) & 1);
  int modePar2 = (int) ((mode / 10) & 1);

  int firstPos = vectorIntcode->at(pos + 1);
  int secondPos = vectorIntcode->at(pos + 2);
  int targetPos = vectorIntcode->at(pos + 3);

  int firstVal = 0;
  int secondVal = 0;

  // get Values for the opcode
  if (modePar1 == MODE_IMMEDIATE)
  {
    firstVal = firstPos;
  }
  else
  {
    firstVal = vectorIntcode->at(firstPos);
  }

  if (modePar2 == MODE_IMMEDIATE)
  {
    secondVal = secondPos;
  }
  else
  {
    secondVal = vectorIntcode->at(secondPos);
  }

  // Operation
  if (firstVal == secondVal)
  {
    vectorIntcode->at(targetPos) = 1;
  }
  else
  {
    vectorIntcode->at(targetPos) = 0;
  }

  return (4);
}

int CIntcodeComputer::opcodeRelBaseAdjust(std::vector<int> *vectorIntcode, int pos, unsigned mode)
{
  int retPos = 0;
  int modePar1 = (int) ((mode / 1) & 1);

  // Get values or addresses
  int firstPos = vectorIntcode->at(pos + 1);

  // get Values for the opcode
  if (modePar1 == MODE_IMMEDIATE)
  {
    retPos = firstPos;
  }
  else
  {
    retPos = vectorIntcode->at(firstPos);
  }

  return (retPos);
}
