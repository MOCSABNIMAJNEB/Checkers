#ifndef __HUMANPLAYER
#define __HUMANPLAYER
#include "move.h"
#include "board.h"

class humanPlayer : public Player {

 public:
  void getHelp();
  /*
   * Gets user input move, if move is illegal will return false and player will
   * be reprompted
   */
  Move *getMove();

 humanPlayer(Board *board, color c) : Player(board, c) {};
};

#endif

