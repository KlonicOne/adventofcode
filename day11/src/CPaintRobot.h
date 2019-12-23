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

#define YDIM 200 // Map y
#define XDIM 200 // Map z
#define ZDIM 2 // Two dimensions in z, first for color, second how often the field was colored

// Type for the output value, coming from intcode computer iterating
typedef enum t_OutputValueType
{
  e_color = 0, e_turn
} t_OutputValueType;

// Orientation used for robot orientation to know in which direction the step is done
typedef enum t_robotOrientation
{
  e_up = 0,
  e_right,
  e_down,
  e_left
} t_robotOrientation;

// Class for paint robot itself
class CPaintRobot
{
public:
  CPaintRobot();
  virtual ~CPaintRobot();

  // Read the input stream from file and store inside the intcode computer
  void readInputCode(istream &input);

  // These two functions to be used as callbacks on input and output for intcomp
  long long getCameraInput(void);
  void setIntCodeOutput(long long outVal);

  // Go through the intcode computer code, for in and out callbacks are used
  void progressPaintRobotCode(void);
  void calcPaintedFieldStat(void);

  // To set and get the brain of the paint robot
  void setIncodeComputer(CIntcodeComputer *IntComp);
  CIntcodeComputer* getIntcodeComputer(void);

  // Outputs of robot
  int getNumberOfColoredFields(void);
  void printPathOfPaintBot(void);

private:
  CIntcodeComputer *mIntComputer; // Reference to the brain, the intcode computer
  std::vector<long long> mCodeVector; // Store the code program

  // Paint robot pos, path and map
  long long mYMapDim = YDIM;
  long long mXMapDim = XDIM;
  long long mZMapDim = ZDIM;

  tuple<long long, long long, t_robotOrientation> mCurrentPaintBotPos;
  std::vector<tuple<long long, long long>> mPathOfPaintBot;
  long long mColorMap[XDIM][YDIM][ZDIM];

  // The output value alternate between color and turning direction this tells the type
  t_OutputValueType mTypeOfOutputValue;
  int mNumberOfColoredFields;

  void colorTheCurrentPosition(long long color);
  void moveThePaintRobot(long long turnDirection);

  t_robotOrientation getNextOrientation(t_robotOrientation inOrientation, long long turnDirection);

};

#endif /* CPAINTROBOT_H_ */
