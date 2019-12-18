/*
 * COrbitMap.cpp
 *
 *  Created on: 16 Dec 2019
 *      Author: nico
 */
#include <iostream>
#include <sstream>
#include <string>
#include <iterator>
#include "COrbitMap.h"

COrbitMap::COrbitMap()
{
  this->mRootOrbit = NULL;
  this->mSumOfOrbitConnections = 0;
}

COrbitMap::~COrbitMap()
{
}

COrbit::COrbit()
{
  this->mOrbitName = "";
  this->mNumOrbitConnections = 0;
}

COrbit::~COrbit()
{
}

void COrbitMap::insertOrbit(std::string rootOrbitName, std::string newOrbitName)
{
  COrbit *foundOrbitRoot = this->searchOrbit(rootOrbitName); // Get reference on root from tree
  // Check if the element is in the tree

  // If root is not in the tree create new root and add to tree with child
  if (foundOrbitRoot == NULL)
  {
    // Create new orbits, for root and for child
    COrbit *cOrbitRoot = new COrbit();
    COrbit *cOrbitChild = new COrbit();

    this->mOrbitMap.push_back(*cOrbitRoot); // New element in vector for graph
    this->mOrbitMap.back().mOrbitName = rootOrbitName; // Assign name

    // Difference to other elements we store as root
    if (!rootOrbitName.compare("COM"))
    {
      this->mRootOrbit = &(this->mOrbitMap.back()); // Get reference on new COM root element
    }

    // Now create second planet, the child orbit
    this->mOrbitMap.push_back(*cOrbitChild); // New element in vector for graph
    this->mOrbitMap.back().mOrbitName = newOrbitName; // Assign name
    // And assign parent
    this->mOrbitMap.back().mParentOrbits.push_back(cOrbitRoot);
  }
  // If root exists then add the child to the existing root element
  else
  {
    // Only new child, here the assumption we will never get in input exactly same combination
    COrbit *cOrbitChild = new COrbit();

    // Now create second planet, the child orbit
    this->mOrbitMap.push_back(*cOrbitChild); // New element in vector for graph
    this->mOrbitMap.back().mOrbitName = newOrbitName; // Assign name
    // And assign parent which is in the tree already
    this->mOrbitMap.back().mParentOrbits.push_back(foundOrbitRoot);
  }
}

COrbit* COrbitMap::searchOrbit(std::string orbitName)
{
  COrbit *foundOrbit = NULL;
  for(std::vector<COrbit>::iterator it = this->mOrbitMap.begin(); it != this->mOrbitMap.end(); it++)
  {
    if(orbitName.compare((*it).mOrbitName) == 0)
    {
      foundOrbit = &(*it);
    }
  }

  return(foundOrbit);
}

void COrbitMap::parseInputMap(std::istream &input)
{
  std::string orbitMapLine;

  while (std::getline(input, orbitMapLine))
  {
    std::stringstream linestream(orbitMapLine);
    std::string orbitMapElement;
    std::vector < std::string > vecOrbitElements(2);
    int counter = 0;

    while (std::getline(linestream, orbitMapElement, ')'))
    {
      // delete new line at the end
      eraseNewLine(orbitMapElement);
      // The take over
      vecOrbitElements[counter] = orbitMapElement;
      counter++;
    }
    // now make tuple and add to map
    this->mInputMap.push_back(std::make_tuple(vecOrbitElements[0], vecOrbitElements[1]));
    // debug
    //std::cout << vecOrbitElements[0] << ")" << vecOrbitElements[1] << std::endl;
  }
}

void COrbitMap::eraseNewLine(std::string &s)
{
  unsigned pos;

  // Windows
  if ((pos = s.find('\n')) <= s.size())
  {
    s.erase(pos);
  }
  // Linux
  if ((pos = s.find('\r')) <= s.size())
  {
    s.erase(pos);
  }
}

void COrbitMap::printOrbitInputMap(void)
{
  for (unsigned i = 0; i < this->mInputMap.size(); i++)
  {
    std::string root = std::get < 0 > (this->mInputMap[i]);
    std::string child = std::get < 1 > (this->mInputMap[i]);

    std::cout << root << ")" << child << std::endl;
  }
}

void COrbitMap::printOrbitMap(void)
{
  for (std::vector<COrbit>::iterator itRoot = this->mOrbitMap.begin(); itRoot != this->mOrbitMap.end(); itRoot++)
  {
    for (std::vector<COrbit *>::iterator itChild = itRoot->mChildOrbits.begin(); itChild != itRoot->mChildOrbits.end(); itChild++)
    {
      std::cout << itRoot->mOrbitName << ")" << &(*itChild)->mOrbitName << std::endl;
    }
  }
}

void COrbitMap::constructOrbitMap(void)
{
  // Walk through the map vector and create binary tree
  for (unsigned i = 0; i < this->mInputMap.size(); i++)
  {
    // Create Orbit search tree
    this->insertOrbit(std::get < 0 > (this->mInputMap[i]), std::get < 1 > (this->mInputMap[i]));
  }
}

void COrbitMap::calcOrbitStat(void)
{
}

int COrbitMap::getSumOfOrbitConnections() const
{
  return mSumOfOrbitConnections;
}
