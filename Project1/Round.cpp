#include "Round.h"
#include "iostream"
#include <random>

using namespace std;

Round::Round() {};


void Round::roundStart(Player *player1, Player *player2) {
	//if players have tie, flip coin, else player with more wins goes first
	if (player1->roundsWon == player2->roundsWon) {
		char coinResult = 'h';//coinFlip();

		cout << "Call coin toss (H for heads, T for tails): ";
		char guess;
		cin >> guess;

		cout << "Result of coin toss: " << coinResult << endl;

		if (tolower(guess) == coinResult)
		{
			cout << "You won the coin toss. You will play first." << endl;
			nextPlayer = player1;
			player1->color = 'B';
			player2->color = 'W';

		}
		else
		{
			cout << "You lost the coin toss. Opponent will play first." << endl;
			nextPlayer = player2;
			player1->color = 'W';
			player2->color = 'B';
		}
	}
	else {
		nextPlayer = (player1->roundsWon < player2->roundsWon) ? player1 : player2; // gpt for ternary operator syntax
	}
};

char Round::coinFlip()
{
	int headsOrTails;
	srand(time(NULL));
	headsOrTails = rand() % 2 + 1; // will return 1 for heads or 2 for tails

	if (headsOrTails == 1)
	{
		return 'h';
	}
	else
	{
		return 't';
	}


}