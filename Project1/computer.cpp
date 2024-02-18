#include "Computer.h"

using namespace std;

void Computer::play(Board* board)
{
	// fisrt iteration, just do random moves
	vector<string> moves = board->getPossibleMoves(this->color);

	// take first move from list
	board->MakeMove(moves[0], this->color);
};