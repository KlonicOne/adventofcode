/*
 * day7.cpp
 */

#include <iostream>
#include <string>
#include <math.h>
#include <fstream>
#include <functional>

#include "Amplifier.h"
#include "CIntcodeComputer.h"

using namespace std;

void setAmpOutput(long long outVal);
long long getAmpInputs(void);

const unsigned numAmps = 5;
static long long outputValue = 0;
static std::vector<int> amplifierPhase = { 1, 0, 4, 3, 2 };

int main()
{
  std::ifstream ifile("input.txt");
  std::vector<CAmplifier*> Amplifier;

  // callbacks
  auto callbackIn = std::bind(&getAmpInputs);
  auto callbackOut = std::bind(&setAmpOutput, std::placeholders::_1);

  // Add amplifier to the vector, init with phase and set callbacks
  for (unsigned i = 0; i < numAmps; i++)
  {
    CAmplifier *amp = new CAmplifier(amplifierPhase[i]); // new object of amplifier
    CIntcodeComputer *intcomp = new CIntcodeComputer; // new object of amplifier

    // Set brain of paint robot
    amp->setIncodeComputer(intcomp);

    // Prepare the paint robot call backs
    intcomp->setInputCallBackFunction(callbackIn);
    intcomp->setOutputCallBackFunction(callbackOut);

    Amplifier.push_back(amp); // new amp to vector of pointer
  }

  // Execute the amplifier and pass inputs and outputs
  for (unsigned i = 0; i < numAmps; i++)
  {
    // Read the input code for the paint robot
    Amplifier[i]->readInputCode(ifile);
    // File stream used so rewind for next loop
    ifile.clear();
    ifile.seekg(0);

    // Progress the program for the color robot
    Amplifier[i]->progressCode();
  }

  // output final value
  std::cout << "Result: " << outputValue << std::endl;
}

// Callbacks
void setAmpOutput(long long outVal)
{
  // Standard out for debugging
//  std::cout << "Out: " << outVal << std::endl;
  outputValue = outVal;
}

long long getAmpInputs(void)
{
  static int toggle = 0;
  static int currentPhasePos = 0;
  long long inputVal;

  // First input is phase
  if (toggle == 0)
  {
    inputVal = amplifierPhase[currentPhasePos];
    currentPhasePos++;
    toggle = 1;
  }
  // second is output from previous
  else if (toggle == 1)
  {
    inputVal = outputValue;
    toggle = 0;
  }
  else
  {
    std::cout << "Something went wrong!" << std::endl;
  }

//  std::cout << "In: " << std::endl;
//  std::cout << inputVal << std::endl;

  return (inputVal);
}

