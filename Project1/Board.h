#pragma once
#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;

class Board 
{
public:
	Board();

	void printBoard();

	void setBoard(const char(&newBoard)[8][8]);

	const char(*getBoard())[8];

	void copyBoard(char buffBoard[][8]);

	vector<string> getPossibleMoves(char curColor);

	string generateMoveString(int originRow, int originCol, int destinationRow, int destinationCol);

	pair<string, int> gaugeMove(string move, char curColor, char opColor, int threatLevel, vector<string> opponentsMoves = {});

	void MakeMove(string move, char curColor);

	bool isValid(string move, char curColor);

	int PiecesOnLine(pair<int, int> origin, pair<int, int> destination);

	int SpacesToMove(pair<int, int> origin, pair<int, int> destination);

	pair<int, int> Slope(pair<int, int> origin, pair<int, int> destination);

	bool PiecesInWay(pair<int, int> origin, pair<int, int> destination, char curColor);

	pair<int, int> parseOrigin(string move);

	pair<int, int> parseDestination(string move);

	//void Update(vector<Player*> players); // TODO update number of pieces each player has

	int CountPieces(char color);

	int CountGroups(char color);

	void FloodFill(int row, int col, char color, vector<vector<bool>>& visited);

	map<char, int> lettersToNumbers = { {'a',0}, {'b', 1}, {'c',2}, {'d',3} , {'e',4} , {'f',5} , {'g',6} , {'h',7} }; // mapping columns to array notation
	//map<int, int> numbersTo

	char defaultBoard[8][8] = {
		{'.', 'B', 'B', 'B', 'B', 'B', '.', '.'},
		{'W', '.', '.', '.', '.', '.', 'B', 'W'},
		{'W', '.', '.', '.', '.', '.', '.', 'W'},
		{'W', '.', '.', '.', '.', '.', '.', 'W'},
		{'W', '.', '.', '.', '.', '.', '.', 'W'},
		{'W', '.', '.', '.', '.', '.', '.', 'W'},
		{'W', '.', '.', '.', '.', '.', '.', 'W'},
		{'.', '.', '.', '.', '.', '.', '.', '.'}
	};

private: 
	char board[8][8] = {
		{'.', 'B', 'B', 'B', 'B', 'B', '.', '.'},
		{'W', '.', '.', '.', '.', '.', '.', 'W'},
		{'W', '.', '.', '.', '.', '.', 'B', 'W'},
		{'W', '.', '.', '.', '.', '.', '.', 'W'},
		{'W', '.', '.', '.', '.', '.', '.', 'W'},
		{'W', '.', '.', '.', '.', '.', '.', 'W'},
		{'W', '.', '.', '.', '.', '.', '.', 'W'},
		{'.', '.', '.', '.', '.', '.', '.', '.'}
	};

	
};