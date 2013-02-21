#ifndef __BOARD
#define __BOARD
#include <string>
#include "move.h"
#include "piece.h"

class Board {
 private:
  // integers which keep track of the number of pieces of each color on the board
  int _blackPieces, _redPieces;
  // boolean which keeps track of if a player with a particular color has a hop
  bool _redHasHop, _blackHasHop;
  Piece *board[8][8];
  color _turn;  
  
 public:
  Board();
  Board(bool start);
  /*
   * Given a color, finds whether or not there is a moveable piece and returns that piece
   * contains the logic for determining if there is a hop available and resets the number of
   * pieces for each player based on the board state.
   */
  void clear();
  void save();
  Piece *getPieceToMove(color c);
  /*
   * Given a piece, returns the next legal move. Returns null if there are no legal
   * moves for that piece
   */
  Move *getLegalMove(Piece *p);
  /*
   * Checks very briefly if a move is legal but not relative to the piece type
   * but rather whether or not the source and destination are empty and whether
   * or not the source and destination points are on the board
   */
  bool isLegal(Move *m);
  /*
   * Given a color and a move, makes that move and subsequent required moves (double jumps)
   * calls isLegal and canTake to determine if the move can be taken;
   */
  bool move(color c, Move *m);
  std::string toString();

  void placePiece(Piece *p);

  /*
   * A boolean method to check if the game is over. Checks both whether or not either
   * player is out of pieces or either player is out of moves.
   */
  bool isOver();
  /*
   * Given a piece, returns true if that piece can hop (jump)
   */
  bool hasHop(Piece *piece);
  /*
   * Given a piece, returns a hop for that piece or NULL if it can't hop
   * should never return null since is always guarded by hasHop
   */
  Move *getHop(Piece *piece);
  /*
   * Given a piece, returns true if that piece can skip (single move)
   */
  bool hasSkip(Piece *piece);
  /*
   * Given a piece returns a skip move for that piece
   */
  Move *getSkip(Piece *piece);
  /*
   * Keeps track of whether a color has a hop, used to ensure player takes hop if 
   * they have one
   */
  bool colorHasHop(color c);
  /*
   * Method which removes pieces from a board once that board is done playing
   */
  void tearDown();
  color getTurn() { return _turn; };
  void setTurn(color c) { _turn = c; };

};

#endif
