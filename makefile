all: checkers

checkers:
	g++ -g -o checkers move.cpp controller.cpp player.cpp humanPlayer.cpp computerPlayer.cpp board.cpp piece.cpp

clean:
	rm checkers
	rm *~
