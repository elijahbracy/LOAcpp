#pragma once
#include <iostream>
using namespace std;

class Board 
{
public:
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
};