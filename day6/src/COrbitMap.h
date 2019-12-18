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
  // References
  std::vector<COrbit *> mParentOrbits;
  std::vector<COrbit *> mChildOrbits;
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
  void calcOrbitStat(void);
  // Get sum of all connections
  int getSumOfOrbitConnections() const;

  void insertOrbit(std::string rootOrbitName, std::string newOrbitName);
  // Search specific element and get pointer handle
  COrbit *searchOrbit(std::string orbitName);

  // Debuggin functions
  void printOrbitInputMap();


private:
  COrbit *mRootOrbit; // Used as anchor for COM
  std::vector<COrbit> mOrbitMap; // Vector with all orbits
  std::vector<std::tuple<std::string, std::string>> mInputMap;
  int mSumOfOrbitConnections;

  void eraseNewLine(std::string &s);

};

#endif /* CORBITMAP_H_ */
