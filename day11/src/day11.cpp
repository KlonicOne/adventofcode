/*
 * day11.cpp
 */

#include <iostream>
#include <string>
#include <math.h>
#include <fstream>
#include <functional>
#include "CIntcodeComputer.h"
#include "CPaintRobot.h"

using namespace std;

int main()
{
  std::ifstream ifile("input.txt");

  CIntcodeComputer intcodeComp;
  CPaintRobot paintRobot;

  auto callbackIn = std::bind(&CPaintRobot::getCameraInput, &paintRobot);
  auto callbackOut = std::bind(&CPaintRobot::setIntCodeOutput, &paintRobot, std::placeholders::_1);

  // Set brain of paint robot
  paintRobot.setIncodeComputer(&intcodeComp);

  // Prepare the paint robot callbacks
  intcodeComp.setInputCallBackFunction(callbackIn);
  intcodeComp.setOutputCallBackFunction(callbackOut);

  // Read the input code for the paint robot
  paintRobot.readInputCode(ifile);

  // Progress the program for the color robot
  paintRobot.progressPaintRobotCode();

  paintRobot.printPathOfPaintBot();

  // Output
  int coloredFields = paintRobot.getNumberOfColoredFields();
  std::cout << "Colored fields: " << coloredFields << std::endl;

}

