#include <string>
#include <sstream>
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <fcntl.h>
#include <vector>
#include "board.h"
#include "move.h"
#include "piece.h"

using namespace std;

Board::Board() {
}

Board::Board(bool isNew) {
  if (isNew) {
    _turn = BLACK;
    _redPieces = 12;
    _blackPieces = 12;


    board[0][1] = new Piece(RED, 1, 0);
    board[0][3] = new Piece(RED, 3, 0);
    board[0][5] = new Piece(RED, 5, 0);
    board[0][7] = new Piece(RED, 7, 0);

    board[1][0] = new Piece(RED, 0, 1);
    board[1][2] = new Piece(RED, 2, 1);
    board[1][4] = new Piece(RED, 4, 1);
    board[1][6] = new Piece(RED, 6, 1);

    board[2][1] = new Piece(RED, 1, 2);
    board[2][3] = new Piece(RED, 3, 2);
    board[2][5] = new Piece(RED, 5, 2);
    board[2][7] = new Piece(RED, 7, 2);

    board[5][0] = new Piece(BLACK, 0, 5);
    board[5][2] = new Piece(BLACK, 2, 5);
    board[5][4] = new Piece(BLACK, 4, 5);
    board[5][6] = new Piece(BLACK, 6, 5);

    board[6][1] = new Piece(BLACK, 1, 6);
    board[6][3] = new Piece(BLACK, 3, 6);
    board[6][5] = new Piece(BLACK, 5, 6);
    board[6][7] = new Piece(BLACK, 7, 6);

    board[7][0] = new Piece(BLACK, 0, 7);
    board[7][2] = new Piece(BLACK, 2, 7);
    board[7][4] = new Piece(BLACK, 4, 7);
    board[7][6] = new Piece(BLACK, 6, 7);
  }
};


void Board::placePiece(Piece *p) {
  if (p->getColor() == BLACK) {
    _blackPieces++;
  } else {
    _redPieces++;
 }
  board[p->getY()][p->getX()] = p;
};



void Board::clear() {
  int i, j;
  for (i=0; i<7; i++) {
    for (j=0; j<7; j++) {
      delete board[i][j];
    }
  }

}

void Board::save() {
  int i, j, bwrite, out;
  color turnTemp = _turn;
  Piece piece;
  out = open("save.data", O_RDWR | O_CREAT | O_TRUNC, 0644);
  bwrite = write(out, &turnTemp, sizeof(color));

  for (i=0; i<8; i++) {
    for (j=0; j<8; j++) {
      if (!(board[i][j] == NULL)) {
	//cout << board[i][j]->getColor() << " piece at "  <<board[i][j]->getY() << ", " << board[i][j]->getX() << " written\n";
	piece = *board[i][j];
	bwrite = write(out, &piece, sizeof(Piece));
      }
    }
  }

  cout << "Board Saved!";
}

Piece *Board::getPieceToMove(color c) {
  vector <Piece*> pieces, skippable, hoppable;
  int i,j,index;


  for (i=0; i<8; i++) {
    for (j=0; j<8; j++) {
      if (board[i][j] != NULL) {
	if (board[i][j]->getColor() == c) {
	  pieces.push_back(board[i][j]);
	}
      }
    }
  }
  
  for (i=0; i<pieces.size(); i++) {
    if (hasHop(pieces.at(i))) {
      hoppable.push_back(pieces.at(i));
    }
    if (hasSkip(pieces.at(i))) {
      skippable.push_back(pieces.at(i));
    }
  }

  for (i=0; i<hoppable.size(); i++) {
    Piece *hopper = hoppable.at(i);
  }

  if (hoppable.size() > 0) {
    if (c == BLACK) {
      _blackHasHop = true;
    } else {
      _redHasHop = true;
    }
    index = rand() % hoppable.size();
    return hoppable.at(index);
  } else if (skippable.size() > 0) {
    if (c == BLACK) {
      _blackHasHop = false;
    } else {
      _redHasHop = false;
    }
    index = rand() % skippable.size();
    return skippable.at(index);
  }

  return NULL;
};


Move *Board::getLegalMove(Piece *p) {
  if (p == NULL)
    return NULL;

  if (hasHop(p)) {
    return getHop(p);
  }

  if (hasSkip(p)) {
    return getSkip(p);
  }

  return NULL;
}


bool Board::isOver() {
  // One player is out of pieces
  if (_blackPieces == 0 || _redPieces == 0)
    return true;

  if (getPieceToMove(RED) == NULL || getPieceToMove(BLACK) == NULL)
    return true;

  return false;
};

