#ifndef _FUELCALCULATOR_
#define _FUELCALCULATOR_

#include <iostream>

using namespace std;

class CFuelCalculator
{
public:
  CFuelCalculator();
  ~CFuelCalculator();
  int getFuelOfModule(int moduleMass);

private:
  int getFuelOfFuel(int fuelMass);

};

#endif // _FUELCALCULATOR_
