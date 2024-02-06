#include "Round.h"
#include "iostream"
#include <random>

using namespace std;

void Round::roundStart(Player& player1, Player& player2) {
	//if players have tie, flip coin, else player with more wins goes first
	if (player1.roundsWon == player2.roundsWon) {
		char coin = coinFlip();

		cout << "Call coin toss (H for heads, T for tails): ";
		char guess;
		cin >> guess;

		cout << "Result of coin toss: " << coin << endl;

		if (tolower(guess) == coin)
		{
			cout << "You won the coin toss. You will play first." << endl;
			nextPlayer = player1.color;
		}
		else
		{
			cout << "You lost the coin toss. Opponent will play first." << endl;
			nextPlayer = player2.color;
		}
	}
	else {
		nextPlayer = (player1.roundsWon < player2.roundsWon) ? player1.color : player2.color; // gpt for ternary operator syntax
	}
};

char Round::coinFlip()
{
	int headsOrTails;

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