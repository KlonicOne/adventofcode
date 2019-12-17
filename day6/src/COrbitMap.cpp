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
  this->destroyOrbitMap();
}

COrbit::COrbit()
{
  this->mOrbitName = "";
  this->mNumOrbitConnections = 0;
  this->mLeftOrbit = NULL;
  this->mRightOrbit = NULL;
}

COrbit::~COrbit()
{
}

void COrbitMap::insertOrbit(std::string rootOrbitName, std::string newOrbitName)
{
  if (this->mRootOrbit == NULL)
  {
    this->mRootOrbit = new COrbit;
    this->mRootOrbit->mOrbitName = rootOrbitName;
    this->mRootOrbit->mLeftOrbit = NULL;
    this->mRootOrbit->mRightOrbit = NULL;
    // On root we can already assign next tree
    this->insertOrbit(rootOrbitName, newOrbitName, this->mRootOrbit);
  }
  else
  {
    this->insertOrbit(rootOrbitName, newOrbitName, this->mRootOrbit);
  }
}

COrbit* COrbitMap::searchOrbit(std::string orbitName)
{
  return (this->searchOrbit(orbitName, this->mRootOrbit));
}

void COrbitMap::destroyOrbitMap()
{
}

void COrbitMap::destroyOrbitMap(COrbit *orbit)
{
  if (orbit != NULL)
  {
    this->destroyOrbitMap(orbit->mLeftOrbit);
    this->destroyOrbitMap(orbit->mRightOrbit);
    delete orbit;
  }
}

void COrbitMap::insertOrbit(std::string rootOrbitName, std::string newOrbitName, COrbit *orbit)
{
  // Extract locals to better debug
  std::string currentOrbitName = orbit->mOrbitName;
  int orbitCompare = rootOrbitName.compare(currentOrbitName);

  // debug out
  std::cout << "Check: " << rootOrbitName << ")" << newOrbitName << " on " << currentOrbitName << std::endl;

  // Check if root orbit found
  if (orbitCompare == 0)
  {
    // left branch of the given orbit is not assigned
    if (orbit->mLeftOrbit == NULL)
    {
      // Check if same given orbit could be already on right orbit branch
      if (orbit->mRightOrbit != NULL) // First check if it is unequal NULL ptr
      {
        if (orbit->mRightOrbit->mOrbitName != newOrbitName) // check now if it is the one
        {
          // The given branch is not the one on right so we can assign it
          orbit->mLeftOrbit = new COrbit; // Create orbit
          orbit->mLeftOrbit->mOrbitName = newOrbitName;
          orbit->mLeftOrbit->mLeftOrbit = NULL;
          orbit->mLeftOrbit->mRightOrbit = NULL;

          // debug out
          std::cout << "L: Added: " << rootOrbitName << ") " << newOrbitName << std::endl;
        }
      }
      else // The other branch is NULL so we can assign it
      {
        orbit->mLeftOrbit = new COrbit; // Create orbit
        orbit->mLeftOrbit->mOrbitName = newOrbitName;
        orbit->mLeftOrbit->mLeftOrbit = NULL;
        orbit->mLeftOrbit->mRightOrbit = NULL;

        // debug out
        std::cout << "L: Added: " << rootOrbitName << ") " << newOrbitName << std::endl;
      }
    }
    else if (orbit->mRightOrbit == NULL) // free branch so allocate
    {
      // Check if same given orbit could be already on left orbit branch
      if (orbit->mLeftOrbit != NULL) // First check if it is unequal NULL ptr
      {
        if (orbit->mLeftOrbit->mOrbitName != newOrbitName) // check now if it is the one
        {
          // The given branch is not the one on left so we can assign it
          orbit->mRightOrbit = new COrbit; // Create orbit
          orbit->mRightOrbit->mOrbitName = newOrbitName;
          orbit->mRightOrbit->mLeftOrbit = NULL;
          orbit->mRightOrbit->mRightOrbit = NULL;

          // debug out
          std::cout << "R: Added: " << rootOrbitName << ") " << newOrbitName << std::endl;
        }
      }
      else // The other branch is NULL so we can assign it
      {
        orbit->mRightOrbit = new COrbit; // Create orbit
        orbit->mRightOrbit->mOrbitName = newOrbitName;
        orbit->mRightOrbit->mLeftOrbit = NULL;
        orbit->mRightOrbit->mRightOrbit = NULL;

        // debug out
        std::cout << "R: Added: " << rootOrbitName << ") " << newOrbitName << std::endl;
      }
    }
    else
    {
      // Here the given orbit is already assigned
      // nothing to be done
      std::cout << "Orbits assigned already!" << std::endl;
    }
  }
  else
  {
    // Here current root node didn't match, so only continue if the branches are assigned
    if (orbit->mLeftOrbit != NULL)
    {
      // First go through left branch then through right
      this->insertOrbit(rootOrbitName, newOrbitName, orbit->mLeftOrbit);
    }
    // Both ways to be followed when branch assigned
    if (orbit->mRightOrbit != NULL)
    {
      this->insertOrbit(rootOrbitName, newOrbitName, orbit->mRightOrbit);
    }
  }
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
  for (unsigned j = 0; j < this->mInputMap.size(); j++)
  {
    for (unsigned i = 0; i < this->mInputMap.size(); i++)
    {
      // Create Orbit search tree
      this->insertOrbit(std::get < 0 > (this->mInputMap[i]), std::get < 1 > (this->mInputMap[i]));
    }
  }
}

COrbit* COrbitMap::searchOrbit(std::string orbitName, COrbit *orbit)
{
  return (NULL);
}

int COrbitMap::maxOrbitMapDepth(void)
{
  return (this->maxOrbitMapDepth(this->mRootOrbit));
}

int COrbitMap::maxOrbitMapDepth(COrbit *orbit)
{
  int depthOrbit;

  if (orbit == NULL)
  {
    depthOrbit = 0;
  }
  else
  {
    /* compute the depth of each subtree */
    int lDepth = maxOrbitMapDepth(orbit->mLeftOrbit);
    int rDepth = maxOrbitMapDepth(orbit->mRightOrbit);

    /* use the larger one */
    if (lDepth > rDepth)
    {
      depthOrbit = lDepth + 1;
    }
    else
    {
      depthOrbit = rDepth + 1;
    }

    // Store own orbit value
    orbit->mNumOrbitConnections = depthOrbit;
  }

//std::cout << orbit->mOrbitName << ": " << depthOrbit << std::endl;
// Overall sum
  this->mSumOfOrbitConnections += depthOrbit;

  return (depthOrbit);
}

int COrbitMap::getSumOfOrbitConnections() const
{
  return mSumOfOrbitConnections;
}
