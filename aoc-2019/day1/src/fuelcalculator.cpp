/*
 * fuelcalculator.cpp
 */

#include <math.h>
#include "fuelcalculator.h"

// Constructor
CFuelCalculator::CFuelCalculator()
{
}

// Destructor
CFuelCalculator::~CFuelCalculator(void)
{
}

// Function to calculate the fuel based on the module mass
int CFuelCalculator::getFuelOfModule(int moduleMass)
{
  // Calc fuel and return
  int fuelForModule = moduleMass / 3 - 2;
  fuelForModule = this->getFuelOfFuel(fuelForModule);
  return (fuelForModule);
}

// Calculate all fuel for fuel mass
int CFuelCalculator::getFuelOfFuel(int fuelMass)
{
  if (0 > fuelMass)
  {
    return(0);
  }
  else
  {
    return fuelMass += getFuelOfFuel(fuelMass / 3 - 2);
  }
}
