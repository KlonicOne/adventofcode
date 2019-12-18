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
  if ((this->mRootOrbit == NULL) && !(rootOrbitName.compare("COM")))
  {
    // This is our root element
    COrbit cOrbitParent;
    this->mOrbitMap.emplace_back(cOrbitParent); // New element in vector for graph
    this->mOrbitMap.back().mOrbitName = rootOrbitName; // Assign name
    // Difference to other elements we store as root
    this->mRootOrbit = &(this->mOrbitMap.back()); // Get reference on new COM root element

    // Now create second planet
    COrbit cOrbitChild;
    this->mOrbitMap.emplace_back(cOrbitChild); // New element in vector for graph
    this->mOrbitMap.back().mOrbitName = newOrbitName; // Assign name
    // And assign parent
    this->mOrbitMap.back().mParentOrbits.emplace_back(this->searchOrbit(rootOrbitName));
  }
  else
  {

  }
}

COrbit* COrbitMap::searchOrbit(std::string orbitName)
{
  COrbit *foundOrbit;
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
