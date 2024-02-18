#pragma once
#include "Player.h"

class Computer:public Player
{
	string name = "Computer";
	virtual void play(Board* board) {};

};