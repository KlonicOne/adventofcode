/*
 * Path.cpp
 *
 *  Created on: 5 Dec 2019
 *      Author: nico
 */
#include <algorithm>
#include <math.h>

#include "Path.h"

Path::Path()
{
  // TODO Auto-generated constructor stub

}

Path::~Path()
{
  // TODO Auto-generated destructor stub
}

std::vector<std::string> Path::separateWirePath(std::ifstream &inputFile)
{
  std::string pathElement;
  std::vector < std::string > retVector;

  while (getline(inputFile, pathElement))
  {
    retVector.push_back(pathElement);
  }

  return (retVector);
}

std::vector<std::tuple<int, int> > Path::getPathOfString(std::string &inputString)
{
  std::stringstream inStringStream(inputString);
  std::vector < std::tuple<int, int> > retPath;
  std::tuple<int, int> nextPos;
  std::string pathElement;
  int index = 0;

  // Start with the path on 0,0
  retPath.push_back(std::tuple<int, int>(0, 0));

  while (getline(inStringStream, pathElement, ','))
  {
    // Get next position as tuple of ints
    nextPos = this->getNextXYPosition(pathElement);

    // Extract X and Y positions
    int posX = std::get < 0 > (nextPos); // can be positive and negative
    int posY = std::get < 1 > (nextPos);

    // Get last position at end of the path vector
    int lastPosX = std::get < 0 > (*(retPath.end() - 1));
    int lastPosY = std::get < 1 > (*(retPath.end() - 1));

    // Generate path along route, first X value
    if (posX > 0) // positive X
    {
      for (index = 1; index <= posX; index++)
      {
        retPath.push_back(std::tuple<int, int>((lastPosX + index), lastPosY));
      }
    }
    else if (posX < 0)
    {
      for (index = -1; index >= posX; index--)
      {
        retPath.push_back(std::tuple<int, int>((lastPosX + index), lastPosY));
      }
    }
    else
    {
      // do nothing it's same position as previous
    }

    // Then Y value
    if (posY > 0) // positive Y
    {
      for (index = 1; index <= posY; index++)
      {
        retPath.push_back(std::tuple<int, int>(lastPosX, (lastPosY + index)));
      }
    }
    else if (posY < 0)
    {
      for (index = -1; index >= posY; index--)
      {
        retPath.push_back(std::tuple<int, int>(lastPosX, (lastPosY + index)));
      }
    }
    else
    {
      // nothing to do
    }
  }

  return (retPath);
}

std::tuple<int, int> Path::getNextXYPosition(std::string &pathElement)
{
  std::tuple<int, int> retPos(0, 0);

  // The given path is split into direction and value
  std::vector < std::string > pathElementVec = this->splitPathElement(pathElement);

  // Calculate the next position
  switch (hashcode(pathElementVec.at(0)))
  {
  case eU:
    retPos = std::make_tuple(0, stoi(pathElementVec.at(1)));
    break;
  case eD:
    retPos = std::make_tuple(0, (-1) * stoi(pathElementVec.at(1)));
    break;
  case eL:
    retPos = std::make_tuple((-1) * stoi(pathElementVec.at(1)), 0);
    break;
  case eR:
    retPos = std::make_tuple(stoi(pathElementVec.at(1)), 0);
    break;
  }

  return (retPos);
}

std::vector<std::string> Path::splitPathElement(std::string &pathElement)
{
  std::vector < std::string > retSplitStringVec;

  retSplitStringVec.push_back(this->getStringFromCharacter(pathElement.at(0)));
  retSplitStringVec.push_back(pathElement.substr(1));

  return (retSplitStringVec);
}

std::string Path::getStringFromCharacter(char singleChar)
{
  std::string s(1, singleChar);
  return s;
}

