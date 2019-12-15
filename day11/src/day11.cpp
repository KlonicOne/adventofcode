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

  CIntcodeComputer intcodeComp;
  CPaintRobot paintRobot;

  // Set brain of paint robot
  paintRobot.setIncodeComputer(&intcodeComp);

  // Prepare the paint robot
  paintRobot.setCallBackFunctions();

  // Read the input code for the paint robot
  paintRobot.readInputCode(ifile);

  // Progress the program for the color robot
  paintRobot.progressPaintRobotCode();

  // Output

}

