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
#include <functional>

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
  // Getter and setter for the size of the original intcode program size
  long long getProgramSizeInputCode();
  void setProgramSizeInputCode(long long codeSize);
  // Callback functions to be able to manipulate the input and output
  void setInputCallBackFunction(std::function<long long(void)> fp);
  void setOutputCallBackFunction(std::function<void(long long)> fp);
  // Read in code an
  void parseVectorCode(istream &input);
  std::vector<long long> getIntCodePrg(void);
  void resizeIntCodePrg(long long newSize);
  void progressVectorCode(std::vector<long long> vectorIntcode);
  std::vector<long long> getProgressedIntCodePrg(void);
  long long nounVerbResultProducedInput(std::vector<long long> vectorIntcode, long long targetVal);
  void debugOutVector(std::vector<long long> inVector);

private:
  // Program size and program parsed from input string
  long long mProgramSizeInputCode;
  std::vector<long long> mIntCodeProgram;
  std::vector<long long> mProgressedIntCodeProgram;

  // Call back signature
  std::function<long long(void)> inputCallBackFunction;
  std::function<void(long long)> outputCallBackFunction;


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
  long long getWritePos(long long mode, long long pos, long long relBase);
};

#endif /* CINTCODECOMPUTER_H_ */
