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

std::vector<long> CIntcodeComputer::getVectorCode(istream &input)
{
  string codeElement;
  std::vector<long> codeVector;

  while (getline(input, codeElement, ','))
  {
    codeVector.push_back(stol(codeElement));
  }

//  this->debugOutVector(codeVector);

  return (codeVector);
}

std::vector<long> CIntcodeComputer::progressVectorCode(std::vector<long> vectorIntcode)
{
  int opcodePos = 0;
  int relativePos = 0;
  long opcode = 0;
  int relativeBase = 0;
  unsigned mode = 0;

  // Walk through given intcode in stepsize based on command until end reached
  for (std::vector<long>::const_iterator opcodeIt = vectorIntcode.begin(); *opcodeIt != OPCODE_END;
      opcodeIt += relativePos, opcodePos += relativePos)
  {
    opcode = (*opcodeIt) % OPCODE_RANGE;
    mode = (unsigned) (*opcodeIt / OPCODE_RANGE);

    switch (opcode)
    {
    case (OPCODE_ADD):
    {
      // Add operation
      relativePos = this->opcodeAdd(&vectorIntcode, opcodePos, relativeBase, mode);
      break;
    }

    case (OPCODE_MUL):
    {
      relativePos = this->opcodeMul(&vectorIntcode, opcodePos, relativeBase, mode);
      break;
    }

    case (OPCODE_IN):
    {
      relativePos = this->opcodeIn(&vectorIntcode, opcodePos, relativeBase, mode);
      break;
    }

    case (OPCODE_OUT):
    {
      relativePos = this->opcodeOut(&vectorIntcode, opcodePos, relativeBase, mode);
      break;
    }

    case (OPCODE_JIT):
    {
      relativePos = this->opcodeJiT(&vectorIntcode, opcodePos, relativeBase, mode);
      break;
    }

    case (OPCODE_JIF):
    {
      relativePos = this->opcodeJiF(&vectorIntcode, opcodePos, relativeBase, mode);
      break;
    }

    case (OPCODE_LESSTHAN):
    {
      relativePos = this->opcodeLessThan(&vectorIntcode, opcodePos, relativeBase, mode);
      break;
    }

    case (OPCODE_EQUALS):
    {
      relativePos = this->opcodeEquals(&vectorIntcode, opcodePos, relativeBase, mode);
      break;
    }

    case (OPCODE_RELBASEADJUST):
    {
      relativePos = this->opcodeRelBaseAdjust(&vectorIntcode, opcodePos, &relativeBase, mode);
      break;
    }

    default:
      break;
    }
  }

//    this->debugOutVector(vectorIntcode);
  return (vectorIntcode);
}

