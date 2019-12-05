/*
 * Path.h
 *
 *  Created on: 5 Dec 2019
 *      Author: nico
 */

#ifndef PATH_H_
#define PATH_H_

#include <vector>
#include <cstring>
#include <fstream>
#include <iostream>
#include <tuple>
#include <sstream>

enum string_code {
    eU,
    eD,
    eL,
    eR,
};

class Path
{
public:
  Path();
  virtual ~Path();

  std::vector<std::string> separateWirePath(std::ifstream &inputFile);
  std::vector<std::tuple<int, int>> getPathOfString(std::string &inputString);
  std::vector<std::tuple<int, int>> getIntersections(std::vector<std::tuple<int, int>> wire1, std::vector<std::tuple<int, int>> wire2);

private:
  std::tuple<int, int> getNextXYPosition(std::string &pathElement);
  std::vector<std::string> splitPathElement(std::string &pathElement);
  std::string getStringFromCharacter(char singleChar);
  string_code hashcode (std::string const& inString);
};

#endif /* PATH_H_ */
