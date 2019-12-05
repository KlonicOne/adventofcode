/*
 * Path.cpp
 *
 *  Created on: 5 Dec 2019
 *      Author: nico
 */

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
  std::vector<std::string> retVector;

  while (getline(inputFile, pathElement))
  {
    retVector.push_back(pathElement);
  }

  return (retVector);
}

std::vector<std::tuple<int, int> > Path::getPathOfString(std::string &inputString)
{
  std::stringstream inStringStream(inputString);
  std::vector<std::tuple<int, int> > retPath;
  std::string pathElement;
  int index = 0;

  while (getline(inStringStream, pathElement, ','))
  {
    std::cout << pathElement << ", " << index << std::endl;
  }
  return (retPath);

}


