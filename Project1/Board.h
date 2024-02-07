#pragma once
#include <iostream>
#include <map>
using namespace std;

class Board 
{
public:
	Board() {
		
	}
	void printBoard() {
		cout << " +-----------------+" << endl;
		for (int row = 7; row >= 0; row--)
		{
			cout << row + 1 << "| ";
			for (int col = 0; col < 8; col++)
			{
				cout << board[row][col] << " ";
			}
			cout << '|' << endl;
		}
		cout << " +-----------------+" << endl;
		cout << "   A B C D E F G H" << endl;
	}

	

	bool isValid(string move, Player* curPlayer) {
		pair<int, int> origin = parseOrigin(move);
		pair<int, int> destination = parseDestination(move);

		// if origin coordinate has piece that belongs to player
		// and desination is empty or has enemy piece
		// and path between has no enemy pieces
		// 
		//char(*boardData)[8] = board->getBoard(); // get board data, pointer to array of char arrays
		cout << board[origin.first][origin.second];
		char originSpace = board[origin.first][origin.second];
		char destinationSpace = board[destination.first][destination.second];
		if (originSpace == curPlayer->color && destinationSpace != curPlayer->color)
		{
			//iterate through spaces in between origin and destination looking for opponents pieces

		}
		
		//alternatively, if origin and destination are in list of valid moves
	}

	pair<int, int> parseOrigin(string move) {
		int row = move[1] - '0'; // get int from ascii number
		row = -(row - 8); // subtract 8 and flip sign to get proper row
		int col = lettersToNumbers[move[0]]; //use map to get column number
		cout << "coordinate of origin is: [" << row << "][" << col << ']' << endl;
		return make_pair(row, col);
	}

	pair<int, int> parseDestination(string move) {
		int row = move[5] - '0'; // get int from ascii number
		row = -(row - 8); // subtract 8 and flip sign to get proper row
		int col = lettersToNumbers[move[4]]; //use map to get column number
		cout << "coordinate of destination is: [" << row << "][" << col << ']' << endl;
		return make_pair(row, col);
	}

	map<char, int> lettersToNumbers = { {'a',0}, {'b', 1}, {'c',2}, {'d',3} , {'e',4} , {'f',5} , {'g',6} , {'h',7} }; // mapping columns to array notation
	//map<int, int> numbersTo

private: 
	char board[8][8] = {
		{'.', 'B', 'B', 'B', 'B', 'B', 'B', '.'},
		{'W', '.', '.', '.', '.', '.', '.', 'W'},
		{'W', '.', '.', '.', '.', '.', '.', 'W'},
		{'W', '.', '.', '.', '.', '.', '.', 'W'},
		{'W', '.', '.', '.', '.', '.', '.', 'W'},
		{'W', '.', '.', '.', '.', '.', '.', 'W'},
		{'W', '.', '.', '.', '.', '.', '.', 'W'},
		{'.', 'B', 'B', 'B', 'B', 'B', 'B', '.'}
	};


};