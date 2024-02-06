#include "Board.h"
#include "Round.h"

using namespace std;

int main(){
	Board board;
	Round round;
	Player p1;
	Player p2;
	round.roundStart(p1, p2);
	board.printBoard();
}