/*
 * CIntcodeComputer.h
 *
 *  Created on: 3 Dec 2019
 *      Author: nico
 */

#ifndef CDECODEPW_H_
#define CDECODEPW_H_

#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <map>
#include <set>

#include <vector>
#include <istream>
using namespace std;

class CDecodePW
{
public:
  CDecodePW();
  virtual ~CDecodePW();
  std::vector<int> stringToVec(std::string tempString);
  bool checkNumber(int inputInt);
  bool checkNumberPart2(int inputInt);
};

#endif /* CDECODEPW_H_ */
