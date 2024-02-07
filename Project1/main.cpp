#include "Board.h"
#include "Round.h"
#include "Human.h"

int main() {
	Board *board = new Board;
	Round round;
	Human *p1 = new Human;
	Human *p2 = new Human;
	round.roundStart(p1, p2);
	board->printBoard();
	//game loop
	do {
		round.nextPlayer->play(board);


	} while (1);
}