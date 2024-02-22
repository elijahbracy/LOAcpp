#pragma once
#include "Player.h"



void Player::UpdateNumPieces(Board* board)
{
	this->setPiecesOnBoard(board->CountPieces(this->getColor()));
};

pair<string, string> Player::strategize(Board* board)
{
	string moveToMake;
	string reason;

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
			if (board->isCapture(move, this->getColor(), opponentColor) && board->isThwart(move, this->getColor(), opponentColor) && !board->isWinningMove(move, this->getColor())) // capturing while not giving opponent win and is not winning move itself = delay
			{
				moveToMake = move;
				reason = move.substr(0, 2) + " to " + move.substr(4) + ", delaying win to increase score.\n";
				return make_pair(moveToMake, reason);
			}
		}
	}

	// check for winning move, if found, make it
	for (string move : moves)
	{
		if (board->isWinningMove(move, this->getColor()))
		{
			moveToMake = move;
			reason = move.substr(0, 2) + " to " + move.substr(4) + " to win the round.\n";
			return make_pair(moveToMake, reason);
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
				moveToMake = move;
				reason = move.substr(0, 2) + " to " + move.substr(4) + " to thwart opponent's win.\n";
				return make_pair(moveToMake, reason);
			}
		}
	}

	//test for connecting 2 groups
	for (string move : moves)
	{
		if (board->isConnectingGroups(move, this->getColor()) && board->isThwart(move, this->getColor(), opponentColor))
		{
			moveToMake = move;
			reason = move.substr(0, 2) + " to " + move.substr(4) + " to connect 2 groups.\n";
			return make_pair(moveToMake, reason);
		}
	}


	// test for condensing groups
	for (string move : moves)
	{
		if (board->isCondensingGroups(move, this->getColor()) && board->isThwart(move, this->getColor(), opponentColor))
		{
			moveToMake = move;
			reason = move.substr(0, 2) + " to " + move.substr(4) + " to condense groups.\n";
			return make_pair(moveToMake, reason);
		}
	}

	// test for blocks
	for (string move : moves)
	{
		if (board->isBlock(move, this->getColor(), opponentColor))
		{
			moveToMake = move;
			reason = move.substr(0, 2) + " to " + move.substr(4) + " to block opponent.\n";
			return make_pair(moveToMake, reason);
		}
	}

	// capture
	for (string move : moves)
	{
		if (board->isCapture(move, this->getColor(), opponentColor) && board->isThwart(move, this->getColor(), opponentColor))
		{
			moveToMake = move;
			reason = move.substr(0, 2) + " to " + move.substr(4) + " to capture opponent's piece.\n";
			return make_pair(moveToMake, reason);
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
				moveToMake = move;
				reason = move.substr(0, 2) + " to " + move.substr(4) + " to capture piece as last resort.\n";
				return make_pair(moveToMake, reason);
			}
		}
	}

	// last resort stall
	for (string move : moves)
	{
		if (board->isStall(move, this->getColor(), opponentColor))
		{
			moveToMake = move;
			reason = "Suggested move: " + move.substr(0, 2) + " to " + move.substr(4) + " to stall defeat.\n";
			return make_pair(moveToMake, reason);
		}
	}
};

