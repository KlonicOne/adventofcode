/*
 * CIntcodeComputer.h
 *
 *  Created on: 3 Dec 2019
 *      Author: nico
 */

#ifndef CDECODEPW_H_
#define CDECODEPW_H_

#include <vector>
#include <istream>
#include <sstream>
using namespace std;

class CDecodePW
{
public:
  CDecodePW();
  virtual ~CDecodePW();

  std::vector<int> stringToVec(std::string tempString);
  bool checkCodePart1(int inputCode);
  bool checkCodePart2(int inputCode);
};

#endif /* CDECODEPW_H_ */
