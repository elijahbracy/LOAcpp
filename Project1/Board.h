#pragma once

#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

class Board {
public:
    Board() {};

    void printBoard();

    void setBoard(const char(&newBoard)[8][8]);

    const char(*getBoard())[8];

    vector<string> getPossibleMoves(char curColor);

    void copyBoard(char buffBoard[][8]);

    string generateMoveString(int originRow, int originCol, int destinationRow, int destinationCol);

    bool isWinningMove(string move, char curColor);

    bool isThwart(string move, char curColor, char opponentColor);

    bool isBlock(string move, char curColor, char opponentColor);

    bool isCapture(string move, char curColor, char opponentColor);

    bool isConnectingGroups(string move, char curColor);

    bool isCondensingGroups(string move, char curColor);

    bool isStall(string move, char curColor, char opponentColor);

    void MakeMove(string move, char curColor);

    bool isValid(string move, char curColor);

    int PiecesOnLine(pair<int, int> origin, pair<int, int> destination);

    int SpacesToMove(pair<int, int> origin, pair<int, int> destination);

    pair<int, int> Slope(pair<int, int> origin, pair<int, int> destination);

    bool PiecesInWay(pair<int, int> origin, pair<int, int> destination, char curColor);

    pair<int, int> parseOrigin(string move);

    pair<int, int> parseDestination(string move);

    int CountPieces(char color);

    int CountGroups(char color);

    void FloodFill(int row, int col, char color, vector<vector<bool>>& visited);

    void resetBoard();

private:

    // Private member variables
    char board[8][8];
    map<char, int> lettersToNumbers = { {'a',0}, {'b', 1}, {'c',2}, {'d',3} , {'e',4} , {'f',5} , {'g',6} , {'h',7} };
    char defaultBoard[8][8] = {
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
