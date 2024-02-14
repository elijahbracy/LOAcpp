#pragma once
#include "Player.h"
#include <vector>


class Round
{
public: 
	Round();
	void roundStart(Player *p1, Player *p2);
	Player* curPlayer;
	Player *nextPlayer;
	char coinFlip();
	//bool roundOver();
	Player* GetNextPlayer(vector<Player*>& playerList, Player* curPlayer);
	void Score(Player* winner, int numOpponentPieces);
	bool playAgain = false;
	void PlayAgain();

	int turnsPlayed = 0;

	bool resumingGame = false;

	void announceRoundWin(Player* curPlayer, Player* nextPlayer);

private:

};