bool Board::colorHasHop(color c) {
  if (c == BLACK && _blackHasHop)
    return true;
  else if (c == RED && _redHasHop)
    return true;
  
  return false;
}

bool Board::move(color c, Move *m) {
  if (m == NULL) {
    cout << "Error; invalid move\n";
    return false;
  }

  Piece *source;
  if (board[m->getY()][m->getX()] != NULL) {
    source = board[m->getY()][m->getX()];
  }
  else {
    cout << "Illegal Move!\n";
    return false;
  };

  if (m->getType()==SKIP && colorHasHop(c)) {
    Piece *legalPiece = getPieceToMove(c);
    Move *legalMove = getLegalMove(legalPiece);
    cout << "You must take your jump at row " << legalMove->getY() << ", column " << legalMove->getX() << endl;
    return false;
  }


  if (isLegal(m) && source->canTake(c, m)) {
    board[m->getDy()][m->getDx()] = source;
    board[m->getY()][m->getX()] = NULL;

    source->setX(m->getDx());
    source->setY(m->getDy());

    if (source->getColor()==BLACK) {
      if (m->getDy()==0) {
	source->setType(KING);
      }	
    } else {
      if (m->getDy()==7) {
	source->setType(KING);
      }	
    }

    if (m->getType() == HOP) {
      if (board[((m->getY() + m->getDy())/2)][((m->getX() + m->getDx())/2)]->getColor()==RED) {
	_redPieces--;
      }
      else {
	_blackPieces--;
      }

      delete board[((m->getY() + m->getDy())/2)][((m->getX() + m->getDx())/2)];
      board[((m->getY() + m->getDy())/2)][((m->getX() + m->getDx())/2)] = NULL;
    }
    
    if (m->getType()==HOP && hasHop(source)) {
      Move *nextHop = getHop(source);
      move(source->getColor(), nextHop);
      delete nextHop;
    }
    if (c == BLACK) {
      _turn = RED;
    } else {
      _turn = BLACK;
    }

    return true;
  }

  return false;
};

bool Board::isLegal(Move *m) {
  if ((m->getX()<0) || (m->getX()>8) || (m->getY()<0) || (m->getY()>8)) {
    cout << "Illegal Move! (Out of Bounds)\n";
    return false;
  } else if ((m->getDx()<0) || (m->getDx()>8) || (m->getDy()<0) || (m->getDy()>8)) {
    cout << "Illegal Move! (Out of Bounds)\n";
    return false;
  }

  if (board[m->getDy()][m->getDx()] != NULL) {
    cout << "Illegal Move! (Destination not empty)\n";
    return false;
  }
  else if (board[m->getY()][m->getX()] == NULL) {
    cout << "Illegal Move! (Source empty)\n\n";
    return false;
  }

  return true;
};

string Board::toString() {
  int i, j;
  stringstream output; 
  output << "   _A___B___C___D___E___F___G___H_\n";
  output <<  "  |   |   |   |   |   |   |   |   |\n";
  for (i=0; i<8; i++) {
    for (j=0; j<8; j++) {
      if (j==0) {
	output << i;
      }

      output << " | ";

 
      if (board[i][j] != NULL) {
	output << board[i][j]->toString();
      }
      else {
	output << " ";
      }
    }
    output << " |\n";
  }
  output <<  "  |___|___|___|___|___|___|___|___|\n";
  return output.str();
}

bool Board::hasSkip(Piece *piece) {
  int dir;

  if (piece->getColor() == BLACK)
    dir = -1;
  else
    dir = 1;

  
  if (piece->getType() == PIECE) {
    if (piece->getY()+dir>=0 && piece->getY()+dir<8) {
      if (piece->getX()+1<8) {
	if (board[piece->getY()+dir][piece->getX()+1] == NULL) {
	  return true;
	} 
      }
      if (piece->getX()-1>=0) {
	if (board[piece->getY()+dir][piece->getX()-1] == NULL) {
	  return true;
	} 
	
      }
    }

  } else {
    if (piece->getY()+1<8) {
      if (piece->getX()+1<8) {
	if (board[piece->getY()+1][piece->getX()+1] == NULL) {
	  return true;
	}
      }
      if (piece->getX()-1>=0) {
	if (board[piece->getY()+1][piece->getX()-1] == NULL) {
	  return true;
	} 
      }
    }
    if (piece->getY()-1>=0) {
      if (piece->getX()+1<8) {
	if (board[piece->getY()-1][piece->getX()+1] == NULL) {
	  return true;
	}
      }
      if (piece->getX()-1>=0) {
	if (board[piece->getY()-1][piece->getX()-1] == NULL) {
	  return true;
	}
      }
    }
  }
  return false;
}

