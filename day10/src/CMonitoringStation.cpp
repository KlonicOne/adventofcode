/*
 * monitoringstation.cpp
 *
 *  Created on: 6 Jan 2020
 *      Author: nico
 */
#include <numeric>
#include <iostream>
#include <string>
#include <math.h>
#include <fstream>

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

  // debug out size
  std::cout << "x(" << X << "), y(" << Y << ")" << std::endl;

  // fit other maps to same size
  this->mAsteroidCountMap.resize(X, vector<int>(Y));
  this->mAsteroidSightMap.resize(X, vector<int>(Y));
}

void CMonitoringStation::calcCandidates(void)
{
  std::vector<int> xCounts;
  std::vector<int> yCounts;

  // Size for the x and y vectors
  xCounts.resize(this->mSizeX, 0);
  yCounts.resize(this->mSizeY, 0);

  // Calculate the x and y counts
  for (unsigned y = 0; y < mSizeY; y++)
  {
    for (unsigned x = 0; x < mSizeX; x++)
    {
      xCounts.at(y) += mAsteroidMap[y].at(x);
      yCounts.at(x) += mAsteroidMap[y].at(x);
    }
  }

  // Store to the map for candidates
  for (unsigned y = 0; y < mSizeY; y++)
  {
    for (unsigned x = 0; x < mSizeX; x++)
    {
      // Only add how many in row and column when there is a asteroid
      if (mAsteroidMap[y].at(x) != 0)
      {
        mAsteroidCountMap[y].at(x) = xCounts.at(y) + yCounts.at(x);
      }
    }
  }
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

void CMonitoringStation::plotCandidatesdMap(void)
{
  for (unsigned y = 0; y < mSizeY; y++)
  {
    for (unsigned x = 0; x < mSizeX; x++)
    {
      std::cout << this->mAsteroidCountMap[y].at(x);
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}
