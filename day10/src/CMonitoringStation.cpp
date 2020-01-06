/*
 * monitoringstation.cpp
 *
 *  Created on: 6 Jan 2020
 *      Author: nico
 */

#include "CMonitoringStation.h"

CMonitoringStation::CMonitoringStation()
{
  this->mSizeX = 0;
  this->mSizeY = 0;
}

CMonitoringStation::~CMonitoringStation()
{
  // TODO Auto-generated destructor stub
}

void CMonitoringStation::parseMap(istream &input)
{
  unsigned X { 0 };
  unsigned Y { 0 };
  std::string asteroidMapLine;
  string isAsteroid = "#";
  string isEmpty = ".";

  while (std::getline(input, asteroidMapLine))
  {
    std::vector<int> tempMapLine;
    X = 0; // reset x size
    // loop over string
    for (char& asteroidElement : asteroidMapLine)
    {
      if (asteroidElement == '#')
      {
        tempMapLine.push_back(1);
      }
      else
      {
        tempMapLine.push_back(0);
      }
      X++;
    }
    // Add created line to the asteroid map
    this->mAsteroidMap.push_back(tempMapLine);
    tempMapLine.clear(); // clear content for new line
    Y++;
  }

  // Take over the map size
  this->mSizeX = X;
  this->mSizeY = Y;
}

void CMonitoringStation::plotAsteroidMap(void)
{
  for (unsigned y = 0; y < mSizeY; y++)
  {
    for (unsigned x = 0; x < mSizeX; x++)
    {
      std::cout << this->mAsteroidMap[y].at(x);
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}
