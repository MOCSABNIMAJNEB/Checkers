#include <iostream>
#include "player.h"
#include "humanPlayer.h"
#include "board.h"
#include "move.h"


using namespace std;

Move *humanPlayer::getMove() {
  char i, k, j, m;
  char inp[100];
  cout << "Please select a move : \n";
  cout << "column from: ";
  cin >> inp;
  if (inp[0] == 'M') {
    return 0;
  }
  i = inp[0] - 65;
  cout << "row from: ";
  cin >> inp;
  if (inp[0] == 'M') {
    return 0;
  }
  j = inp[0] - 48;
  cout << "column to: ";
  cin >> inp;
  if (inp[0] == 'M') {
    return 0;
  }
  k = inp[0] - 65;
  cout << "row to: ";
  cin >> inp;
  if (inp[0] == 'M') {
    return 0;
  }
  m = inp[0] - 48;


  Move *thisMove = new Move(i, j, k, m);
  return thisMove;
};


void humanPlayer::getHelp() { };



