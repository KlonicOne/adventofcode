/*
 * COrbitMap.cpp
 *
 *  Created on: 16 Dec 2019
 *      Author: nico
 */
#include <iostream>
#include <sstream>
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

void COrbitMap::destroyOrbitMap(COrbit* orbit)
{
  if (orbit != NULL)
  {
    this->destroyOrbitMap(orbit->mLeftOrbit);
    this->destroyOrbitMap(orbit->mRightOrbit);
    delete orbit;
  }
}

void COrbitMap::insertOrbit(std::string rootOrbitName, std::string newOrbitName, COrbit* orbit)
{
  // Check if root orbit found
  if (!(rootOrbitName.compare(orbit->mOrbitName)))
  {
    if (orbit->mLeftOrbit == NULL) // free branch so allocate
    {
      orbit->mLeftOrbit = new COrbit; // Create orbit
      orbit->mLeftOrbit->mOrbitName = newOrbitName;
      orbit->mLeftOrbit->mLeftOrbit = NULL;
      orbit->mLeftOrbit->mRightOrbit = NULL;
    }
    else if (orbit->mRightOrbit == NULL) // free branch so allocate
    {
      orbit->mRightOrbit = new COrbit; // Create orbit
      orbit->mRightOrbit->mOrbitName = newOrbitName;
      orbit->mRightOrbit->mLeftOrbit = NULL;
      orbit->mRightOrbit->mRightOrbit = NULL;
    }
    else
    {
      std::cout << "Error orbit found but not empty nodes! " << rootOrbitName << std::endl;
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
    if (orbit->mRightOrbit != NULL)
    {
      this->insertOrbit(rootOrbitName, newOrbitName, orbit->mRightOrbit);
    }
  }
}

void COrbitMap::parseInputMap(std::istream& input)
{
  std::string orbitMapLine;

  while (std::getline(input, orbitMapLine))
  {
    std::stringstream linestream(orbitMapLine);
    std::string orbitMapElement;
    std::vector<std::string> vecOrbitElements(2);
    int counter = 0;

    while (std::getline(linestream, orbitMapElement, ')'))
    {
      vecOrbitElements[counter] = orbitMapElement;
      counter++;
    }
    // now make tuple and add to map
    this->mInputMap.push_back(std::make_tuple(vecOrbitElements[0], vecOrbitElements[1]));
    //std::cout << vecOrbitElements[0] << ")" << vecOrbitElements[1] << std::endl;
  }
}

void COrbitMap::printOrbitInputMap(void)
{
  for (unsigned i = 0; i < this->mInputMap.size(); i++)
  {
    std::string root = std::get<0>(this->mInputMap[i]);
    std::string child = std::get<1>(this->mInputMap[i]);

    std::cout << root << ")" << child << std::endl;
  }
}

void COrbitMap::constructOrbitMap(void)
{
  // Walk through the map vector and create binary tree
  for (unsigned i = 0; i < this->mInputMap.size(); i++)
  {
    // Create Orbit search tree
    this->insertOrbit(std::get<0>(this->mInputMap[i]), std::get<1>(this->mInputMap[i]));
  }
}

COrbit* COrbitMap::searchOrbit(std::string orbitName, COrbit* orbit)
{
  return (NULL);
}

int COrbitMap::maxOrbitMapDepth(void)
{
  return (this->maxOrbitMapDepth(this->mRootOrbit));
}

int COrbitMap::maxOrbitMapDepth(COrbit* orbit)
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
