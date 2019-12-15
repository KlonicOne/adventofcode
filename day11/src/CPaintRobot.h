/*
 * CPaintRobot.h
 *
 *  Created on: 15.12.2019
 *      Author: Nico
 */

#ifndef CPAINTROBOT_H_
#define CPAINTROBOT_H_

#include <vector>
#include <tuple>
#include "CIntcodeComputer.h"

#define YDIM 1000
#define XDIM 1000

typedef enum t_OutputValueType
{
  e_color = 0, e_turn
} t_OutputValueType;

typedef enum t_robotOrientation
{
  e_up = 0,
  e_right,
  e_down,
  e_left
} t_robotOrientation;

class CPaintRobot
{
public:
  CPaintRobot();
  virtual ~CPaintRobot();

  void readInputCode(istream &input);
  void setCallBackFunctions(void);

  long long getCameraInput(void);
  void setIntCodeOutput(long long outVal);

  void progressPaintRobotCode(void);

  void setIncodeComputer(CIntcodeComputer *IntComp);
  CIntcodeComputer* getIntcodeComputer(void);

private:
  CIntcodeComputer *mIntComputer; // Reference to the brain, the intcode computer
  std::vector<long long> mCodeVector; // Store the code program

  // Paint robot pos, path and map
  long long mYMapDim = YDIM;
  long long mXMapDim = XDIM;
  tuple<long long, long long, t_robotOrientation> mCurrentPaintBotPos;
  std::vector<tuple<long long, long long>> mPathOfPaintBot;
  long long mColorMap[XDIM][YDIM];

  // The output value alternate between color and turning direction this tells the type
  t_OutputValueType mTypeOfOutputValue;
  int mNumberOfColoredFields;

  void colorTheCurrentPosition(long long color);
  void moveThePaintRobot(long long turnDirection);

  t_robotOrientation getNextOrientation(t_robotOrientation inOrientation, long long turnDirection);

};

#endif /* CPAINTROBOT_H_ */
