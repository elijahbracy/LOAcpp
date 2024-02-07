#pragma once
#include "Board.h"

class Player 
{
public:
	char color;
	int roundsWon = 0;
	int score;
	virtual void play(Board* board) {};
};