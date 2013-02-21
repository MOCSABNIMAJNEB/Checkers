#ifndef __COMPUTERPLAYER
#define __COMPUTERPLAYER
#include "move.h"
#include "board.h"

class computerPlayer : public Player {

 public:
  /*
   * Prompts board for the next legal move
   */
  Move *getMove();

 computerPlayer(Board *board, color c) : Player(board, c) {};

};

#endif
