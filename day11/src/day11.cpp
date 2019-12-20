/*
 * day11.cpp
 */

#include <iostream>
#include <string>
#include <math.h>
#include <fstream>
#include "CIntcodeComputer.h"
#include "CPaintRobot.h"

using namespace std;

int main()
{
  std::ifstream ifile("input.txt");
  auto callbackIn = std::bind(&CPaintRobot::getCameraInput, CPaintRobot());
  auto callbackOut = std::bind(&CPaintRobot::setIntCodeOutput, CPaintRobot(), std::placeholders::_1);

  CIntcodeComputer intcodeComp;
  CPaintRobot paintRobot;

  // Set brain of paint robot
  paintRobot.setIncodeComputer(&intcodeComp);

  // Prepare the paint robot callbacks
  intcodeComp.setInputCallBackFunction(callbackIn);
  intcodeComp.setOutputCallBackFunction(callbackOut);

  // Read the input code for the paint robot
  paintRobot.readInputCode(ifile);

  // Progress the program for the color robot
  paintRobot.progressPaintRobotCode();

  // Output

}

