#include "Round.h"
#include "iostream"
#include <random>
#include <algorithm>
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
			curPlayer = player1;
			nextPlayer = player2;
			player1->color = 'B';
			player2->color = 'W';

		}
		else
		{
			cout << "You lost the coin toss. Opponent will play first." << endl;
			curPlayer = player2;
			nextPlayer = player1;
			player1->color = 'W';
			player2->color = 'B';
		}
	}
	else {
		curPlayer = (player1->roundsWon < player2->roundsWon) ? player1 : player2; // gpt for ternary operator syntax
		nextPlayer = (player1->roundsWon > player2->roundsWon) ? player1 : player2;
	}
};

void Round::announceRoundWin(Player* curPlayer, Player* nextPlayer)
{
	cout << "Player: " << curPlayer->color << " won the round!" << endl;
	cout << curPlayer->color << " scored " << curPlayer->totalPieces - nextPlayer->totalPieces << " points" << endl;
	cout << nextPlayer->color << " scored " << "0 points" << endl;
};


Player* Round::GetNextPlayer(vector<Player*>& playerList, Player* curPlayer)
{
	// get index of current player
	auto it = find(playerList.begin(), playerList.end(), curPlayer);

	// it curPlayer found
	if (it != playerList.end())
	{
		// get index of cuPlayer within vector
		int index = distance(playerList.begin(), it);

		// move to next player, wrapping around if at end
		index = (index + 1) % playerList.size();

		// return pointer to next player
		cout << "next player: " << playerList[index]->color << endl;

		return playerList[index];
	}

	// if current player not found, log and return nullptr
	cout << "error: current player not found" << endl;
	return nullptr;
}

void Round::Score(Player* winner, int numOpponentPieces)
{
	winner->roundsWon += 1;
	winner->score += winner->totalPieces - numOpponentPieces;
};

void Round::PlayAgain()
{
	char response = 'Y';
	do
	{
		cout << "Play again? (y/n): ";
		cin >> response;
		response = toupper(response);

		if (response != 'Y' && response != 'N')
		{
			cout << "Invalid input. Enter 'y' to play again or 'n' to quit." << endl;
		}

	} while (response != 'Y' && response != 'N');

	if (response == 'Y')
	{
		this->playAgain = true;
	}

	return;

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