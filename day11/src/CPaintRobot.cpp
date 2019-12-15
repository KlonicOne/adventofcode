/*
 * CPaintRobot.cpp
 *
 *  Created on: 15.12.2019
 *      Author: Nico
 */

#include <iostream>
#include "CPaintRobot.h"

using namespace std;

#define INIT_SIZE (10000000)

CPaintRobot::CPaintRobot()
{
  this->mIntComputer = NULL;
  this->mTypeOfOutputValue = e_color;
  this->mNumberOfColoredFields = 0;
  this->mCurrentPaintBotPos = std::make_tuple(0, 0, e_up);
}

CPaintRobot::~CPaintRobot()
{
  // TODO Auto-generated destructor stub
}

void CPaintRobot::readInputCode(istream &input)
{
  this->mIntComputer->parseVectorCode(input);

  // extend vector as it will happen that we write behind the program
  this->mIntComputer->resizeIntCodePrg(INIT_SIZE);
}

long long CPaintRobot::getCameraInput(void)
{
  long long colorCurrentPos;
  // Color of current position of paint robot
  colorCurrentPos = this->mColorMap[std::get < 0 > (this->mCurrentPaintBotPos)][std::get < 1
      > (this->mCurrentPaintBotPos)];

  return (colorCurrentPos);
}

void CPaintRobot::setIncodeComputer(CIntcodeComputer *IntComp)
{
  this->mIntComputer = IntComp;
}

void CPaintRobot::progressPaintRobotCode(void)
{
  // Progress new code vector
  mIntComputer->progressVectorCode(mCodeVector);
}

void CPaintRobot::setCallBackFunctions(void)
{
  // The call back functions are called on the intcode computer input and output
  mIntComputer->setInputCallBackFunction(this->getCameraInput);
  mIntComputer->setOutputCallBackFunction(this->setIntCodeOutput);
}

void CPaintRobot::setIntCodeOutput(long long outVal)
{
  // The values iterate color and movement
  switch (this->mTypeOfOutputValue)
  {
    case (e_color): // Color given paint current position in map
    {
      this->colorTheCurrentPosition(outVal);
      this->mTypeOfOutputValue = e_turn; // next time turn robot
      break;
    }
    case (e_turn): // Turn given call function for movement
    {
      this->moveThePaintRobot(outVal);
      this->mTypeOfOutputValue = e_color; // next time color
      break;
    }
    default:
      break;
  }
}

CIntcodeComputer* CPaintRobot::getIntcodeComputer(void)
{
  return (this->mIntComputer);
}

void CPaintRobot::colorTheCurrentPosition(long long color)
{
  long long currentColor = this->mColorMap[std::get < 0 > (this->mCurrentPaintBotPos)][std::get < 1
      > (this->mCurrentPaintBotPos)];
  long long newColor = color;

  // Check if the field need to be colored
  if (currentColor != newColor)
  {
    this->mColorMap[std::get < 0 > (this->mCurrentPaintBotPos)][std::get < 1 > (this->mCurrentPaintBotPos)] = color;
    mNumberOfColoredFields = mNumberOfColoredFields + 1;
  }
}

void CPaintRobot::moveThePaintRobot(long long turnDirection)
{
  long long nextXPos = get < 0 > (this->mCurrentPaintBotPos);
  long long nextYPos = get < 1 > (this->mCurrentPaintBotPos);
  t_robotOrientation nextOrientation = get < 2 > (this->mCurrentPaintBotPos);

  if (turnDirection == 0) // left turn
  {
    // first turn
    nextOrientation = getNextOrientation(get < 2 > (this->mCurrentPaintBotPos), turnDirection);
  }
  else if (turnDirection == 1) // right turn
  {
    // first turn
    nextOrientation = getNextOrientation(get < 2 > (this->mCurrentPaintBotPos), turnDirection);
  }
  else
  {
    std::cout << "Invalid turn" << std::endl;
  }

  // then move
  switch (nextOrientation)
  {
    case (e_up):
    {
      nextYPos = nextYPos - 1;
      break;
    }
    case (e_down):
    {
      nextYPos = nextYPos + 1;
      break;
    }
    case (e_left):
    {
      nextXPos = nextXPos - 1;
      break;
    }
    case (e_right):
    {
      nextXPos = nextXPos + 1;
      break;
    }
  }

  // set new position for the robot
  std::get < 0 > (this->mCurrentPaintBotPos) = nextXPos;
  std::get < 1 > (this->mCurrentPaintBotPos) = nextYPos;
  std::get < 2 > (this->mCurrentPaintBotPos) = nextOrientation;
}

t_robotOrientation CPaintRobot::getNextOrientation(t_robotOrientation inOrientation, long long turnDirection)
{
  t_robotOrientation retValue;

  switch (inOrientation)
  {
    case (e_up):
    {
      if (turnDirection == 0) // turn left
      {
        retValue = e_left;
      }
      else if (turnDirection == 1) // right
      {
        retValue = e_right;
      }
      else
      {
        std::cout << "Invalid turn!" << std::endl;
      }
      break;
    }
    case (e_left):
    {
      if (turnDirection == 0) // turn left
      {
        retValue = e_down;
      }
      else if (turnDirection == 1) // right
      {
        retValue = e_up;
      }
      else
      {
        std::cout << "Invalid turn!" << std::endl;
      }
      break;
    }
    case (e_right):
    {
      if (turnDirection == 0) // turn left
      {
        retValue = e_up;
      }
      else if (turnDirection == 1) // right
      {
        retValue = e_down;
      }
      else
      {
        std::cout << "Invalid turn!" << std::endl;
      }
      break;
    }
    case (e_down):
    {
      if (turnDirection == 0) // turn left
      {
        retValue = e_right;
      }
      else if (turnDirection == 1) // right
      {
        retValue = e_left;
      }
      else
      {
        std::cout << "Invalid turn!" << std::endl;
      }
      break;
    }
  }
  return (retValue);
}
