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
void resetAllAmpsComputer();
void isNewMax(long long value);

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

    amp->setIncodeComputer(intcomp); // Set brain of paint robot
    // Prepare the call backs
    intcomp->setInputCallBackFunction(callbackIn); // Callback for input
    intcomp->setOutputCallBackFunction(callbackOut); // and output

    Amplifier.push_back(amp); // new amp to vector of pointer for loops

    // Read the input code for the amp
    Amplifier[itAmp]->readInputCode(ifile);
    // File stream used so rewind for next loop
    ifile.clear();
    ifile.seekg(0);
  }

  // First sort the vector of phases to iterate over all permutations
  std::sort(amplifierPhase, amplifierPhase + numAmps);

  do // Loop over all permutations
  {
    // Reset output value for next loop over amps
    outputValue = 0;
    do // Loop until all amps are returning FASLSE which means they are on a stop opcode
    {
      for (unsigned itAmp = 0; itAmp < numAmps; itAmp++) // Call amps in order A-B-C-D-E-F
      {
        currentPhasePos = itAmp; // Set current amp iterator, used in callback functions
        amplifierRunning[itAmp] = Amplifier[itAmp]->progressCode(); // Progress the program for the color robot
      }

      // Final output value from the loop calculated now check if it is new max
      isNewMax(outputValue);

    } while (ampsRunning());

    // The permutation is checked, so reset intcode computer and pass again the phases on first calls
    resetAllAmpsComputer();
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

void resetAllAmpsComputer()
{
  // The permutation is checked, so reset intcode computer and pass again the phases on first calls
  for (unsigned itAmp = 0; itAmp < numAmps; itAmp++)
  {
    // for next permutation we need to reset the intcomp computers
    phasePassed[itAmp] = false; // all get new the phase as first inputs
    Amplifier[itAmp]->resetIntcodeComputer();
  }
}

void isNewMax(long long value)
{
  // Final output value from the loop calculated now check if it is new max
  if (value > currentMaxValue) // we found new max
  {
    // take over new max and phase settings
    currentMaxValue = value;
    std::copy(std::begin(amplifierPhase), std::end(amplifierPhase), std::begin(currentAmplifierMaxPhase));
    // deug out current max and the phases for it
    //        std::cout << "Max: " << currentMaxValue << std::endl;
    //        std::cout << "Max phases: " << currentAmplifierMaxPhase[0] << ", " << currentAmplifierMaxPhase[1] << ", "
    //            << currentAmplifierMaxPhase[2] << ", " << currentAmplifierMaxPhase[3] << ", " << currentAmplifierMaxPhase[4]
    //            << ", " << std::endl;
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