bool Board::hasHop(Piece *piece) {
  int dir, xdir;

  if (piece->getColor() == BLACK) {
    dir = -2;
    xdir = -1;
  }
  else {
    dir = 2;
    xdir = 1;
  }

  
  if (piece->getType() == PIECE) {
    if (piece->getY()+dir>=0 && piece->getY()+dir<8) {
      if (piece->getX()+2<8) {
 	if (board[piece->getY()+dir][piece->getX()+2] == NULL) {
	  if (board[piece->getY()+xdir][piece->getX()+1] != NULL) {
	    if (board[piece->getY()+xdir][piece->getX()+1]->getColor() != piece->getColor()) {
	      
	      return true;
	    }
	  }
	}
      } else if (piece->getX()-2>=0) {
	if (board[piece->getY()+dir][piece->getX()-2] == NULL) {
	  if (board[piece->getY()+xdir][piece->getX()-1] != NULL) {
	    if (board[piece->getY()+xdir][piece->getX()-1]->getColor() != piece->getColor()) {
	      return true;
	    }
	  }
	} 
      }
    }
  

  } else {
    if (piece->getY()+2<8) {
      if (piece->getX()+2<8) {
	if (board[piece->getY()+2][piece->getX()+2] == NULL) {
	  if (board[piece->getY()+1][piece->getX()+1] != NULL) {
	    if (board[piece->getY()+1][piece->getX()+1]->getColor() != piece->getColor()) {
	      return true;
	    }
	  }
	}
      }
      if (piece->getX()-2>=0) {
	if (board[piece->getY()+2][piece->getX()-2] == NULL) {
	  if (board[piece->getY()+1][piece->getX()-1] != NULL) {
	    if (board[piece->getY()+1][piece->getX()-1]->getColor() != piece->getColor()) {
	      return true;
	    }
	  }
	}
      }
    }
    if (piece->getY()-2>=0) {
      if (piece->getX()+2<8) {
	if (board[piece->getY()-2][piece->getX()+2] == NULL) {
	  if (board[piece->getY()-1][piece->getX()+1] != NULL) {
	    if (board[piece->getY()-1][piece->getX()+1]->getColor() != piece->getColor()) {
	      return true;
	    }
	  }
	}
      }
      if (piece->getX()-2>=0) {
	if (board[piece->getY()-2][piece->getX()-2] == NULL) {
	  if (board[piece->getY()-1][piece->getX()-1] != NULL) {
	    if (board[piece->getY()-1][piece->getX()-1]->getColor() != piece->getColor()) {
	      return true;
	    }
	  }
	}
      }
    }
  }
  return false;
}

Move *Board::getSkip(Piece *piece) {
  int dir, index, i;
  vector <Move*> moves;  
  srand( time(NULL) );

  if (piece->getColor() == BLACK)
    dir = -1;
  else
    dir = 1;

 if (piece->getType() == PIECE) {
    if (piece->getY()+dir>=0 && piece->getY()+dir<8) {
      if (piece->getX()+1<8) {
	if (board[piece->getY()+dir][piece->getX()+1] == NULL) {
 	  moves.push_back(new Move(piece->getX(), piece->getY(), piece->getX()+1, piece->getY()+dir));
	}
      }
    
      if (piece->getX()-1>=0) {
	if (board[piece->getY()+dir][piece->getX()-1] == NULL) {
	  moves.push_back(new Move(piece->getX(), piece->getY(), piece->getX()-1, piece->getY()+dir));
	} 
      }
      
    }
 } else {
   if (piece->getY()+1<8) {
     if (piece->getX()+1<8) {
       if (board[piece->getY()+1][piece->getX()+1] == NULL) {
	 moves.push_back(new Move(piece->getX(), piece->getY(), piece->getX()+1, piece->getY()+1));
       }
     }
     if (piece->getX()-1>=0) {
       if (board[piece->getY()+1][piece->getX()-1] == NULL) {
	 moves.push_back(new Move(piece->getX(), piece->getY(), piece->getX()-1, piece->getY()+1));
       } 
     }
   }
   if (piece->getY()-1>=0) {
     if (piece->getX()+1<8) {
       if (board[piece->getY()-1][piece->getX()+1] == NULL) {
	 moves.push_back(new Move(piece->getX(), piece->getY(), piece->getX()+1, piece->getY()-1));
       }
     }
     if (piece->getX()-1>=0) {
       if (board[piece->getY()-1][piece->getX()-1] == NULL) {
	 moves.push_back(new Move(piece->getX(), piece->getY(), piece->getX()-1, piece->getY()-1));
       }
     }
   }
 }
 if (moves.size() > 0) {
   index = rand() % moves.size();

   for (i=0; i<moves.size(); i++) {
     if (i != index) {
       delete moves[i];
     }
   }

   return moves.at(index);
 }   

 return NULL;
 
}

