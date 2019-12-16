/*
 * COrbitMap.h
 *
 *  Created on: 16 Dec 2019
 *      Author: nico
 */

#ifndef CORBITMAP_H_
#define CORBITMAP_H_

#include <string>
#include <tuple>
#include <vector>
#include <fstream>
#include <istream>

class COrbit
{
public:
  COrbit();
  virtual ~COrbit();

  std::string mOrbitName;
  COrbit *mLeftOrbit;
  COrbit *mRightOrbit;
};

class COrbitMap
{
public:
  COrbitMap();
  virtual ~COrbitMap();

  // Read input file and store the map intern as vector
  void parseInputMap(std::istream &input);
  // Create the tree
  void constructOrbitMap(void);

  // For individual access on Orbit Map
  // Add element
  void insertOrbit(std::string rootOrbitName, std::string newOrbitName);
  // Search specific element and get pointer handle
  COrbit *searchOrbit(std::string orbitName);
  // Delete map, automatically done in destructor
  void destroyOrbitMap();

  // Debuggin functions
  void printOrbitInputMap();

private:
  COrbit *mRootOrbit;
  std::vector<std::tuple<std::string, std::string>> mInputMap;

  void destroyOrbitMap(COrbit *orbit);
  void insertOrbit(std::string rootOrbitName, std::string newOrbitName, COrbit* orbit);
  COrbit *searchOrbit(std::string orbitName, COrbit *orbit);

};

#endif /* CORBITMAP_H_ */
