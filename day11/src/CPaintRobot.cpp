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
  // We set the bot in the middle of the map
  this->mCurrentPaintBotPos = std::make_tuple(XDIM / 2, YDIM / 2, e_up);
  this->mPathOfPaintBot.push_back(std::make_tuple(XDIM / 2, YDIM / 2));
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

  colorCurrentPos = this->mColorMap[std::get < 0 > (this->mCurrentPaintBotPos)][std::get < 1
      > (this->mCurrentPaintBotPos)][0];

//  std::cout << "In: " << std::endl;
//  std::cin >> colorCurrentPos;

  return (colorCurrentPos);
}

void CPaintRobot::setIncodeComputer(CIntcodeComputer *IntComp)
{
  this->mIntComputer = IntComp;
}

void CPaintRobot::progressPaintRobotCode(void)
{
  // Get the int code in which shall be prepared
  this->mCodeVector = mIntComputer->getIntCodePrg();

  // Progress new code vector
  mIntComputer->progressVectorCode(this->mCodeVector);
}

void CPaintRobot::setIntCodeOutput(long long outVal)
{
  // Standard out for debugging
  std::cout << "Out(" << this->mTypeOfOutputValue << "): " << outVal << std::endl;

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
      > (this->mCurrentPaintBotPos)][0];
  long long newColor = color;

  std::cout << "New: " << newColor << " Current " << currentColor << std::endl;

  // Check if the field need to be colored
  if (currentColor != newColor)
  {
    // Change color and count up how often the field was colored
    this->mColorMap[std::get < 0 > (this->mCurrentPaintBotPos)][std::get < 1 > (this->mCurrentPaintBotPos)][0] = color;
    // Count fields colored once
    if (this->mColorMap[std::get < 0 > (this->mCurrentPaintBotPos)][std::get < 1 > (this->mCurrentPaintBotPos)][1] == 0)
    {
      this->mNumberOfColoredFields += 1; // The field is colored the first time
    }
    this->mColorMap[std::get < 0 > (this->mCurrentPaintBotPos)][std::get < 1 > (this->mCurrentPaintBotPos)][1] += 1;
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

  // Store path of robot
  this->mPathOfPaintBot.push_back(std::make_tuple(nextXPos, nextYPos)); // new position and color not changed

  // Debug out the position to check how often we hit same position
  std::cout << "RoPos: " << nextXPos << ", " << nextYPos << ", " << nextOrientation << std::endl;
}

int CPaintRobot::getNumberOfColoredFields(void)
{
  return (this->mNumberOfColoredFields);
}

void CPaintRobot::printPathOfPaintBot(void)
{
  std::vector<std::tuple<long long, long long>>::iterator it;

  for (it = this->mPathOfPaintBot.begin(); it != this->mPathOfPaintBot.end(); it++)
  {
    std::cout << "RoPath: " << get < 0 > (*it) << ", " << get < 1 > (*it) << std::endl;
  }
}

void CPaintRobot::calcPaintedFieldStat(void)
{
  // go through map and check how many fields are colored at least once
  for (unsigned i = 0; i < this->mXMapDim; i++)
  {
    for (unsigned j = 0; j < this->mYMapDim; j++)
    {
      if (this->mColorMap[i][j][1] != 0) // at least colored once
      {
        this->mNumberOfColoredFields++;
      }
    }
  }

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
