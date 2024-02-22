#pragma once
#include "Player.h"
#include <iostream>
#include <map>
class Human : public Player
{
public:

	Human() {};
	~Human() override {};
	void displayName() { cout << name; };

private:
	string name = "Human";
	void play(Board* board) override;
	void getHelp(Board* board);
};