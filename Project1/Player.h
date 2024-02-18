#pragma once
#include "Board.h"

class Player 
{
public:
	char color;
	int roundsWon = 0;
	int score = 0;
	virtual void play(Board* board) {};
	int totalPieces = 12;
	string name;
	void UpdateNumPieces(Board* board);
};