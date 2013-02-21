#include <string>
#include <iostream>
#include <sstream>
#include <cmath>
#include "piece.h"
#include "move.h"
#include "board.h"

using namespace std;

Piece::Piece() {
}

Piece::Piece(color color, int x, int y) {
  _color = color;
  _type = PIECE;
  _x = x;
  _y = y;
}

Piece::Piece(color color, int x, int y, type t) {
  _color = color;
  _type = t;
  _x = x;
  _y = y;
}

bool Piece::canTake(color c, Move *m) {
  int dist;
  if (m->getType() == SKIP) {
    dist = 1;
  } else  {
    dist = 2;
  }

  if (_color != c) {
    cout << "Cannot move opponents piece!\n";
    return false;
  }

  if (fabs(m->getX() - m->getDx()) != dist) {
    cout << "Cannot move that far over\n";
    return false;
  }
  if (fabs(m->getY() - m->getDy()) != dist) {
    cout << "Cannot move that far ahead\n";
    return false;
  }

  if (_type == PIECE) {
    if (_color == BLACK && m->getY() - m->getDy() < 0) {
      cout << "This piece cannot move in that direction\n";
      return false;
    }

    if (_color == RED && m->getY() - m->getDy() > 0) {
      cout << "This piece cannot move in that direction\n";
      return false;
    }
  }

  return true;
}


string Piece::toString() {
  stringstream output;

  if (getColor() == RED) {
    if (getType() == PIECE)
      output << "R";
    else
      output << "K";
  }
  else if (getColor() == BLACK) {
    if (getType() == PIECE)
      output << "b";
    else
      output << "k";
    
  }
  return output.str();
}




