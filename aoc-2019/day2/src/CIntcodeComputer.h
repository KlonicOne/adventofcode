/*
 * CIntcodeComputer.h
 *
 *  Created on: 3 Dec 2019
 *      Author: nico
 */

#ifndef CINTCODECOMPUTER_H_
#define CINTCODECOMPUTER_H_

#include <vector>
#include <istream>
using namespace std;

// Opcode defines
#define OPCODE_END 99
#define OPCODE_ADD 1
#define OPCODE_MUL 2

class CIntcodeComputer
{
public:
  CIntcodeComputer();
  virtual ~CIntcodeComputer();

  std::vector<int> getVectorCode(istream &input);
  std::vector<int> progressVectorCode(std::vector<int> vectorIntcode);
  int nounVerbResultProducedInput(std::vector<int> vectorIntcode, int targetVal);

private:
  void debugOutVector(vector<int> inVector);

};

#endif /* CINTCODECOMPUTER_H_ */
