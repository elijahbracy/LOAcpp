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

	void SwitchPlayers();

	bool playAgain = false;

	void PlayAgain();

	int turnsPlayed = 0;

	bool resumingGame = false;

	void announceRoundWin(Player* curPlayer, Player* nextPlayer);

	bool suspend = false;

	void suspendGame(Board* board, Player* human, Player* comp);

	bool resumeGame();

	void loadGameState(Board* board, Player* human, Player* computer);

	string getPath();

private:

};