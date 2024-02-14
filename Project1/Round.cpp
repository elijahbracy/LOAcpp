#include "Round.h"
#include "iostream"
#include <random>
#include <algorithm>
#include <fstream>
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
	char response;
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


};

void Round::suspendGame(Board* board, Player* human, Player* comp)
{
	char response;
	do
	{
		cout << "Suspend game (data will be saved)?  (y/n): ";
		cin >> response;
		response = toupper(response);

		if (response != 'Y' && response != 'N')
		{
			cout << "Invalid input. Enter 'y' to suspend game or 'n' to continue." << endl;
		}

	} while (response != 'Y' && response != 'N');

	if (response == 'Y')
	{
		// create output file stream object
		ofstream out;

		// open file
		out.open("gameState.txt");

		// if unable to open display error message
		if (!out.is_open())
		{
			cerr << "error opening file" << endl;
		}

		// get board
		const char(*boardPtr)[8] = board->getBoard();

		out << "Board:" << endl;
		// save board state
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				// replace '.' with 'x'
				if (boardPtr[i][j] == '.')
				{
					out << "x ";
				}
				else
				{
					out << boardPtr[i][j] << ' ';
				}
				
			}
			out << endl;
		}

		out << "Human:" << endl;
		out << "Rounds won: " << human->roundsWon << endl;
		out << "Score: " << human->score << endl;
		out << endl;
		out << "Computer: " << endl;
		out << "Rounds won: " << comp->roundsWon << endl;
		out << "Score: " << comp->score << endl;
		out << endl;
		out << "Next Player: " << this->nextPlayer->color << endl;
		out << "Color: " << this->nextPlayer->color << endl;

		out.close();

	}
};