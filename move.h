#ifndef __MOVE
#define __MOVE

enum moveType { HOP, SKIP };

class Move {
 private:
  moveType _type;
  int _y, _yDelta;
  int _x, _xDelta;

 public:
  Move(int x, int y, int xDelta, int yDelta);
  int getX() { return _x; };
  int getY() { return _y; };
  int getDx() { return _xDelta; };
  int getDy() { return _yDelta; };
  moveType getType() { return _type; };
  
};

#endif
