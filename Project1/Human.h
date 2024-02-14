#pragma once
#include "Player.h"
#include <iostream>
#include <map>
class Human : public Player
{
public:

	Human() {};
private:
	void play(Board* board) override 
	{
		
		string move;
		bool validMove;
		do
		{
			cout << "make a move (ex. b1->b3)" << endl;
			cin >> move;
			validMove = board->isValid(move, this->color);
			if (validMove)
			{
				board->MakeMove(move, this->color);
				break;
			}
			cout << "invalid" << endl;
		} while (!validMove);
	};




};