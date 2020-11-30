/*
 * CIntcodeComputer.h
 *
 *  Created on: 3 Dec 2019
 *      Author: nico
 */

#ifndef CINTCODECOMPUTER_H_
#define CINTCODECOMPUTER_H_

#include <vector>
#include <tuple>
#include <istream>
using namespace std;

// Opcode defines
#define OPCODE_END (99)
#define OPCODE_ADD (1)
#define OPCODE_MUL (2)
#define OPCODE_IN (3)
#define OPCODE_OUT (4)
#define OPCODE_JIT (5)
#define OPCODE_JIF (6)
#define OPCODE_LESSTHAN (7)
#define OPCODE_EQUALS (8)
#define OPCODE_RELBASEADJUST (9)

// Mode defines
#define MODE_RELATIVE (2)
#define MODE_IMMEDIATE (1)
#define MODE_POSITION (0)

// Objects
#define EMPTY (0)
#define WALL (1)
#define BLOCK (2)
#define H_PADDLE (3)
#define BALL (4)

class CIntcodeComputer
{
public:
  CIntcodeComputer();
  virtual ~CIntcodeComputer();

  int createScreenMap(std::vector<long long> inputScreenMap);
  int initScreenMap(void);
  int initStatisticsVectorScreenMap(void);
  int printScreenMap(void);
  long long getOuput(void);
  long long getProgramSizeInputCode() const;
  long long nounVerbResultProducedInput(std::vector<long long> vectorIntcode, long long targetVal);
  std::vector<long long> getVectorCode(istream &input);
  std::vector<long long> progressVectorCode(std::vector<long long> vectorIntcode);
  void debugOutVector(vector<int> inVector);
  void debugOutVector(vector<long long> inVector);
  void setInput(long long inVal);
  void setProgramSizeInputCode(long long programSizeInputCode);

private:
  // program size of original read program
  long long programSizeInputCode;

  // Map size
  const int xDim = 1000;
  const int yDim = 1000;

  // member
  long long mInputValue;
  long long mOutputValue;

  // screen variable
  std::vector<std::vector<long long>> mScreenMap;
  std::vector<std::tuple<long long, long long>> mObjectStatistics;

  // Screen map fct
  int initScreenMap(std::vector<std::vector<int>> *ptrScreenMap);

  // Opcodes
  long long opcodeAdd(std::vector<long long> *vectorIntcode, long long pos, long long relBase, long long mode);
  long long opcodeMul(std::vector<long long> *vectorIntcode, long long pos, long long relBase, long long mode);
  long long opcodeIn(std::vector<long long> *vectorIntcode, long long pos, long long relBase, long long mode);
  long long opcodeOut(std::vector<long long> *vectorIntcode, long long pos, long long relBase, long long mode);
  long long opcodeJiT(std::vector<long long> *vectorIntcode, long long pos, long long relBase, long long mode);
  long long opcodeJiF(std::vector<long long> *vectorIntcode, long long pos, long long relBase, long long mode);
  long long opcodeLessThan(std::vector<long long> *vectorIntcode, long long pos, long long relBase, long long mode);
  long long opcodeEquals(std::vector<long long> *vectorIntcode, long long pos, long long relBase, long long mode);
  long long opcodeRelBaseAdjust(std::vector<long long> *vectorIntcode, long long pos, long long *relBase,
      long long mode);

  long long getParameterValue(long long mode, long long pos, long long relBase, std::vector<long long> *vectorIntcode);
  long long getWritePos(long long mode, long long pos, long long relBase);
};

#endif /* CINTCODECOMPUTER_H_ */
