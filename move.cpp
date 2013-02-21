#include <cmath>
#include "move.h"

Move::Move(int x, int y, int xDelta, int yDelta) {
  _x = x;
  _y = y;
  _xDelta = xDelta;
  _yDelta = yDelta;

  if ((fabs(_xDelta - _x) > 1) && (fabs(_yDelta - _y) > 1)) {
    _type = HOP;
  }
  else {
    _type = SKIP;
  }

			       
}


