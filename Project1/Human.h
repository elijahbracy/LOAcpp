#pragma once
#include "Player.h"
#include <iostream>
#include <map>
class Human : public Player
{
	void play(Board* board) override {
		cout << "make a move (ex. b1->b3)" << endl;
		string move;
		cin >> move;

		if (board->isValid(move)) {
			//TODO: make piece move, update board
			
		}
	};




};