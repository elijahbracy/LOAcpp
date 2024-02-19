#pragma once
#include "Player.h"
#include "algorithm"

class Computer:public Player
{
	string name = "Computer";
	virtual void play(Board* board);
	//vector<pair<string, int>> gaugeMove(string move, Board board);

};