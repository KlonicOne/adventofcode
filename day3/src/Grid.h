/*
 * Advent.h
 *
 */

#ifndef GRID_H_
#define GRID_H_

#include <list>
#include <vector>
#include <string>

using namespace std;


#define GRIDSTEP 10

enum Direction {
  UP,
  DOWN,
  LEFT,
  RIGHT
};

struct Movement {
  Direction dir;
  int distance;
};

enum Owner {
  NONE,
  CENTER,
  WIRE1,
  WIRE2,
  OVERLAP
};

struct InputChain {
  Owner owner;
  std::vector<Movement> movements;
};

struct Vector2 {
  int x;
  int y;
  bool operator==(const Vector2& rhs)
  {
    return x == rhs.x && y == rhs.y;
  }
};

struct Field {
  Owner owner = NONE;
  int nWIRE1 = -1;
  int nWIRE2 = -1;
};

/*
A dynamically resizing Grid.
Anytime we would have a negative index we emplace GRIDSTEP items to vector and shift center + current position indices to suplement the new range.
Anytime we would have a index outside of the range we simply add GRIDSTEP amount of items to the end of the vectors (No shifting needed).
Is slow atm because of slow emplace in vectors, also uses tons of ram (~3.0GB with my input).
*/
class Grid {
public:
  Grid();
  int walkPath(InputChain chain);

  std::vector<std::vector<Field>>& getGrid();
  Vector2 getCenterPort();
  Vector2 getGridSize();
  std::string renderAscii();
private:
  std::vector<std::vector<Field>> mGrid;
  Vector2 mGridSize;
  Vector2 mCenterPort;
};

#endif /* GRID_H_ */
