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

// Defines how long the opcode can be, here from 0 to 99
#define OPCODE_RANGE (100)

CIntcodeComputer::CIntcodeComputer()
{
  // TODO Auto-generated constructor stub

}

CIntcodeComputer::~CIntcodeComputer()
{
  // TODO Auto-generated destructor stub
}

std::vector<long long> CIntcodeComputer::getVectorCode(istream &input)
{
  string codeElement;
  std::vector<long long> codeVector;

  // Iterate through given istream and extract code as vector if ints
  while (getline(input, codeElement, ','))
  {
    codeVector.push_back(stoll(codeElement));
  }

//  this->debugOutVector(codeVector);

  return (codeVector);
}

std::vector<long long> CIntcodeComputer::progressVectorCode(std::vector<long long> vectorIntcode, long long programSize)
{
  long long opcodePos = 0;
  long long relativePos = 0;
  long long opcode = 0;
  long long relativeBase = 0;
  long long mode = 0;

  // Walk through given intcode in stepsize based on command until end reached
  for (std::vector<long long>::const_iterator opcodeIt = vectorIntcode.begin(); *opcodeIt != OPCODE_END; opcodeIt +=
      relativePos, opcodePos += relativePos)
  {
    // Extract opcode and modes
    opcode = (*opcodeIt) % OPCODE_RANGE;
    mode = (long long) (*opcodeIt / OPCODE_RANGE);

    // Decide function for opcode
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

long long CIntcodeComputer::nounVerbResultProducedInput(std::vector<long long> vectorIntcode, long long targetVal)
{
  long long x, y;
  bool exitLoop = false;
  std::vector<long long> vectorResult;

  for (x = 0; x < OPCODE_END; x++)
  {
    for (y = 0; y < OPCODE_END; y++)
    {
      // Exchange two values
      vectorIntcode.at(1) = x;
      vectorIntcode.at(2) = y;

      // Calculate result for given noun and verb
      vectorResult = progressVectorCode(vectorIntcode, vectorIntcode.size());

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

void CIntcodeComputer::debugOutVector(vector<long long> inVector)
{
  for (std::vector<long long>::const_iterator i = inVector.begin(); i != inVector.end(); ++i)
  {
    std::cout << *i << ',' << ' ';
  }
  std::cout << std::endl;
}

long long CIntcodeComputer::getParameterValue(long long mode, long long pos, long long relBase, std::vector<long long>* vectorIntcode)
{
  long long value;

  // get Values for the opcode
  if (mode == MODE_IMMEDIATE)
  {
    value = pos;
  }
  else if (mode == MODE_RELATIVE)
  {
    value = vectorIntcode->at(pos + relBase);
  }
  else
  {
    value = vectorIntcode->at(pos);
  }

  return value;
}

long long CIntcodeComputer::opcodeAdd(std::vector<long long> *vectorIntcode, long long pos, long long relBase, long long mode)
{
  long long modePar1 = (long long) (mode % 10);
  long long modePar2 = (long long) ((mode / 10) % 10);
  long long modePar3 = (long long) ((mode / 100) % 10);

  // Get values or addresses
  long long firstPos = vectorIntcode->at(pos + 1);
  long long secondPos = vectorIntcode->at(pos + 2);
  long long targetPos = vectorIntcode->at(pos + 3);

  // get Values for the opcode
  long long firstVal = getParameterValue(modePar1, firstPos, relBase, vectorIntcode);
  long long secondVal = getParameterValue(modePar2, secondPos, relBase, vectorIntcode);
  long long writePos = getWritePos(modePar3, targetPos, relBase);

  // Operation
  vectorIntcode->at(writePos) = firstVal + secondVal;

  return (4);
}

long long CIntcodeComputer::opcodeMul(std::vector<long long> *vectorIntcode, long long pos, long long relBase, long long mode)
{
  long long modePar1 = (long long) (mode % 10);
  long long modePar2 = (long long) ((mode / 10) % 10);
  long long modePar3 = (long long) ((mode / 100) % 10);

  // Get values or addresses
  long long firstPos = vectorIntcode->at(pos + 1);
  long long secondPos = vectorIntcode->at(pos + 2);
  long long targetPos = vectorIntcode->at(pos + 3);

  // get Values for the opcode
  long long firstVal = getParameterValue(modePar1, firstPos, relBase, vectorIntcode);
  long long secondVal = getParameterValue(modePar2, secondPos, relBase, vectorIntcode);
  long long writePos = getWritePos(modePar3, targetPos, relBase);

  vectorIntcode->at(writePos) = firstVal * secondVal;

  return (4);
}

long long CIntcodeComputer::opcodeIn(std::vector<long long> *vectorIntcode, long long pos, long long relBase, long long mode)
{
  long long modePar1 = (long long) (mode % 10);
  long long writePos = vectorIntcode->at(pos + 1);

  // Get in value
  std::cout << "Input value: " << this->mInputValue << std::endl;

  // Operation
  // get Values for the opcode
  if (modePar1 == MODE_IMMEDIATE)
  {
    // nor supported here
    std::cout << "Problem immediate mode for IN" << std::endl;
  }
  else if (modePar1 == MODE_RELATIVE)
  {
    vectorIntcode->at(writePos + relBase) = this->mInputValue;
  }
  else
  {
    vectorIntcode->at(writePos) = this->mInputValue;
  }

  return (2);
}

long long CIntcodeComputer::opcodeOut(std::vector<long long> *vectorIntcode, long long pos, long long relBase, long long mode)
{
  long long modePar1 = (long long) (mode % 10);
  long long outPos = vectorIntcode->at(pos + 1);

  // get Values for the opcode
  this->mOutputValue = getParameterValue(modePar1, outPos, relBase, vectorIntcode);


  return (2);
}

long long CIntcodeComputer::opcodeJiT(std::vector<long long> *vectorIntcode, long long pos, long long relBase, long long mode)
{
  long long retPos = 3;
  long long modePar1 = (long long) (mode % 10);
  long long modePar2 = (long long) ((mode / 10) % 10);

  // Get values or addresses
  long long firstPos = vectorIntcode->at(pos + 1);
  long long secondPos = vectorIntcode->at(pos + 2);

  // get Values for the opcode
  long long firstVal = getParameterValue(modePar1, firstPos, relBase, vectorIntcode);
  long long secondVal = getParameterValue(modePar2, secondPos, relBase, vectorIntcode);

  if (firstVal != 0)
  {
    retPos = secondVal - pos; // I used relative jumps
  }

  return (retPos);
}

long long CIntcodeComputer::opcodeJiF(std::vector<long long> *vectorIntcode, long long pos, long long relBase, long long mode)
{
  long long retPos = 3;
  long long modePar1 = (long long) (mode % 10);
  long long modePar2 = (long long) ((mode / 10) % 10);

  // Get values or addresses
  long long firstPos = vectorIntcode->at(pos + 1);
  long long secondPos = vectorIntcode->at(pos + 2);

  // get Values for the opcode
  long long firstVal = getParameterValue(modePar1, firstPos, relBase, vectorIntcode);
  long long secondVal = getParameterValue(modePar2, secondPos, relBase, vectorIntcode);

  if (firstVal == 0)
  {
    retPos = secondVal - pos; // I used relative jumps
  }

  return (retPos);
}

long long CIntcodeComputer::opcodeLessThan(std::vector<long long> *vectorIntcode, long long pos, long long relBase, long long mode)
{
  long long modePar1 = (long long) (mode % 10);
  long long modePar2 = (long long) ((mode / 10) % 10);
  long long modePar3 = (long long) ((mode / 100) % 10);

  long long firstPos = vectorIntcode->at(pos + 1);
  long long secondPos = vectorIntcode->at(pos + 2);
  long long targetPos = vectorIntcode->at(pos + 3);

  // get Values for the opcode
  long long firstVal = getParameterValue(modePar1, firstPos, relBase, vectorIntcode);
  long long secondVal = getParameterValue(modePar2, secondPos, relBase, vectorIntcode);
  long long writePos = getWritePos(modePar3, targetPos, relBase);


  // Operation
  if (firstVal < secondVal)
  {
    vectorIntcode->at(writePos) = 1;
  }
  else
  {
    vectorIntcode->at(writePos) = 0;
  }

  return (4);
}

long long CIntcodeComputer::opcodeEquals(std::vector<long long> *vectorIntcode, long long pos, long long relBase, long long mode)
{
  long long modePar1 = (long long) (mode % 10);
  long long modePar2 = (long long) ((mode / 10) % 10);
  long long modePar3 = (long long) ((mode / 100) % 10);

  // Get values or addresses
  long long firstPos = vectorIntcode->at(pos + 1);
  long long secondPos = vectorIntcode->at(pos + 2);
  long long targetPos = vectorIntcode->at(pos + 3);

  // get Values for the opcode
  long long firstVal = getParameterValue(modePar1, firstPos, relBase, vectorIntcode);
  long long secondVal = getParameterValue(modePar2, secondPos, relBase, vectorIntcode);
  long long writePos = getWritePos(modePar3, targetPos, relBase);


  // Operation
  if (firstVal == secondVal)
  {
    vectorIntcode->at(writePos) = 1;
  }
  else
  {
    vectorIntcode->at(writePos) = 0;
  }

  return (4);
}

long long CIntcodeComputer::opcodeRelBaseAdjust(std::vector<long long> *vectorIntcode, long long pos, long long *relBase, long long mode)
{
  long long modePar1 = (long long) (mode % 10);

  // Get values or addresses
  long long firstPos = vectorIntcode->at(pos + 1);

  // get Values for the opcode
  if (modePar1 == MODE_IMMEDIATE)
  {
    *relBase += firstPos;
  }
  else if (modePar1 == MODE_RELATIVE)
  {
    *relBase += vectorIntcode->at(firstPos + *relBase);
  }
  else
  {
    *relBase += vectorIntcode->at(firstPos);
  }

  return (2);
}

long long CIntcodeComputer::getWritePos(long long mode, long long pos, long long relBase)
{
  long long value;

  // get Values for the opcode
  if (mode == MODE_IMMEDIATE)
  {
    value = pos;
  }
  else if (mode == MODE_RELATIVE)
  {
    value = pos + relBase;
  }
  else
  {
    value = pos;
  }

  return value;
}

long long CIntcodeComputer::getOuput(void)
{
  return(this->mOutputValue);
}

void CIntcodeComputer::setInput(long long inVal)
{
  this->mInputValue = inVal;
}
