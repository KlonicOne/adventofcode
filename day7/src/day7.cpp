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

int main()
{
  std::ifstream ifile("input.txt");

  CIntcodeComputer intcodeCompA;
  CAmplifier AmplifierA;

  auto callbackIn = std::bind(&CAmplifier::getIntcodeInput, &AmplifierA);
  auto callbackOut = std::bind(&CAmplifier::setIntcodeOutput, &AmplifierA, std::placeholders::_1);

  // Set brain of paint robot
  AmplifierA.setIncodeComputer(&intcodeCompA);

  // Prepare the paint robot callbacks
  intcodeCompA.setInputCallBackFunction(callbackIn);
  intcodeCompA.setOutputCallBackFunction(callbackOut);

  // Read the input code for the paint robot
  AmplifierA.readInputCode(ifile);

  // Progress the program for the color robot
  AmplifierA.progressCode();

}

