/*
 * CAmplifier.cpp
 *
 *  Created on: 15.12.2019
 *      Author: Nico
 */

#include <iostream>

#include "Amplifier.h"

using namespace std;

#define INIT_SIZE (1000)

CAmplifier::CAmplifier(int phase)
{
  this->mPhase = phase;
  this->mIntComputer = NULL;
}

CAmplifier::~CAmplifier()
{
}

void CAmplifier::readInputCode(istream &input)
{
  this->mIntComputer->parseVectorCode(input);

  // extend vector as it will happen that we write behind the program
  this->mIntComputer->resizeIntCodePrg(INIT_SIZE);
}

long long CAmplifier::getIntcodeInput(void)
{
  long long inputVal;
  std::cout << "In: " << std::endl;
  std::cin >> inputVal;

  return (inputVal);
}

void CAmplifier::setIncodeComputer(CIntcodeComputer *IntComp)
{
  this->mIntComputer = IntComp;
}

void CAmplifier::progressCode(void)
{
  // Get the int code in which shall be prepared
  this->mCodeVector = mIntComputer->getIntCodePrg();

  // Progress new code vector
  mIntComputer->progressVectorCode(this->mCodeVector);
}

void CAmplifier::setIntcodeOutput(long long outVal)
{
  // Standard out for debugging
  std::cout << "Out: " << outVal << std::endl;
}

CIntcodeComputer* CAmplifier::getIntcodeComputer(void)
{
  return (this->mIntComputer);
}

void CAmplifier::setPhase(int phase)
{
  this->mPhase = phase;
}

int CAmplifier::getPhase(void)
{
  return(this->mPhase);
}
