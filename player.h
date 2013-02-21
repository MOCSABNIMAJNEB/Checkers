#ifndef __PLAYER
#define __PLAYER
#include "move.h"
#include "board.h"
#include "piece.h"

class Player {
 private:
  Board *_board;
  color _color;

 public:
  Player(Board *board, color color);

  /*
   * Inheritable move function
   * Implemented in humanPlayer.cpp and computerPlayer.cpp
   */
  virtual Move *getMove() { };
  color getColor() { return _color; };
  Board *getBoard() { return _board; };
};


#endif

