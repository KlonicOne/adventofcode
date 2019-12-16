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

  void parseInputMap(std::istream &input);
  void insertOrbit(std::string rootOrbitName, std::string newOrbitName);
  COrbit *searchOrbit(std::string orbitName);
  void destroyOrbitMap();

  void printOrbitInputMap();

private:
  COrbit *mRootOrbit;
  std::vector<std::tuple<std::string, std::string>> mInputMap;

  void destroyOrbitMap(COrbit *orbit);
  void insertOrbit(std::string rootOrbitName, std::string newOrbitName, COrbit* orbit);
  COrbit *searchOrbit(std::string orbitName, COrbit *orbit);

};

#endif /* CORBITMAP_H_ */
