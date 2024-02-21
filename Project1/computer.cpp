#include "Computer.h"

using namespace std;

void Computer::play(Board* board)
{
	// print board before making move
	board->printBoard();

	vector<string> moves = board->getPossibleMoves(this->getColor());
	sort(moves.begin(), moves.end());

	cout << "List of possible moves: " << endl;
	for (string move : moves)
	{
		cout << move << endl;
	}

	

	char opponentColor = (this->getColor() == 'W') ? 'B' : 'W';

	// check for winning move
	bool winThisTurn = false;

	for (string move : moves)
	{
		if (board->isWinningMove(move, this->getColor()))
		{
			winThisTurn = true;
		}
	}

	// check for delay
	// if winning move, see if capture will not cause opponent win
	if (winThisTurn)
	{
		for (string move : moves)
		{
			if (board->isCapture(move, this->getColor(), opponentColor) && board->isThwart(move, this->getColor(), opponentColor)) // capturing while not giving opponent win = delay
			{
				board->MakeMove(move, this->getColor());
				board->printBoard();
				cout << "The computer moved its piece from " << move.substr(0, 2) << " to " << move.substr(4) << ", delaying win to increase score." << endl;
				return;
			}
		}
	}

	// check for winning move, if found, make it
	for (string move : moves)
	{
		if (board->isWinningMove(move, this->getColor()))
		{
			board->MakeMove(move, this->getColor());
			board->printBoard();
			cout << "The computer moved its piece from " << move.substr(0, 2) << " to " << move.substr(4) << " to win the round." << endl;
			return;
		}
	}

	// next check for thwart
	// need to know if opponents next move is win

	// get opponents possible moves and see if win is imminent
	vector<string> opponentMoves = board->getPossibleMoves(opponentColor);

	bool winIncoming = false;

	for (string move : opponentMoves)
	{
		if (board->isWinningMove(move, opponentColor))
		{
			winIncoming = true;
		}
	}

	//test for thwarts if win is incoming
	if (winIncoming)
	{
		for (string move : moves)
		{
			if (board->isThwart(move, this->getColor(), opponentColor))
			{
				board->MakeMove(move, this->getColor());
				board->printBoard();
				cout << "The computer moved its piece from " << move.substr(0, 2) << " to " << move.substr(4) << " to thwart opponent's win." << endl;
				return;
			}
		}
	}

	//test for connecting 2 groups
	for (string move : moves)
	{
		if (board->isConnectingGroups(move, this->getColor()) && board->isThwart(move, this->getColor(), opponentColor))
		{
			board->MakeMove(move, this->getColor());
			board->printBoard();
			cout << "The computer moved its piece from " << move.substr(0, 2) << " to " << move.substr(4) << " to connect 2 groups." << endl;
			return;
		}
	}

	// test for condensing groups
	for (string move : moves)
	{
		if (board->isCondensingGroups(move, this->getColor()) && board->isThwart(move, this->getColor(), opponentColor))
		{
			board->MakeMove(move, this->getColor());
			board->printBoard();
			cout << "The computer moved its piece from " << move.substr(0, 2) << " to " << move.substr(4) << " to condense groups." << endl;
			return;
		}
	}

	// test for blocks
	for (string move : moves)
	{
		if (board->isBlock(move, this->getColor(), opponentColor))
		{
			board->MakeMove(move, this->getColor());
			board->printBoard();
			cout << "The computer moved its piece from " << move.substr(0, 2) << " to " << move.substr(4) << " to block opponent." << endl;
			return;
		}
	}

	// check for capture
	for (string move : moves)
	{
		if (board->isCapture(move, this->getColor(), opponentColor) && board->isThwart(move, this->getColor(), opponentColor))
		{
			board->MakeMove(move, this->getColor());
			board->printBoard();
			cout << "The computer moved its piece from " << move.substr(0, 2) << " to " << move.substr(4) << " to capture opponent's piece." << endl;
			return;
		}
	}

	// last resort capture
	//if win incoming
	if (winIncoming)
	{
		for (string move : moves)
		{
			if (board->isCapture(move, this->getColor(), opponentColor))
			{
				board->MakeMove(move, this->getColor());
				board->printBoard();
				cout << "The computer moved its piece from " << move.substr(0, 2) << " to " << move.substr(4) << " to capture piece as last resort." << endl;
				return;
			}
		}
	}

	// last resort stall
	for (string move : moves)
	{
		if (board->isStall(move, this->getColor(), opponentColor))
		{
			board->MakeMove(move, this->getColor());
			board->printBoard();
			cout << "The computer moved its piece from " << move.substr(0, 2) << " to " << move.substr(4) << " to stall defeat." << endl;
			return;
		}
	}

};