int CIntcodeComputer::nounVerbResultProducedInput(std::vector<long> vectorIntcode, int targetVal)
{
  int x, y;
  bool exitLoop = false;
  std::vector<long> vectorResult;

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

void CIntcodeComputer::debugOutVector(vector<long> inVector)
{
  for (std::vector<long>::const_iterator i = inVector.begin(); i != inVector.end(); ++i)
  {
    std::cout << *i << ',' << ' ';
  }
  std::cout << std::endl;
}

int CIntcodeComputer::opcodeAdd(std::vector<long> *vectorIntcode, int pos, int relBase, unsigned mode)
{
  int modePar1 = (int) (mode % 10);
  int modePar2 = (int) ((mode / 10) % 10);

  // Get values or addresses
  long firstPos = vectorIntcode->at(pos + 1);
  long secondPos = vectorIntcode->at(pos + 2);
  long targetPos = vectorIntcode->at(pos + 3);

  long firstVal = 0;
  long secondVal = 0;

  // get Values for the opcode
  if (modePar1 == MODE_IMMEDIATE)
  {
    firstVal = firstPos;
  }
  else if (modePar1 == MODE_RELATIVE)
  {
    firstVal = vectorIntcode->at(firstPos + relBase);
  }
  else
  {
    firstVal = vectorIntcode->at(firstPos);
  }

  if (modePar2 == MODE_IMMEDIATE)
  {
    secondVal = secondPos;
  }
  else if (modePar1 == MODE_RELATIVE)
  {
    secondVal = vectorIntcode->at(secondPos + relBase);
  }
  else
  {
    secondVal = vectorIntcode->at(secondPos);
  }

  // Operation
  vectorIntcode->at(targetPos) = firstVal + secondVal;

  return (4);
}

int CIntcodeComputer::opcodeMul(std::vector<long> *vectorIntcode, int pos, int relBase, unsigned mode)
{
  int modePar1 = (int) (mode % 10);
  int modePar2 = (int) ((mode / 10) % 10);

  // Get values or addresses
  long firstPos = vectorIntcode->at(pos + 1);
  long secondPos = vectorIntcode->at(pos + 2);
  long targetPos = vectorIntcode->at(pos + 3);

  long firstVal = 0;
  long secondVal = 0;

  // get Values for the opcode
  if (modePar1 == MODE_IMMEDIATE)
  {
    firstVal = firstPos;
  }
  else if (modePar1 == MODE_RELATIVE)
  {
    firstVal = vectorIntcode->at(firstPos + relBase);
  }
  else
  {
    firstVal = vectorIntcode->at(firstPos);
  }

  if (modePar2 == MODE_IMMEDIATE)
  {
    secondVal = secondPos;
  }
  else if (modePar1 == MODE_RELATIVE)
  {
    secondVal = vectorIntcode->at(secondPos + relBase);
  }
  else
  {
    secondVal = vectorIntcode->at(secondPos);
  }

//  long vecSize = (long) vectorIntcode->size();
//
//  // Operation
//  std::cout << "target: " << targetPos << std::endl;
//  std::cout << "size: " << vecSize << std::endl;
//
//  if(targetPos > vecSize)
//  {
//    int extRange = targetPos - vecSize + 1;
//    std::cout << "extRange: " << extRange << std::endl;
//
//    vectorIntcode->insert(vectorIntcode->end(), extRange, result);
//  }
//
//  std::cout << "size: " << vectorIntcode->size() << std::endl;
  long result = firstVal * secondVal;
  vectorIntcode->at(targetPos) = result;

  return (4);
}

int CIntcodeComputer::opcodeIn(std::vector<long> *vectorIntcode, int pos, int relBase, unsigned mode)
{
  long targetPos = vectorIntcode->at(pos + 1);
  long inVal = 0;

  // Get in value
  std::cout << "Input value: " << std::endl;
  std::cin >> inVal;

  // Operation
  vectorIntcode->at(targetPos) = inVal;

  return (2);
}

int CIntcodeComputer::opcodeOut(std::vector<long> *vectorIntcode, int pos, int relBase, unsigned mode)
{
  int modePar1 = (int) (mode % 10);
  long outPos = vectorIntcode->at(pos + 1);
  long outVal = 0;

  if (modePar1 == MODE_IMMEDIATE)
  {
    outVal = outPos;
  }
  else if (modePar1 == MODE_RELATIVE)
  {
    outVal = vectorIntcode->at(relBase + outPos);
  }
  else
  {
    outVal = vectorIntcode->at(outPos);
  }

  // Operation
  std::cout << outVal << ", " << std::endl;

  return (2);
}

int CIntcodeComputer::opcodeJiT(std::vector<long> *vectorIntcode, int pos, int relBase, unsigned mode)
{
  int modePar1 = (int) (mode % 10);
  int modePar2 = (int) ((mode / 10) % 10);
  int retPos = 3;

  // Get values or addresses
  long firstPos = vectorIntcode->at(pos + 1);
  long secondPos = vectorIntcode->at(pos + 2);

  long firstVal = 0;
  long secondVal = 0;

  // get Values for the opcode
  if (modePar1 == MODE_IMMEDIATE)
  {
    firstVal = firstPos;
  }
  else if (modePar1 == MODE_RELATIVE)
  {
    firstVal = vectorIntcode->at(firstPos + relBase);
  }
  else
  {
    firstVal = vectorIntcode->at(firstPos);
  }

  if (modePar2 == MODE_IMMEDIATE)
  {
    secondVal = secondPos;
  }
  else if (modePar1 == MODE_RELATIVE)
  {
    secondVal = vectorIntcode->at(secondPos + relBase);
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

int CIntcodeComputer::opcodeJiF(std::vector<long> *vectorIntcode, int pos, int relBase, unsigned mode)
{
  int modePar1 = (int) (mode % 10);
  int modePar2 = (int) ((mode / 10) % 10);
  int retPos = 3;

  // Get values or addresses
  long firstPos = vectorIntcode->at(pos + 1);
  long secondPos = vectorIntcode->at(pos + 2);

  long firstVal = 0;
  long secondVal = 0;

  // get Values for the opcode
  if (modePar1 == MODE_IMMEDIATE)
  {
    firstVal = firstPos;
  }
  else if (modePar1 == MODE_RELATIVE)
  {
    firstVal = vectorIntcode->at(firstPos + relBase);
  }
  else
  {
    firstVal = vectorIntcode->at(firstPos);
  }

  if (modePar2 == MODE_IMMEDIATE)
  {
    secondVal = secondPos;
  }
  else if (modePar1 == MODE_RELATIVE)
  {
    secondVal = vectorIntcode->at(secondPos + relBase);
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

int CIntcodeComputer::opcodeLessThan(std::vector<long> *vectorIntcode, int pos, int relBase, unsigned mode)
{
  int modePar1 = (int) (mode % 10);
  int modePar2 = (int) ((mode / 10) % 10);

  long firstPos = vectorIntcode->at(pos + 1);
  long secondPos = vectorIntcode->at(pos + 2);
  long targetPos = vectorIntcode->at(pos + 3);

  long firstVal = 0;
  long secondVal = 0;

  // get Values for the opcode
  if (modePar1 == MODE_IMMEDIATE)
  {
    firstVal = firstPos;
  }
  else if (modePar1 == MODE_RELATIVE)
  {
    firstVal = vectorIntcode->at(firstPos + relBase);
  }
  else
  {
    firstVal = vectorIntcode->at(firstPos);
  }

  if (modePar2 == MODE_IMMEDIATE)
  {
    secondVal = secondPos;
  }
  else if (modePar1 == MODE_RELATIVE)
  {
    secondVal = vectorIntcode->at(secondPos + relBase);
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

int CIntcodeComputer::opcodeEquals(std::vector<long> *vectorIntcode, int pos, int relBase, unsigned mode)
{
  int modePar1 = (int) (mode % 10);
  int modePar2 = (int) ((mode / 10) % 10);

  long firstPos = vectorIntcode->at(pos + 1);
  long secondPos = vectorIntcode->at(pos + 2);
  long targetPos = vectorIntcode->at(pos + 3);

  long firstVal = 0;
  long secondVal = 0;

  // get Values for the opcode
  if (modePar1 == MODE_IMMEDIATE)
  {
    firstVal = firstPos;
  }
  else if (modePar1 == MODE_RELATIVE)
  {
    firstVal = vectorIntcode->at(firstPos + relBase);
  }
  else
  {
    firstVal = vectorIntcode->at(firstPos);
  }

  if (modePar2 == MODE_IMMEDIATE)
  {
    secondVal = secondPos;
  }
  else if (modePar1 == MODE_RELATIVE)
  {
    secondVal = vectorIntcode->at(secondPos + relBase);
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

int CIntcodeComputer::opcodeRelBaseAdjust(std::vector<long> *vectorIntcode, int pos, int *relBase, unsigned mode)
{
  int retPos = 2;
  int modePar1 = (int) (mode % 10);

  // Get values or addresses
  long firstPos = vectorIntcode->at(pos + 1);

  // get Values for the opcode
  if (modePar1 == MODE_IMMEDIATE)
  {
    *relBase += firstPos;
  }
  else if (modePar1 == MODE_RELATIVE)
  {
    *relBase = vectorIntcode->at(firstPos + *relBase);
  }
  else
  {
    *relBase += vectorIntcode->at(firstPos);
  }

  return (retPos);
}
