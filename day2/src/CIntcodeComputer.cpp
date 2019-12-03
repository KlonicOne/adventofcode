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

  //this->debugOutVector(codeVector);

  return (codeVector);
}

std::vector<int> CIntcodeComputer::progressVectorCode(std::vector<int> vectorIntcode)
{
  int firstVal;
  int secondVal;

  // Walk through given intcode in stepsize 4 until end reached
  for (std::vector<int>::const_iterator Opcode = vectorIntcode.begin(); *Opcode != OPCODE_END; Opcode += 4)
  {
    //std::cout << *Opcode << ' ';
    switch (*Opcode)
    {
    case (OPCODE_ADD):
      firstVal = vectorIntcode.at(*Opcode + 1);
      secondVal = vectorIntcode.at(*Opcode + 2);
      vectorIntcode.at(*Opcode + 3) = firstVal + secondVal;
      break;
    case (OPCODE_MUL):
      firstVal = vectorIntcode.at(*Opcode + 1);
      secondVal = vectorIntcode.at(*Opcode + 2);
      vectorIntcode.at(*Opcode + 3) = firstVal * secondVal;
      break;
    default:
      break;
    }
  }
  this->debugOutVector(vectorIntcode);
  return (vectorIntcode);
}

void CIntcodeComputer::debugOutVector(vector<int> inVector)
{
  for (std::vector<int>::const_iterator i = inVector.begin(); i != inVector.end(); ++i)
  {
    std::cout << *i << ',' << ' ';
  }
}
