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
#define OPCODE_IN 3
#define OPCODE_OUT 4
#define OPCODE_JIT 5
#define OPCODE_JIF 6
#define OPCODE_LESSTHAN 7
#define OPCODE_EQUALS 8
#define OPCODE_RELBASEADJUST 9

#define MODE_RELATIVE (2)
#define MODE_IMMEDIATE (1)
#define MODE_POSITION (0)

class CIntcodeComputer
{
public:
  CIntcodeComputer();
  virtual ~CIntcodeComputer();

  std::vector<int> getVectorCode(istream &input);
  std::vector<int> progressVectorCode(std::vector<int> vectorIntcode);
  int nounVerbResultProducedInput(std::vector<int> vectorIntcode, int targetVal);
  void debugOutVector(vector<int> inVector);

private:
  // Opcodes
  int opcodeAdd(std::vector<int> *vectorIntcode, int pos, int relBase, unsigned mode);
  int opcodeMul(std::vector<int> *vectorIntcode, int pos, int relBase, unsigned mode);
  int opcodeIn(std::vector<int> *vectorIntcode, int pos, int relBase, unsigned mode);
  int opcodeOut(std::vector<int> *vectorIntcode, int pos, int relBase, unsigned mode);
  int opcodeJiT(std::vector<int> *vectorIntcode, int pos, int relBase, unsigned mode);
  int opcodeJiF(std::vector<int> *vectorIntcode, int pos, int relBase, unsigned mode);
  int opcodeLessThan(std::vector<int> *vectorIntcode, int pos, int relBase, unsigned mode);
  int opcodeEquals(std::vector<int> *vectorIntcode, int pos, int relBase, unsigned mode);
  int opcodeRelBaseAdjust(std::vector<int> *vectorIntcode, int pos, int *relBase, unsigned mode);
};

#endif /* CINTCODECOMPUTER_H_ */
