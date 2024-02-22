#pragma once
#include "Board.h"
using namespace std;
class Player 
{
public:
	Player() {};
	virtual ~Player() {};
	void setColor(char a_color) { m_color = a_color; }
	char getColor() const { return m_color; }
	void setRoundsWon(int a_roundsWon) { m_roundsWon = a_roundsWon; }
	int getRoundsWon() const { return m_roundsWon; }
	void setScore(int a_score) { m_score = a_score; }
	int getScore() const { return m_score; }
	void setTournamentScore(int a_tournamentScore) { m_tournamentScore = a_tournamentScore; }
	int getTournamentScore() const { return m_tournamentScore; }
	virtual void play(Board* board) {};
	pair<string, string> strategize(Board* board);
	void setPiecesOnBoard(int a_piecesOnBoard) { m_piecesOnBoard = a_piecesOnBoard; }
	int getPiecesOnBoard() const { return m_piecesOnBoard; }
	void UpdateNumPieces(Board* board);
	virtual void displayName() {};
private:
	char m_color;
	int m_roundsWon = 0;
	int m_score = 0;
	int m_tournamentScore = 0;
	int m_piecesOnBoard = 12;
	string m_name;
};