std::vector<std::tuple<int, int> > Path::getIntersections(std::vector<std::tuple<int, int> > wire1,
    std::vector<std::tuple<int, int> > wire2)
{
  std::vector < std::tuple<int, int> > intersectionsFound;

  // find matching tuple elements and add to intersections
  for (const auto &itw1 : wire1)
  {
//    std::cout << std::get<0>(itw1) << " " << std::get<1>(itw1) << std::endl;
    for (const auto &itw2 : wire2)
    {
//    	std::cout << std::get<0>(itw2) << " " << std::get<1>(itw2) << std::endl;

      // Check for matching intersections and push back if found
      if ((std::get < 0 > (itw1) == std::get < 0 > (itw2)) // Match X
      && (std::get < 1 > (itw1) == std::get < 1 > (itw2))) // Match Y
      {
        // Intersection found so pushback to intersections vector
        intersectionsFound.push_back(std::tuple<int, int>(std::get < 0 > (itw1), std::get < 1 > (itw1)));
      }
    }
  }

  return (intersectionsFound);
}

std::vector<int> Path::getManhattenDistance(std::vector<std::tuple<int, int> > intersections)
{
  std::vector<int> distances;

  // Calculate distances
  for (const auto &it : intersections)
  {
    distances.push_back((abs(std::get < 0 > (it)) + abs(std::get < 1 > (it))));
  }

  return (distances);
}

string_code Path::hashcode(std::string const &inString)
{
  if (inString == "U")
  {
    return eU;
  }
  else if (inString == "D")
  {
    return eD;
  }
  else if (inString == "L")
  {
    return eL;
  }
  else if (inString == "R")
  {
    return eR;
  }

  return (eU);
}

int Path::getShortestWireDistance(std::vector<std::tuple<int, int>> wire1, std::vector<std::tuple<int, int>> wire2,
    std::vector<std::tuple<int, int>> intersections)
{
  std::vector<int> shortestWireDistances;
  std::vector<int> shortestWire1Distances;
  std::vector<int> shortestWire2Distances;
  int distance = 0;

  // find matching tuple intersections
  for (const auto &ititns : intersections)
  {
    int xPosToFind = std::get < 0 > (ititns);
    int yPosToFind = std::get < 1 > (ititns);

    // find matching tuple elements on wire1
    distance = 0;
    for (const auto &itw1 : wire1)
    {
      // Check for matching intersections and push back if found
      if (((std::get < 0 > (itw1)) == xPosToFind) // Match X
      && ((std::get < 1 > (itw1)) == yPosToFind)) // Match Y
      {
        shortestWire1Distances.push_back(distance);
      }
      // Count up index following the path each element on wire
      distance++;
    }

    // reset index
    distance = 0;
    //    std::cout << std::get<0>(itw1) << " " << std::get<1>(itw1) << std::endl;
    for (const auto &itw2 : wire2)
    {
      // Check for matching intersections and push back if found
      if (((std::get < 0 > (itw2)) == xPosToFind) // Match X
      && ((std::get < 1 > (itw2)) == yPosToFind)) // Match Y
      {
        shortestWire2Distances.push_back(distance);
      }
      // Count up index following the path each element on wire
      distance++;
    }
  }

  for (unsigned int i = 0; i < shortestWire1Distances.size(); i++)
  {
    // Sum up each distance on wire
    shortestWire1Distances[i] = shortestWire1Distances[i] + shortestWire2Distances[i];
  }

  // Sort vector
  std::sort(shortestWire1Distances.begin(), shortestWire1Distances.end());

  return (shortestWire1Distances[1]);
}

std::vector<int> Path::sortDistanceVector(std::vector<int> distances)
{
  // Sort distances
  std::sort(distances.begin(), distances.end());
  return (distances);
}

int Path::getIndexOfDistance(std::vector<int> distances, int distanceToFindIndex)
{
  // Find distance
  std::vector<int>::iterator it = std::find(distances.begin(), distances.end(), distanceToFindIndex);
  // Extract index on iterator
  int index = std::distance(distances.begin(), it);

  return (index);
}
