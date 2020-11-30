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

#include "CDecodePW.h"

CDecodePW::CDecodePW()
{
  // TODO Auto-generated constructor stub

}

CDecodePW::~CDecodePW()
{
  // TODO Auto-generated destructor stub
}

std::vector<int> CDecodePW::stringToVec(std::string tempString)
{
  stringstream tempSS;
  std::vector<int> tempIntVector;
  int tempInt;

  for (unsigned z = 0; z < tempString.size(); z++)
  {
    tempInt = tempString[z] - 48;
    tempIntVector.push_back(tempInt);
  }

  return tempIntVector;
}


bool CDecodePW::checkCodePart1(int inputCode)
{
  bool returnObject = false;
  bool doubleDigitLock = false;
  bool lookAhead = true;
  std::vector<int> digits;

  digits = this->stringToVec(to_string(inputCode));

  for (size_t i = 0; i < digits.size() - 1; i++)
  {
    if (digits.at(i) <= digits.at(i + 1) && lookAhead == true)
    {
      returnObject = true;

      if (digits.at(i) == digits.at(i + 1))
      {
        returnObject = true;
        doubleDigitLock = true;
      }
      else
      {
        if (doubleDigitLock)
        {
          returnObject = true;
        }
        else
        {
          returnObject = false;
        }
      }
    }
    else
    {
      lookAhead = false;
      returnObject = false;
    }
  }

  return returnObject;
}


bool CDecodePW::checkCodePart2(int inputCode)
{
  bool returnObject = false;
  bool doubleDigitLock = false;
  bool lookAhead = true;
  bool trippleFail = false;
  int trippleFailInt = 0;
  std::vector<int> digits;

  digits = this->stringToVec(to_string(inputCode));

  for (size_t i = 0; i < digits.size() - 1; i++)
  {
    if (i < digits.size() - 2)
    {
      if (digits.at(i) == digits.at(i + 1) && digits.at(i) == digits.at(i + 2))
      {
        trippleFail = true;
        trippleFailInt = digits.at(i);
      }
    }

    if (digits.at(i) <= digits.at(i + 1) && lookAhead == true)
    {
      if ((trippleFail == false) | (trippleFailInt != digits.at(i)))
      {
        returnObject = true;

        if (digits.at(i) == digits.at(i + 1))
        {
          returnObject = true;
          doubleDigitLock = true;
        }
        else
        {
          if (doubleDigitLock)
          {
            returnObject = true;
          }
          else
          {
            returnObject = false;
          }
        }
      }
    }
    else
    {
      lookAhead = false;
      returnObject = false;
    }
  }

  return returnObject;
}
