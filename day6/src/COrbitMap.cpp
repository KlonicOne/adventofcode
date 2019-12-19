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
  COrbit *foundOrbitChild = this->searchOrbit(newOrbitName); // Get reference on child from tree

  // Both elements are existing, so only new connections
  if ((foundOrbitRoot != 0) && (foundOrbitChild != NULL))
  {
    foundOrbitRoot->mChildOrbits.push_back(foundOrbitChild); // Child on root
    foundOrbitChild->mParentOrbits.push_back(foundOrbitRoot); // Root on child
  }
  // Root not in tree but child
  else if ((foundOrbitRoot == NULL) && (foundOrbitChild != NULL))
  {
    COrbit *cOrbitRoot = new COrbit(); // New root element

    // Root creation
    this->mOrbitMap.push_back(cOrbitRoot); // New element in vector for graph
    cOrbitRoot->mOrbitName = rootOrbitName; // Assign name
    cOrbitRoot->mChildOrbits.push_back(foundOrbitChild); // Child connection
    foundOrbitChild->mParentOrbits.push_back(cOrbitRoot); // Root on found child

    // Special treatment of COM  we store as root reference
    if (!rootOrbitName.compare("COM"))
    {
      this->mRootOrbit = cOrbitRoot; // Get reference on new COM root element
    }
  }
  // Root in tree but new child
  else if ((foundOrbitRoot != NULL) && (foundOrbitChild == NULL))
  {
    COrbit *cOrbitChild = new COrbit(); // New child element

    // Child creation
    this->mOrbitMap.push_back(cOrbitChild); // New element in vector for graph
    cOrbitChild->mOrbitName = newOrbitName; // Assign name
    cOrbitChild->mParentOrbits.push_back(foundOrbitRoot); // Parent connection
    foundOrbitRoot->mChildOrbits.push_back(cOrbitChild); // Root on found child
  }
  // Nothing there all new
  else
  {
    COrbit *cOrbitRoot = new COrbit(); // New root element
    COrbit *cOrbitChild = new COrbit(); // New child element

    // Root creation
    this->mOrbitMap.push_back(cOrbitRoot); // New element in vector for graph
    cOrbitRoot->mOrbitName = rootOrbitName; // Assign name
    cOrbitRoot->mChildOrbits.push_back(cOrbitChild); // Child connection

    // Special treatment of COM  we store as root reference
    if (!rootOrbitName.compare("COM"))
    {
      this->mRootOrbit = cOrbitRoot; // Get reference on new COM root element
    }

    // Child creation
    this->mOrbitMap.push_back(cOrbitChild); // New element in vector for graph
    cOrbitChild->mOrbitName = newOrbitName; // Assign name
    cOrbitChild->mParentOrbits.push_back(cOrbitRoot); // Root on found child
  }

  // debug out
//  std::cout << rootOrbitName << ")" << newOrbitName << std::endl;
//  printOrbitMap();
//  std::cout << std::endl;
}

COrbit* COrbitMap::searchOrbit(std::string orbitName)
{
  COrbit *foundOrbit = NULL;
  for (std::vector<COrbit*>::iterator it = this->mOrbitMap.begin(); it != this->mOrbitMap.end(); it++)
  {
    if (orbitName.compare((*it)->mOrbitName) == 0)
    {
      foundOrbit = *it;
    }
  }

  return (foundOrbit);
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
  std::vector<COrbit*>::iterator itRoot; // iterator
  for (itRoot = this->mOrbitMap.begin(); itRoot != this->mOrbitMap.end(); itRoot++)
  {
    std::cout << "Root: " << (*itRoot)->mOrbitName;
    std::cout << ", connections: " << (*itRoot)->mNumOrbitConnections;
    std::cout << ", parent size: " << (*itRoot)->mParentOrbits.size();
    std::cout << ", child size: " << (*itRoot)->mChildOrbits.size() << ", childs: ";

    for (std::vector<COrbit*>::iterator itChild = (*itRoot)->mChildOrbits.begin(); itChild != (*itRoot)->mChildOrbits.end();
        itChild++)
    {
      std::cout << (*itChild)->mOrbitName << ", ";
    }

    std::cout << std::endl;
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
  this->maxOrbitMapDepth(this->mRootOrbit, 0);
}

void COrbitMap::maxOrbitMapDepth(COrbit *orbit, int currentDepth)
{
  int depthOrbit = 0;

  if (orbit == NULL)
  {
    // No additional depth to add
    depthOrbit = currentDepth;
  }
  else
  {
    // Store own orbit value
    orbit->mNumOrbitConnections = currentDepth;
    // Increase depth for next layer
    depthOrbit = currentDepth + 1;
    // Get each child tree
    std::vector<COrbit*>::iterator itChild; // iterator
    for (itChild = orbit->mChildOrbits.begin(); itChild != orbit->mChildOrbits.end(); itChild++)
    {
      maxOrbitMapDepth(*itChild, depthOrbit);
    }

    //std::cout << orbit->mOrbitName << ": " << orbit->mNumOrbitConnections << std::endl;
    // Overall sum
    this->mSumOfOrbitConnections += currentDepth;
  }
}

int COrbitMap::getSumOfOrbitConnections() const
{
  return mSumOfOrbitConnections;
}
