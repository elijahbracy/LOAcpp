#pragma once
#include <iostream>
#include <map>
using namespace std;

class Board 
{
public:
	Board() 
	{
		
	}

	void printBoard() 
	{
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

	bool isValid(string move, char curColor) 
	{
		pair<int, int> origin = parseOrigin(move);
		pair<int, int> destination = parseDestination(move);

		cout << board[origin.first][origin.second];
		char originSpace = board[origin.first][origin.second];
		char destinationSpace = board[destination.first][destination.second];

		// steps must equal number of pieces on that line
		if (SpacesToMove(origin, destination) != PiecesOnLine(origin, destination))
		{
			return false;
		}

		// origin coordinate has piece that belongs to player
		if (originSpace != curColor)
		{
			return false;
		}

		// desination is empty or has enemy piece
		if (destinationSpace == curColor)
		{
			return false;
		}

		// and path between has no enemy pieces
		if (PiecesInWay(origin, destination, curColor))
		{
			return false;
		}

		return true;
		//alternatively, if origin and destination are in list of valid moves
	}

	pair<int, int> SmallerPair(pair<int, int> origin, pair<int, int> destination)
	{
		int sumOrigin = origin.first + origin.second;
		int sumDestination = destination.first + destination.second;

		return (sumOrigin < sumDestination) ? origin : destination;
	}

	int PiecesOnLine(pair<int, int> origin, pair<int, int> destination)
	{
		int numPieces = 0;

		// if 1sts are same, check row
		if (origin.first == destination.first)
		{
			int row = origin.first;
			for (int i = 0; i < 8; i++)
			{
				char curSpace = board[row][i];

				if (curSpace != '.')
				{
					numPieces++;
				}
			}
		}

		// if 2nds are same, check column
		else if (origin.second == destination.second)
		{
			int col = origin.second;
			for (int i = 0; i < 8; i++)
			{
				char curSpace = board[i][col];

				if (curSpace != '.')
				{
					numPieces++;
				}
			}
		}

		// if both different, check diagonal
		// find coordinate closest to 0, subtract difference
		// check until you get to 7
		else
		{
			int rowStep = Slope(origin, destination).first;
			int colStep = Slope(origin, destination).second;

			// start at origin, follow slope to edge
			int x = origin.first;
			int y = origin.second;

			while (x >= 0 && x < 8 && y >= 0 && y < 8)
			{
				char curSpace = board[x][y];
				if (curSpace != '.')
				{
					numPieces++;
				}
				x += rowStep;
				y += colStep;
			}

			// start at origin + 1 step in opposite direction, follow to edge going opposite direction
			x = origin.first + colStep;
			y = origin.second + rowStep;

			while (x >= 0 && x < 8 && y >= 0 && y < 8)
			{
				char curSpace = board[x][y];
				if (curSpace != '.')
				{
					numPieces++;
				}
				x += colStep;
				y += rowStep;
			}
		}

		return numPieces;
	}

	int SpacesToMove(pair<int, int> origin, pair<int, int> destination)
	{
		int rowDiff = abs(origin.first - destination.first);
		int colDiff = abs(origin.second - destination.second);

		return max(rowDiff, colDiff);
	}

	pair<int, int> Slope(pair<int, int> origin, pair<int, int> destination)
	{
		int rowStep = (destination.first - origin.first) / SpacesToMove(origin, destination);
		int colStep = (destination.second - origin.second) / SpacesToMove(origin, destination);

		return make_pair(rowStep, colStep);
	}

	bool PiecesInWay(pair<int, int> origin, pair<int, int> destination, char curColor)
	{
		//get difference in row and col coordinates
		int rowDiff = abs(origin.first - destination.first);
		int colDiff = abs(origin.second - destination.second);

		//if difference is same for row and col, moving diagonally
		// if difference is not same but one value is zero, moving vertically/horizontally
		//if difference is not same for both but both values are non-zero, invalid move
		if (rowDiff != colDiff && rowDiff != 0 && colDiff != 0)
		{
			return true;
		}

		// get number of spaces we need to move
		int steps = max(rowDiff, colDiff);

		// if steps is zero, no move being made, invalid
		if (steps == 0)
		{
			return true;
		}

		//determine direction by taking (destination - origin) / steps
		//will give 1, 0, or -1 for up, neutral or down
		int rowStep = Slope(origin, destination).first;
		int colStep = Slope(origin, destination).second;

	

		//get starting space to check (origin + a step in direction we are moving)
		int row = origin.first + rowStep;
		int col = origin.second + colStep;

		//iterate from that space to destination checking for collision
		// stop 1 before destination
		for (int i = 0; i < steps-1; i++)
		{
			char curSpace = board[row][col];
			if (curSpace != '.' && curSpace != curColor)
			{
				return true;
			}
			//move in predetermined direction
			row += rowStep;
			col += colStep;
		}
		return false;
	}

	pair<int, int> parseOrigin(string move) {
		int row = move[1] - '0'; // get int from ascii number
		row -= 1; // subtract 8 and flip sign to get proper row
		int col = lettersToNumbers[move[0]]; //use map to get column number
		cout << "coordinate of origin is: [" << row << "][" << col << ']' << endl;
		return make_pair(row, col);
	}

	pair<int, int> parseDestination(string move) {
		int row = move[5] - '0'; // get int from ascii number
		row -= 1; // subtract 8 and flip sign to get proper row
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
		{'W', '.', '.', '.', 'B', '.', '.', 'W'},
		{'W', '.', '.', '.', '.', '.', '.', 'W'},
		{'W', 'B', '.', 'B', '.', '.', '.', 'W'},
		{'.', '.', 'B', 'B', 'B', 'B', 'B', '.'}
	};


};