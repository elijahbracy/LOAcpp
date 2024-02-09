#pragma once
#include "Player.h"
#include <iostream>
#include <map>
class Human : public Player
{
public:

	Human() {};
private:
	void play(Board* board) override {
		cout << "make a move (ex. b1->b3)" << endl;
		string move;
		cin >> move;

		if (board->isValid(move, this->color)) {
			//TODO: make piece move, update board
			//board->MakeMove(move)
		}
		else
		{
			cout << "invalid" << endl;
		}
	};




};