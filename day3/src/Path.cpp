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
//    std::cout << pathElement << ", " << index << std::endl;
    this->getNextXYPosition(pathElement);
  }

  return (retPath);
}

std::tuple<int, int> Path::getNextXYPosition(std::string &pathElement)
{
  std::tuple<int, int> retPos(0, 0);
  std::string commandLetter;
  std::string stepValue;

  std::vector<std::string> elvec = this->splitPathElement(pathElement);

  return (retPos);
}

std::vector<std::string> Path::splitPathElement(std::string &pathElement)
{
  std::vector<std::string> retSplitStringVec;

  retSplitStringVec.push_back(this->getStringFromCharacter(pathElement.at(0)));
  retSplitStringVec.push_back(pathElement.substr(1));

  return (retSplitStringVec);
}

std::string Path::getStringFromCharacter(char singleChar)
{
  std::string s(1, singleChar);
  return s;
}
