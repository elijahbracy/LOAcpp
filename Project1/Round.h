#pragma once
#include "Player.h"
#include <vector>


class Round
{
public:
	Round() {};
	~Round() {};
	void roundStart(Player* p1, Player* p2);

	char coinFlip();

	void Score(Player* winner, int numOpponentPieces);

	void SwitchPlayers();

	void PlayAgain();

	int getTurnsPlayed() const { return m_turnsPlayed; }

	void setTurnsPlayed(int a_turnsPlayed) { m_turnsPlayed = a_turnsPlayed; }

	void setResumeGame(bool a_resume) { m_resumingGame = a_resume;}
	bool getResumeGame() const { return m_resumingGame; }

	void announceRoundWin(Player* curPlayer, Player* nextPlayer);

	void setPlayAgain(bool a_playAgain) { m_playAgain = a_playAgain; }
	bool getPlayAgain() const { return m_playAgain; }

	void suspendGame();

	bool resumeGame();

	void loadGameState(Board* board, Player* human, Player* computer);

	string getPath();

	void setCurPlayer(Player* a_curPlayer) { m_curPlayer = a_curPlayer; }
	Player* getCurPlayer() const { return m_curPlayer; }

	void setNextPlayer(Player* a_nextPlayer) { m_nextPlayer = a_nextPlayer; }
	Player* getNextPlayer() const { return m_nextPlayer; }

	void setSuspend(bool a_suspend) { m_suspend = a_suspend; }
	bool getSuspend() const { return m_suspend; }


private:

	int m_turnsPlayed = 0;

	Player* m_curPlayer = nullptr;

	Player* m_nextPlayer = nullptr;

	bool m_suspend = false;

	bool m_resumingGame = false;

	bool m_playAgain = false;
};