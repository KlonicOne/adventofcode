/*
 * CAmplifier.h
 *
 *  Created on: 15.12.2019
 *      Author: Nico
 */

#ifndef AMPLIFIER_H_
#define AMPLIFIER_H_

#include <vector>
#include <tuple>
#include "CIntcodeComputer.h"

// Amplifier Class
class CAmplifier
{
public:
  CAmplifier(int phase);
  virtual ~CAmplifier();

  // Read the input stream from file and store inside the intcode computer
  void readInputCode(istream &input);
  void setPhase(int phase);
  int getPhase(void);

  // These two functions to be used as callbacks on input and output for intcomp
  long long getIntcodeInput(void);
  void setIntcodeOutput(long long outVal);

  // Go through the intcode computer code, for in and out callbacks are used
  bool progressCode(void);

  // To set and get the brain of the paint robot
  void setIncodeComputer(CIntcodeComputer *IntComp);
  CIntcodeComputer* getIntcodeComputer(void);
  void resetIntcodeComputer(void);

private:
  CIntcodeComputer *mIntComputer; // Reference to the brain, the intcode computer
  std::vector<long long> mCodeVector;

  int mPhase;
};

#endif /* AMPLIFIER_H_ */
