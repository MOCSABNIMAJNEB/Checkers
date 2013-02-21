#ifndef __PIECE
#define __PIECE
#include <string>
#include "move.h"

enum color { RED, BLACK };
enum type { PIECE, KING };

class Piece {
 private:
  color _color;
  type _type;
  int _x, _y;
  
 public:
  Piece(); 
  Piece(color c, int x, int y);
  Piece(color c, int x, int y, type t);
  color getColor() { return _color; }; 
  type getType() { return _type; };
  void setType(type t) { _type = t; };
  std::string toString();
  void setX(int x) { _x = x; };
  void setY(int y) { _y = y; };
  int getX() { return _x; };
  int getY() { return _y; };

  /*
   * Checks whether a player with this color
   * can take this move
   */
  bool canTake(color c, Move *m);
    
};
#endif
