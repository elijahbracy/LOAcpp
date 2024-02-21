#pragma once
#include "Board.h"

class Player 
{
private:
	char m_color;
public:
	void setColor(char a_color) { a_color = m_color; }
	char getColor() const { return m_color; }
	int roundsWon = 0;
	int score = 0;
	int tournamentScore = 0;
	virtual void play(Board* board) {};
	//vector<string> moves;
	int totalPieces = 12;
	string name;
	void UpdateNumPieces(Board* board);
	virtual void displayName() {};
};