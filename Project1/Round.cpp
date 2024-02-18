#include "Round.h"
#include "iostream"
#include <random>
#include <algorithm>
#include <fstream>
#include <sstream>
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
			cout << "You won the coin toss. You will play first. Your color: Black" << endl;
			curPlayer = player1;
			nextPlayer = player2;
			player1->color = 'B';
			player2->color = 'W';

		}
		else
		{
			cout << "You lost the coin toss. Opponent will play first. Your color: White" << endl;
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
		
		out << endl;

		out << "Human:" << endl;
		out << "Rounds won: " << human->roundsWon << endl;
		out << "Score: " << human->score << endl;
		out << endl;
		out << "Computer: " << endl;
		out << "Rounds won: " << comp->roundsWon << endl;
		out << "Score: " << comp->score << endl;
		out << endl;
		if (this->nextPlayer == human)
		{
			out << "Next player: " << "Human" << endl;
		}
		else
		{
			out << "Next player: " << "Computer" << endl;
		}
		if (this->nextPlayer->color == 'B')
		{
			out << "Color: " << "Black" << endl;
		}
		else
		{
			out << "Color: " << "White" << endl;
		}
		

		out.close();

		this->suspend = true;
	}
};

bool Round::resumeGame()
{
	cout << "Would you like to resume a game?: ";
	char response;
	do
	{
		cin >> response;

		response = toupper(response);

		if (response != 'Y' && response != 'N')
		{
			cout << "Invalid input. Please enter 'y' for yes or 'n' to start a new game." << endl;
		}

	} while (response != 'Y' && response != 'N');

	if (response == 'N')
	{
		return false;
	}

	return true;
};

void Round::loadGameState(Board* board, Player* human, Player* computer)
{
	string path = getPath();

	ifstream inFile(path);

	string line;

	// iterate through all lines
	while (getline(inFile, line))
	{
		// when board line found
		if (line.find("Board:") != string::npos)
		{

			// get board
			char newboard[8][8];

			for (int i = 0; i < 8; i++)
			{
				//get next line
				getline(inFile, line);

				
				for (int j = 0; j < 8; j++)
				{
					// make everything uppercase and adjust for whitespace but multiplying j by 2
					char space = toupper(line[j * 2]);
					//cout << line[j * 2];
					
					// replace 'x's with '.'s
					if (space == 'X')
					{
						newboard[i][j] = '.';
					}

					else
					{
						newboard[i][j] = toupper(line[j * 2]);
					}
				}
				//cout << endl;
			}

			board->setBoard(newboard);
		}

		// when human line found, 
		if (line.find("Human:") != string::npos)
		{
			//get next line
			getline(inFile, line);
			
			// look for Rounds won:
			size_t pos = line.find("Rounds won:");

			// if found, set human rounds won to number after colon
			if (pos != string::npos)
			{
				cout << "human rounds won = " << stoi(line.substr(pos + 12)) << endl;
				human->roundsWon = stoi(line.substr(pos + 12));
			}

			// get next line for score
			getline(inFile, line);

			// look for score
			pos = line.find("Score:");

			// if found, set score
			if (pos != string::npos)
			{
				cout << "human score = " << stoi(line.substr(pos + 7)) << endl;
				human->roundsWon = stoi(line.substr(pos + 7));
			}
		}

		// when computer line found
		if (line.find("Computer:") != string::npos)
		{
			//get next line
			getline(inFile, line);

			// look for Rounds won:
			size_t pos = line.find("Rounds won:");

			// if found, set human rounds won to number after colon
			if (pos != string::npos)
			{
				cout << "comp rounds won = " << stoi(line.substr(pos + 12)) << endl;
				computer->roundsWon = stoi(line.substr(pos + 12));
			}

			// get next line for score
			getline(inFile, line);

			// look for score
			pos = line.find("Score:");

			// if found, set score
			if (pos != string::npos)
			{
				cout << "computer score = " << stoi(line.substr(pos + 7)) << endl;
				computer->roundsWon = stoi(line.substr(pos + 7));
			}
		}

		// when next player line found:
		if (line.find("Next player:") != string::npos)
		{
			// look for player type:
			size_t pos = line.find("Next player:");

			cout << line.substr(pos + 13) << endl;
			if (line.substr(pos + 13) == "Human")
			{
				cout << "current player = human" << endl;
				this->curPlayer = human;
				this->nextPlayer = computer;
			}

			else
			{
				this->curPlayer = computer;
				this->nextPlayer = human;
			}
		}

		// look for color
		
		if (line.find("Color:") != string::npos)
		{
			// look for player type:
			size_t pos = line.find("Color:");

			cout << line.substr(pos + 7) << endl;
			if (line.substr(pos + 7) == "Black")
			{
				cout << "current player color = black" << endl;
				this->curPlayer->color = 'B';
				this->nextPlayer->color = 'W';
			}

			else
			{
				this->curPlayer->color = 'W';
				this->nextPlayer->color = 'B';
			}
		}
	}
	cout << "game state loaded." << endl;
	this->resumingGame = true;
}

string Round::getPath()
{
	cout << "Please enter filename. (ex. file.txt)" << endl;

	string path;
	bool workingPath;
	do
	{
		cin >> path;

		ifstream inFile(path);

		if (!inFile.is_open())
		{
			cerr << "Error opening file." << endl;
			workingPath = false;
			cout << "please try entering filename again. try specifying whole path (ex C:/Desktop/file.txt)" << endl;
		}
		else 
		{
			workingPath = true;
			inFile.close();
		}

	} while (!workingPath);

	return path;
}