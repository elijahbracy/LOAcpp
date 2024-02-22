#pragma once
#include "Player.h"
#include "algorithm"

class Computer :public Player
{
public:
	Computer() {};
	~Computer() override {};
	void displayName() { cout << name; };
private:
	virtual void play(Board* board);
	string name = "Computer";
};