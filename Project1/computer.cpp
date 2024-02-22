#include "Computer.h"

using namespace std;

void Computer::play(Board* board)
{
	// print board before making move
	board->printBoard();

	pair<string, string> strategy = strategize(board);

	board->MakeMove(strategy.first, this->getColor());
	board->printBoard();
	cout << "The computer moved it's piece from " << strategy.second;

};