Move *Board::getHop(Piece *piece) {
  int xdir, dir, index, i;
  vector <Move*> moves;  
  srand( time(NULL) );
  
  if (piece->getColor() == BLACK) {
    dir = -2;
    xdir = -1;
  }
  else {
    dir = 2;
    xdir = 1;
  }
  
  if (piece->getType()==PIECE) {
    if (piece->getY()+dir>=0 && piece->getY()+dir<8) {
      if (piece->getX()+2<8) {
 	if (board[piece->getY()+dir][piece->getX()+2] == NULL) {
	  if (board[piece->getY()+xdir][piece->getX()+1] != NULL) {
	    if (board[piece->getY()+xdir][piece->getX()+1]->getColor() != piece->getColor()) {
	      moves.push_back(new Move(piece->getX(), piece->getY(), piece->getX()+2, piece->getY()+dir));
	    }
	  }
	}
      } else if (piece->getX()-2>=0) {
	if (board[piece->getY()+dir][piece->getX()-2] == NULL) {
	  if (board[piece->getY()+xdir][piece->getX()-1] != NULL) {
	    if (board[piece->getY()+xdir][piece->getX()-1]->getColor() != piece->getColor()) {
	      moves.push_back(new Move(piece->getX(), piece->getY(), piece->getX()-2, piece->getY()+dir));
	    }
	  }
	} 
      }
    }

  } else {
    if (piece->getY()+2<8) {
      if (piece->getX()+2<8) {
	if (board[piece->getY()+2][piece->getX()+2] == NULL) {
	  if (board[piece->getY()+1][piece->getX()+1] != NULL) {
	    if (board[piece->getY()+1][piece->getX()+1]->getColor() != piece->getColor()) {
	      moves.push_back(new Move(piece->getX(), piece->getY(), piece->getX()+2, piece->getY()+2));
	    }
	  }
	}
      }
      if (piece->getX()-2>=0) {
	if (board[piece->getY()+2][piece->getX()-2] == NULL) {
	  if (board[piece->getY()+1][piece->getX()-1] != NULL) {
	    if (board[piece->getY()+1][piece->getX()-1]->getColor() != piece->getColor()) {
	      moves.push_back(new Move(piece->getX(), piece->getY(), piece->getX()-2, piece->getY()+2));
	    }
	  }
	}
      }
    }
    if (piece->getY()-2>=0) {
      if (piece->getX()+2<8) {
	if (board[piece->getY()-2][piece->getX()+2] == NULL) {
	  if (board[piece->getY()-1][piece->getX()+1] != NULL) {
	    if (board[piece->getY()-1][piece->getX()+1]->getColor() != piece->getColor()) {
	      moves.push_back(new Move(piece->getX(), piece->getY(), piece->getX()+2, piece->getY()-2));
	    }
	  }
	}
      }
      if (piece->getX()-2>=0) {
	if (board[piece->getY()-2][piece->getX()-2] == NULL) {
	  if (board[piece->getY()-1][piece->getX()-1] != NULL) {
	    if (board[piece->getY()-1][piece->getX()-1]->getColor() != piece->getColor()) {
	      moves.push_back(new Move(piece->getX(), piece->getY(), piece->getX()-2, piece->getY()-2));
	    }
	  }
	}
      }
    }
  }
  
  if (moves.size() > 0) {

    index = rand() % moves.size();
    for (i=0; i<moves.size(); i++) {
      if (i != index) {
	delete moves[i];
      }
    }

    return moves.at(index);
  }

  return NULL;
}

void Board::tearDown() {
  int i,j;
  for (i=0; i<8; i++) {
    for (j=0; j<8; j++) {
      if (board[i][j] != NULL) {
	delete board[i][j];
      }
    }
  }


}
