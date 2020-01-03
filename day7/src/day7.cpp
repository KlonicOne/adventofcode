/*
 * day7.cpp
 */

#include <iostream>
#include <string>
#include <math.h>
#include <algorithm>
#include <fstream>
#include <functional>

#include "Amplifier.h"
#include "CIntcodeComputer.h"

using namespace std;

void setAmpOutput(long long outVal);
long long getAmpInputs(void);
void delAmps(void);
bool ampsRunning(void);

const unsigned numAmps = 5;
static long long outputValue = 0;
static bool phasePassed[numAmps] = { false, false, false, false, false };
static int amplifierPhase[numAmps] = { 5, 6, 7, 8, 9 };
static int currentAmplifierMaxPhase[numAmps] = { 0 };
static bool amplifierRunning[numAmps] = { 0 };
static long long currentMaxValue = 0;
static int currentPhasePos = 0;

static std::vector<CAmplifier*> Amplifier;

int main()
{
  std::ifstream ifile("input.txt");

  // callbacks
  auto callbackIn = std::bind(&getAmpInputs);
  auto callbackOut = std::bind(&setAmpOutput, std::placeholders::_1);

  // Initialize the amps
  // Add amplifier to the vector, init with phase and set callbacks
  for (unsigned itAmp = 0; itAmp < numAmps; itAmp++)
  {
    CAmplifier *amp = new CAmplifier(amplifierPhase[itAmp]); // new object of amplifier
    CIntcodeComputer *intcomp = new CIntcodeComputer; // new object of amplifier

    // Set brain of paint robot
    amp->setIncodeComputer(intcomp);

    // Prepare the call backs
    intcomp->setInputCallBackFunction(callbackIn);
    intcomp->setOutputCallBackFunction(callbackOut);

    Amplifier.push_back(amp); // new amp to vector of pointer for loops

    // Read the input code for the amp
    Amplifier[itAmp]->readInputCode(ifile);
    // File stream used so rewind for next loop
    ifile.clear();
    ifile.seekg(0);
  }

  // Here we loop until we find maximum through permutation
  std::sort(amplifierPhase, amplifierPhase + numAmps);

  do
  {
    // Reset output value for next loop over amps
    // Not done in second part as we have used as feedback
//    outputValue = 0;

    do
    {
      // loop through all amps with new permutation
      for (unsigned itAmp = 0; itAmp < numAmps; itAmp++)
      {
        // Set current phase pos for amp
        currentPhasePos = itAmp;

        // Progress the program for the color robot
        amplifierRunning[itAmp] = Amplifier[itAmp]->progressCode();
      }

      // Final output value from the loop calculated now check if it is new max
      if (outputValue > currentMaxValue)    // we found new max
      {
        // take over new max and phase settings
        currentMaxValue = outputValue;
        std::copy(std::begin(amplifierPhase), std::end(amplifierPhase), std::begin(currentAmplifierMaxPhase));

        // deug out
        std::cout << "Max: " << currentMaxValue << std::endl;
//        std::cout << "Max phases: " << currentAmplifierMaxPhase[0] << ", " << currentAmplifierMaxPhase[1] << ", "
//            << currentAmplifierMaxPhase[2] << ", " << currentAmplifierMaxPhase[3] << ", " << currentAmplifierMaxPhase[4]
//            << ", " << std::endl;
      }
    } while (ampsRunning());

    for (unsigned itAmp = 0; itAmp < numAmps; itAmp++)
    {
      // for next permutation we need to reset the intcomp computers
      phasePassed[itAmp] = false; // all get new the phase as first inputs
      Amplifier[itAmp]->resetIntcodeComputer();
    }

    std::cout << "Phase setting: "
        << amplifierPhase[0] << ", " << amplifierPhase[1] << ", "
        << amplifierPhase[2] << ", " << amplifierPhase[3] << ", " << amplifierPhase[4]
        << ", " << std::endl;

  } while (next_permutation(amplifierPhase, amplifierPhase + numAmps));

// output final value
  std::cout << "Result: " << currentMaxValue << std::endl;

  delAmps();
}

void delAmps(void)
{
  for (unsigned itAmp = numAmps; itAmp > 0; itAmp--)
  {
    delete (Amplifier[itAmp - 1]->getIntcodeComputer());
    delete (Amplifier[itAmp - 1]);
  }
}

bool ampsRunning(void)
{
  bool ampsRunning = false;
  for (unsigned itAmp = 0; itAmp < numAmps; itAmp++)
  {
    ampsRunning |= amplifierRunning[itAmp];
  }
  return (ampsRunning);
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
  long long inputVal;

// input is output from previous
  if (phasePassed[currentPhasePos])
  {
    inputVal = outputValue;
  }
// First input is phase
  else
  {
    inputVal = amplifierPhase[currentPhasePos];
    phasePassed[currentPhasePos] = true;
  }

//  std::cout << "In: " << std::endl;
//  std::cout << inputVal << std::endl;

  return (inputVal);
}

