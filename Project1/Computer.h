#pragma once
#include "Player.h"
#include "algorithm"

class Computer :public Player
{
	string name = "Computer";
	virtual void play(Board* board);
	void displayName() { cout << name; };
	//vector<pair<string, int>> gaugeMove(string move, Board board);

};