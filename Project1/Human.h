#pragma once
#include "Player.h"
#include <iostream>
#include <map>
class Human : public Player
{
public:

	Human() {};
	string name = "Human";
	void displayName() { cout << name; };

private:
    void play(Board* board) override
    {
        board->printBoard();

        string input;
        bool validMove;

        while (true) {
            cout << "Enter 'h' to enter help mode or make a move (ex. b1->b3): ";
            cin >> input;

            // Check if the input is 'h' for help mode
            if (input == "h") {
                getHelp(board); // Call the function to display help
                break; // Exit the loop after help mode
            }
            else {

                // Check if the move is valid
                validMove = board->isValid(input, this->getColor());

                if (validMove) {
                    board->MakeMove(input, this->getColor());
					board->printBoard();
                    break;
                }
                else {
                    cout << "Invalid move. Please try again." << endl;
                }
            }
        }
		return;
    }


	void getHelp(Board* board)
	{
		vector<string> moves = board->getPossibleMoves(this->getColor());

		cout << "List of possible moves: " << endl;
		for (string move : moves)
		{
			cout << move << endl;
		}

		char opponentColor = (this->getColor() == 'W') ? 'B' : 'W';

		// check for winning move
		bool winThisTurn = false;

		for (string move : moves)
		{
			if (board->isWinningMove(move, this->getColor()))
			{
				winThisTurn = true;
			}
		}

		// check for delay
		// if winning move, see if capture will not cause opponent win
		if (winThisTurn)
		{
			for (string move : moves)
			{
				if (board->isCapture(move, this->getColor(), opponentColor) && board->isThwart(move, this->getColor(), opponentColor) && !board->isWinningMove(move, this->getColor())) // capturing while not giving opponent win and is not winning move itself = delay
				{
					cout << "Suggested move: " << move.substr(0, 2) << " to " << move.substr(4) << ", delaying win to increase score." << endl;
					play(board);
					return;
				}
			}
		}

		// check for winning move, if found, make it
		for (string move : moves)
		{
			if (board->isWinningMove(move, this->getColor()))
			{
				cout << "Suggested move: " << move.substr(0, 2) << " to " << move.substr(4) << " to win the round." << endl;
				play(board);
				return;
			}
		}

		// next check for thwart
		// need to know if opponents next move is win

		// get opponents possible moves and see if win is imminent
		vector<string> opponentMoves = board->getPossibleMoves(opponentColor);

		bool winIncoming = false;

		for (string move : opponentMoves)
		{
			if (board->isWinningMove(move, opponentColor))
			{
				winIncoming = true;
			}
		}

		//test for thwarts if win is incoming
		if (winIncoming)
		{
			for (string move : moves)
			{
				if (board->isThwart(move, this->getColor(), opponentColor))
				{
					cout << "Suggested move: " << move.substr(0, 2) << " to " << move.substr(4) << " to thwart opponent's win." << endl;
					play(board);
					return;
				}
			}
		}

		//test for connecting 2 groups
		for (string move : moves)
		{
			if (board->isConnectingGroups(move, this->getColor()) && board->isThwart(move, this->getColor(), opponentColor))
			{
				cout << "Suggested move: " << move.substr(0, 2) << " to " << move.substr(4) << " to connect 2 groups." << endl;
				play(board);
				return;
			}
		}


		// test for condensing groups
		for (string move : moves)
		{
			if (board->isCondensingGroups(move, this->getColor()) && board->isThwart(move, this->getColor(), opponentColor))
			{
				cout << "Suggested move: " << move.substr(0, 2) << " to " << move.substr(4) << " to condense groups." << endl;
				play(board);
				return;
			}
		}

		// test for blocks
		for (string move : moves)
		{
			if (board->isBlock(move, this->getColor(), opponentColor))
			{
				cout << "The computer moved its piece from " << move.substr(0, 2) << " to " << move.substr(4) << " to block opponent." << endl;
				play(board);
				return;
			}
		}

		// capture if win is coming and cant stop it
		for (string move : moves)
		{
			if (board->isCapture(move, this->getColor(), opponentColor) && board->isThwart(move, this->getColor(), opponentColor))
			{
				cout << "The computer moved its piece from " << move.substr(0, 2) << " to " << move.substr(4) << " to capture opponent's piece." << endl;
				play(board);
				return;
			}
		}
	};

};