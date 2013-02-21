#include "player.h"
#include "computerPlayer.h"
#include "board.h"
#include "move.h"
#include "piece.h"
#include <iostream>

using namespace std;

Move *computerPlayer::getMove() {
  Piece *piece = getBoard()->getPieceToMove(getColor());
  return getBoard()->getLegalMove(piece);
};




