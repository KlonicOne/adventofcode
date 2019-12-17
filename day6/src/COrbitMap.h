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
  int mNumOrbitConnections;
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
  // Get max orbit depth
  int maxOrbitMapDepth(void);
  // Get sum of all connections
  int getSumOfOrbitConnections() const;

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
  int mSumOfOrbitConnections;

  void destroyOrbitMap(COrbit *orbit);
  void insertOrbit(std::string rootOrbitName, std::string newOrbitName, COrbit* orbit);
  COrbit *searchOrbit(std::string orbitName, COrbit *orbit);
  int maxOrbitMapDepth(COrbit* orbit);
  void eraseNewLine(std::string &s);

};

#endif /* CORBITMAP_H_ */
