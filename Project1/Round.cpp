#include "Round.h"
#include "iostream"
#include <random>
#include <algorithm>
#include <fstream>
#include <sstream>
using namespace std;

void Round::roundStart(Player* player1, Player* player2) {

	// if players have tie, flip coin, else player with more wins goes first
	if (player1->getRoundsWon() == player2->getRoundsWon()) {
		char coinResult = coinFlip();

		char guess;

		// validation for guess
		while (true) {
			cout << "Call coin toss (H for heads, T for tails): ";
			cin >> guess;

			guess = tolower(guess);

			// check validity
			if (guess == 'h' || guess == 't') {
				break;
			}
			else {
				cout << "Invalid input. Please enter 'H' for heads or 'T' for tails." << endl;
			}
		}

		// echo input
		cout << "You called: " << guess << endl;

		cout << "Result of coin toss: " << coinResult << endl;

		if (tolower(guess) == coinResult)
		{
			cout << "You won the coin toss. You will play first. Your color: Black" << endl;
			setCurPlayer(player1);
			setNextPlayer(player2);
			player1->setColor('B');
			player2->setColor('W');

		}
		else
		{
			cout << "You lost the coin toss. Opponent will play first. Your color: White" << endl;
			setCurPlayer(player2);
			setNextPlayer(player1);
			player1->setColor('W');
			player2->setColor('B');
		}
	}
	else {
		setCurPlayer((player1->getRoundsWon() > player2->getRoundsWon()) ? player1 : player2); // gpt for ternary operator syntax
		setNextPlayer((player1->getRoundsWon() < player2->getRoundsWon()) ? player1 : player2);
	}
};

void Round::announceRoundWin(Player* curPlayer, Player* nextPlayer)
{
	curPlayer->displayName(); 
	cout<< " won the round!" << endl;


	curPlayer->displayName();
	cout << " scored " << curPlayer->getPiecesOnBoard() - nextPlayer->getPiecesOnBoard() << " points" << endl;
	cout << "Total tournament score after round:" << curPlayer->getTournamentScore() << endl;


	nextPlayer->displayName();
	cout << " scored " << "0 points" << endl;
	cout << "Total tournament score after round:" << nextPlayer->getTournamentScore() << endl;
	curPlayer->setScore(0);
};

void Round::SwitchPlayers()
{
	Player* buff = getCurPlayer();

	setCurPlayer(getNextPlayer());

	setNextPlayer(buff);
}

void Round::Score(Player* winner, int numOpponentPieces)
{
	winner->setRoundsWon(winner->getRoundsWon() + 1);
	winner->setScore(winner->getPiecesOnBoard() - numOpponentPieces);
	winner->setTournamentScore(winner->getTournamentScore() + winner->getScore());
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
		setResumeGame(false);
		setPlayAgain(true);
		return;
	}
	setPlayAgain(false);

};

char Round::coinFlip()
{
	int headsOrTails;
	srand(time(NULL));
	headsOrTails = rand() % 2 + 1;

	if (headsOrTails == 1)
	{
		return 'h';
	}
	else
	{
		return 't';
	}


};

void Round::suspendGame()
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

		string filename;
		bool validFilename = false;

		do {
			cout << "Please enter a filename for the game save file: ";
			cin >> filename;

			// Check if the filename is valid by looking for any invalid characters
			if (filename.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_.") == string::npos) {
				// Filename contains only valid characters
				validFilename = true;
			}
			else {
				// Invalid filename
				cout << "Invalid filename. Please use only letters, numbers, underscores, and periods." << endl;
			}
		} while (!validFilename);

		// Check if the filename ends with ".txt"
		if (filename.length() >= 4 && filename.substr(filename.length() - 4) != ".txt") {
			// If it doesn't end with ".txt", add the extension
			filename += ".txt";
		}

		// Open the file with the validated filename
		out.open(filename);

		// if unable to open display error message
		if (!out.is_open())
		{
			cerr << "error opening file" << endl;
		}

		// get board
		const char(*boardPtr)[8] = this.bo->getBoard();

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
		out << "Rounds won: " << human->getRoundsWon() << endl;
		out << "Score: " << human->getScore() << endl;
		out << endl;
		out << "Computer: " << endl;
		out << "Rounds won: " << comp->getRoundsWon() << endl;
		out << "Score: " << comp->getScore() << endl;
		out << endl;
		if (getNextPlayer() == human)
		{
			out << "Next player: " << "Human" << endl;
		}
		else
		{
			out << "Next player: " << "Computer" << endl;
		}
		if (getNextPlayer()->getColor() == 'B')
		{
			out << "Color: " << "Black" << endl;
		}
		else
		{
			out << "Color: " << "White" << endl;
		}


		out.close();

		setSuspend(true);
	}
};

bool Round::resumeGame()
{
	cout << "Would you like to resume a game? (y/n): ";
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
				//cout << "human rounds won = " << stoi(line.substr(pos + 12)) << endl;
				human->setRoundsWon(stoi(line.substr(pos + 12)));
			}

			// get next line for score
			getline(inFile, line);

			// look for score
			pos = line.find("Score:");

			// if found, set score
			if (pos != string::npos)
			{
				//cout << "human score = " << stoi(line.substr(pos + 7)) << endl;
				human->setTournamentScore(stoi(line.substr(pos + 7)));
			}
		}

		// when computer line found
		if (line.find("Computer:") != string::npos)
		{
			//get next line
			getline(inFile, line);

			// look for Rounds won:
			size_t pos = line.find("Rounds won:");

			// if found, set computer rounds won to number after colon
			if (pos != string::npos)
			{
				//cout << "comp rounds won = " << stoi(line.substr(pos + 12)) << endl;
				computer->setRoundsWon(stoi(line.substr(pos + 12)));
			}

			// get next line for score
			getline(inFile, line);

			// look for score
			pos = line.find("Score:");

			// if found, set score
			if (pos != string::npos)
			{
				//cout << "computer score = " << stoi(line.substr(pos + 7)) << endl;
				computer->setTournamentScore(stoi(line.substr(pos + 7)));
			}
		}

		// when next player line found:
		if (line.find("Next player:") != string::npos)
		{
			// look for player type:
			size_t pos = line.find("Next player:");

			//cout << line.substr(pos + 13) << endl;
			if (line.substr(pos + 13) == "Human")
			{
				//cout << "current player = human" << endl;
				setCurPlayer(human);
				setNextPlayer(computer);
			}

			else
			{
				setCurPlayer(computer);
				setNextPlayer(human);
			}
		}

		// look for color

		if (line.find("Color:") != string::npos)
		{
			// look for player type:
			size_t pos = line.find("Color:");

			//cout << line.substr(pos + 7) << endl;
			if (line.substr(pos + 7) == "Black")
			{
				//cout << "current player color = black" << endl;
				getCurPlayer()->setColor('B');
				getNextPlayer()->setColor('W');
			}

			else
			{
				getCurPlayer()->setColor('W');
				getNextPlayer()->setColor('B');
			}
		}
	}
	cout << "game state loaded." << endl;
	setResumeGame(true);
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