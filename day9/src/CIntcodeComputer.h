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

// Mode defines
#define MODE_RELATIVE (2)
#define MODE_IMMEDIATE (1)
#define MODE_POSITION (0)

class CIntcodeComputer
{
public:
  CIntcodeComputer();
  virtual ~CIntcodeComputer();

  std::vector<long long> getVectorCode(istream &input);
  std::vector<long long> progressVectorCode(std::vector<long long> vectorIntcode, long long programSize);
  long long nounVerbResultProducedInput(std::vector<long long> vectorIntcode, long long targetVal);
  void debugOutVector(vector<long long> inVector);

private:
  // Opcodes
  long long opcodeAdd(std::vector<long long> *vectorIntcode, long long pos, long long relBase, long long mode);
  long long opcodeMul(std::vector<long long> *vectorIntcode, long long pos, long long relBase, long long mode);
  long long opcodeIn(std::vector<long long> *vectorIntcode, long long pos, long long relBase, long long mode);
  long long opcodeOut(std::vector<long long> *vectorIntcode, long long pos, long long relBase, long long mode);
  long long opcodeJiT(std::vector<long long> *vectorIntcode, long long pos, long long relBase, long long mode);
  long long opcodeJiF(std::vector<long long> *vectorIntcode, long long pos, long long relBase, long long mode);
  long long opcodeLessThan(std::vector<long long> *vectorIntcode, long long pos, long long relBase, long long mode);
  long long opcodeEquals(std::vector<long long> *vectorIntcode, long long pos, long long relBase, long long mode);
  long long opcodeRelBaseAdjust(std::vector<long long> *vectorIntcode, long long pos, long long *relBase, long long mode);

  long long getParameterValue(long long mode, long long pos, long long relBase, std::vector<long long>* vectorIntcode);
};

#endif /* CINTCODECOMPUTER_H_ */
