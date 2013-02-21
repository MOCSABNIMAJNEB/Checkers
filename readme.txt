The game can be run with 3 flags, '-c', '-h' and '-t' ... The -c flag is a human v computer mode, the -h is human vs human mode and the -t flag is a computer v computer test mode. The file game.log contains an example game. To generate example games run it as './checkers -t > game.log'. The game is run from controller.cpp and contains the following classes:

move.cpp
board.cpp
piece.cpp
player.cpp
: humanPlayer.cpp (inherits from player.cpp)
: computerPlayer.cpp (inherits from player.cpp)


Most of the functionality is inside of board.cpp, the piece class does some checking of legal moves for that piece using the canTake() method. Human players and computer players each have different methods to get moves. Illegal moves should throw output errors (computers never make illegal moves so this must be tested by hand). Pieces are required to jump if they have a jump and if that jump can take a second jump it does so. If it has more than one second jump it picks the second jump randomly. The AI simply selects a random legal move where only jumps are legal if there is a jump available else skips are legal. If either player has no more pieces or no more moves available the game is over. Please see header files for additional comments.

Known issues:
      - When runnning through valgrind throws a number of 'Move or jump depends on uninitialized values' errors. Doesn't seem to break program but need to track down why. 
      - Computer seems to preferentially move to the right of the board. Unsure of if there is possibly some broken logic in getHop, hasHop, getSkip or hasSkip which are all
        relatively big functions. Could probably break piece into King and Regular subclasses and break some of that logic out to make it easier to parse. Otherwise not sure how
	to test this well. Nevertheless, manages to always reach endgame so not game-breaking.
