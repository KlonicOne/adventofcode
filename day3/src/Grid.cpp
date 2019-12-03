/*
 * Advent.cpp
 *
 */

#include <iostream>

#include "Grid.h"
#include "Grid.h"

Grid::Grid()
{
  Field tmpField;
  std::vector<Field> tmp;
  tmp.resize(GRIDSTEP, tmpField);
  mGrid.resize(GRIDSTEP, tmp);
  mGridSize.x = GRIDSTEP;
  mGridSize.y = GRIDSTEP;
  mCenterPort.x = mGridSize.x / 2;
  mCenterPort.y = mGridSize.y / 2;
}

Vector2 Grid::getCenterPort()
{
  return mCenterPort;
}

Vector2 Grid::getGridSize()
{
  return mGridSize;
}

std::vector<std::vector<Field>>& Grid::getGrid()
{
  return mGrid;
}

int Grid::walkPath(InputChain chain)
{
  std::cout << "### Walking Chain " << chain.owner << " ###\n";
  int numSteps = 0;
  Vector2 curPos = mCenterPort;
  for (Movement m : chain.movements)
  {
    std::cout << "Processing Movement: " << m.dir << " " << m.distance << " CURPOS: " << curPos.x << " " << curPos.y << "\n";
    switch (m.dir)
    {
    case UP:
      std::cout << "Resizing Grid\n";
      while (curPos.y + m.distance >= mGridSize.y)
      {
        mGridSize.y += GRIDSTEP;
        for (std::vector<Field>& row : mGrid)
        {
          Field tmp;
          for (int i = 0; i < GRIDSTEP; i++)
            row.emplace(row.end(), tmp);
        }
      }
      std::cout << "Walking Distance : " << m.distance << "\n";
      for (int i = 0; i < m.distance; i++)
      {
        curPos.y++;
        if (mGrid[curPos.x][curPos.y].owner == CENTER)
        {
          std::cout << "Crossed Center...\n";
        }
        else if (mGrid[curPos.x][curPos.y].owner != NONE && mGrid[curPos.x][curPos.y].owner != chain.owner)
        {
          mGrid[curPos.x][curPos.y].owner = OVERLAP;
        }
        else {
          mGrid[curPos.x][curPos.y].owner = chain.owner;
        }
        if (chain.owner == WIRE1 && mGrid[curPos.x][curPos.y].nWIRE1 == -1) {
          mGrid[curPos.x][curPos.y].nWIRE1 = numSteps + 1;
        }
        else if (chain.owner == WIRE2 && mGrid[curPos.x][curPos.y].nWIRE2 == -1) {
          mGrid[curPos.x][curPos.y].nWIRE2 = numSteps + 1;
        }
        numSteps++;
      }
      break;
    case DOWN:
      std::cout << "Resizing Grid\n";
      while (curPos.y - m.distance < 0)
      {
        mGridSize.y += GRIDSTEP;
        curPos.y += GRIDSTEP;
        mCenterPort.y += GRIDSTEP;
        for (std::vector<Field>& row : mGrid)
        {
          Field tmp;
          for (int i = 0; i < GRIDSTEP; i++)
            row.emplace(row.begin(), tmp);
        }
      }
      std::cout << "Walking Distance : " << m.distance << "\n";
      for (int i = 0; i < m.distance; i++)
      {
        curPos.y--;
        if (curPos == mCenterPort)
        {
          std::cout << "Crossed Center...\n";
        }
        else if (mGrid[curPos.x][curPos.y].owner != NONE && mGrid[curPos.x][curPos.y].owner != chain.owner)
        {
          mGrid[curPos.x][curPos.y].owner = OVERLAP;
        }
        else {
          mGrid[curPos.x][curPos.y].owner = chain.owner;
        }
        if (chain.owner == WIRE1 && mGrid[curPos.x][curPos.y].nWIRE1 == -1) {
          mGrid[curPos.x][curPos.y].nWIRE1 = numSteps + 1;
        }
        else if (chain.owner == WIRE2 && mGrid[curPos.x][curPos.y].nWIRE2 == -1) {
          mGrid[curPos.x][curPos.y].nWIRE2 = numSteps + 1;
        }
        numSteps++;
      }
      break;
    case LEFT:
      std::cout << "Resizing Grid\n";
      while (curPos.x - m.distance < 0)
      {
        mGridSize.x += GRIDSTEP;
        curPos.x += GRIDSTEP;
        mCenterPort.x += GRIDSTEP;
        for (int i = 0; i < GRIDSTEP; i++)
        {
          Field tmpField;
          std::vector<Field> tmp;
          tmp.resize(mGridSize.y, tmpField);
          mGrid.emplace(mGrid.begin(), tmp);
        }
      }
      std::cout << "Walking Distance : " << m.distance << "\n";
      for (int i = 0; i < m.distance; i++)
      {
        curPos.x--;
        if (curPos == mCenterPort)
        {
          std::cout << "Crossed Center...\n";
        }
        else if (mGrid[curPos.x][curPos.y].owner != NONE && mGrid[curPos.x][curPos.y].owner != chain.owner)
        {
          mGrid[curPos.x][curPos.y].owner = OVERLAP;
        }
        else {
          mGrid[curPos.x][curPos.y].owner = chain.owner;
        }
        if (chain.owner == WIRE1 && mGrid[curPos.x][curPos.y].nWIRE1 == -1) {
          mGrid[curPos.x][curPos.y].nWIRE1 = numSteps + 1;
        }
        else if (chain.owner == WIRE2 && mGrid[curPos.x][curPos.y].nWIRE2 == -1) {
          mGrid[curPos.x][curPos.y].nWIRE2 = numSteps + 1;
        }
        numSteps++;
      }
      break;
    case RIGHT:
      std::cout << "Resizing Grid\n";
      while (curPos.x + m.distance >= mGridSize.x)
      {
        mGridSize.x += GRIDSTEP;
        for (int i = 0; i < GRIDSTEP; i++)
        {
          Field tmpField;
          std::vector<Field> tmp;
          tmp.resize(mGridSize.y, tmpField);
          mGrid.emplace(mGrid.end(), tmp);
        }
      }
      std::cout << "Walking Distance : " << m.distance << "\n";
      for (int i = 0; i < m.distance; i++)
      {
        curPos.x++;
        if (curPos == mCenterPort)
        {
          std::cout << "Crossed Center...\n";
        }
        else if (mGrid[curPos.x][curPos.y].owner != NONE && mGrid[curPos.x][curPos.y].owner != chain.owner)
        {
          mGrid[curPos.x][curPos.y].owner = OVERLAP;
        }
        else {
          mGrid[curPos.x][curPos.y].owner = chain.owner;
        }
        if (chain.owner == WIRE1 && mGrid[curPos.x][curPos.y].nWIRE1 == -1) {
          mGrid[curPos.x][curPos.y].nWIRE1 = numSteps + 1;
        }
        else if (chain.owner == WIRE2 && mGrid[curPos.x][curPos.y].nWIRE2 == -1) {
          mGrid[curPos.x][curPos.y].nWIRE2 = numSteps + 1;
        }
        numSteps++;
      }
      break;
    }
  }
  return 0;
}

std::string Grid::renderAscii()
{
  std::string output;
  for (int y = mGridSize.y - 1; y > 0; y--)
  {
    for (int x = 0; x < mGridSize.x; x++)
    {
      if (mCenterPort.x == x && mCenterPort.y == y)
      {
        output.append("O");
        continue;
      }
      switch (mGrid[x][y].owner)
      {
      case NONE:
        output.append(".");
        break;
      case WIRE1:
        output.append("1");
        break;
      case WIRE2:
        output.append("2");
        break;
      case OVERLAP:
        output.append("#");
        break;
      default:
        output.append("E");
        break;
      }
    }
    output.append("\n");
  }
  return output;
}
