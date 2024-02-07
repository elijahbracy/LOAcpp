#pragma once
#include "Player.h"

class Round
{
public: 
	Round();
	void roundStart(Player *p1, Player *p2);
	Player *nextPlayer;
	char coinFlip();
	//bool roundOver();

private:

};