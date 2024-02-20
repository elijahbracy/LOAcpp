#pragma once
#include "Board.h"

class Player 
{
public:
	char color;
	int roundsWon = 0;
	int score = 0;
	virtual void play(Board* board) {};
	vector<string> moves;
	vector<pair<string, int>> movesRanked;
	int totalPieces = 12;
	string name;
	void UpdateNumPieces(Board* board);
};