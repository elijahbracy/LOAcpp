#pragma once
#include "Player.h"

class Round
{
public: 
	void roundStart(Player& p1, Player& p2);
	char nextPlayer;
	char coinFlip();
};