#include "Board.h"
#include "Round.h"
#include <string>

using namespace std;

Board::Board()
	{

	}

pair<string, int> Board::gaugeMove(string move, char curColor, char opColor, int threatLevel, vector<string> opponentsMoves)
{
	Board* buffBoard = new Board;

	copyBoard(buffBoard->board);

	//buffBoard->printBoard();
	// 
	// "test" move
	buffBoard->MakeMove(move, curColor);
	
	// if after move, total groups is 1, winning move found
	if (buffBoard->CountGroups(curColor) == 1)
	{
		return make_pair(move, 1);
	}

	// after move, check opponents moves again, see if threat level went down
	vector<pair<string, int>> opponentsMovesGauged;

	// judge each move, add it vector
	for (int i = 0; i < opponentsMoves.size(); i++)
	{
		opponentsMovesGauged.push_back(gaugeMove(opponentsMoves[i], curColor, opColor, 0));
	}

	// sort vector based on smallest int, ie, most effective move
	sort(opponentsMovesGauged.begin(), opponentsMovesGauged.end(), [](pair<string, int>& left, pair<string, int>& right) {return left.second < right.second; });

	// create default for threat level comparison
	int newThreatLevel;

	if (opponentsMovesGauged[0])

	// if opponents win is imminent, attempt thwart
[[	if (threatLevel == 1 && opponentsMovesGauged[0].second > 1)
	{
		//thwart happened
		return make_pair(move, 2);
	}
	return make_pair(move, 3);

};

void Board::copyBoard(char buffBoard[][8])
{
	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {
			buffBoard[i][j] = board[i][j];
		}
	}
};

vector<string> Board::getPossibleMoves(char curColor)
{
	vector<string> possibleMoves;

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (board[i][j] == curColor)
			{
				// iterate through every possible destination for piece
				for (int k = 0; k < 8; k++)
				{
					for (int l = 0; l < 8; l++)
					{
						string move = generateMoveString(i, j, k, l);
						
						// call isvalid on every possible move
						if (isValid(move, curColor))
						{
							//if valid, push move back into possible move vector
							possibleMoves.push_back(move);
						}
					}
				}
			}
		}
	}
	return possibleMoves;
};

string Board::generateMoveString(int originRow, int originCol, int destinationRow, int destinationCol)
{
	string move;

	// build out move string, starting with origin col char & row number, followed by "->", then destination col char and row number
	// function starts at destination 0,0 and goes to 7,7
	
	// convert origin col num to char, indexing starts at A
	move += static_cast<char>('A' + originCol);

	// add 1 to origin to since indexing starts at 1
	move += to_string(originRow + 1);

	// add ->
	move += "->";

	// add destination in same way as origin
	move += static_cast<char>('A' + destinationCol);
	move += to_string(destinationRow + 1);

	return move;

};

void Board::setBoard(const char (&newBoard)[8][8])
{
	for (int row = 0; row < 8; row++)
	{
		for (int col = 0; col < 8; col++)
		{
			board[row][col] = newBoard[row][col];
		}
	}
};

const char (*Board::getBoard())[8]
{
	return board;
}

void Board::printBoard()
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
};

void Board::MakeMove(string move, char curColor)
{
	pair<int, int> destination = parseDestination(move);
	pair<int, int> origin = parseOrigin(move);

	// update origin space
	board[origin.first][origin.second] = '.';

	// update destination space
	// if destination space empty, just make move;

	board[destination.first][destination.second] = curColor;

	// if destination space has char, decrement that players total pieces


};

bool Board::isValid(string move, char curColor)
{
	pair<int, int> origin = parseOrigin(move);
	pair<int, int> destination = parseDestination(move);

	//cout << board[origin.first][origin.second];
	char originSpace = board[origin.first][origin.second];
	char destinationSpace = board[destination.first][destination.second];

	// steps must equal number of pieces on that line
	if (SpacesToMove(origin, destination) != PiecesOnLine(origin, destination))
	{
		//cout << "steps must equal number of pieces on that line" << endl;
		return false;
	}

	// origin coordinate has piece that belongs to player
	if (originSpace != curColor)
	{
		//cout << "origin coordinate must have piece that belongs to you" << endl;
		return false;
	}

	// desination is empty or has enemy piece
	if (destinationSpace == curColor)
	{
		//cout << "destination coordinate must be empty or have enemy piece" << endl;
		return false;
	}

	// and path between has no enemy pieces
	if (PiecesInWay(origin, destination, curColor))
	{
		//cout << "path between origin and coordinate must have no enemy pieces" << endl;
		return false;
	}

	return true;
	//alternatively, if origin and destination are in list of valid moves
};

int Board::PiecesOnLine(pair<int, int> origin, pair<int, int> destination)
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
	// start at coordinate, get slope, check until 1 coordinate hits a boundry
	// back to coordinate, flip slope, check until boundry
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
};

int Board::SpacesToMove(pair<int, int> origin, pair<int, int> destination)
{
	int rowDiff = abs(origin.first - destination.first);
	int colDiff = abs(origin.second - destination.second);

	return max(rowDiff, colDiff);
};

pair<int, int> Board::Slope(pair<int, int> origin, pair<int, int> destination)
{
	int rowStep = (destination.first - origin.first) / SpacesToMove(origin, destination);
	int colStep = (destination.second - origin.second) / SpacesToMove(origin, destination);

	return make_pair(rowStep, colStep);
};

bool Board::PiecesInWay(pair<int, int> origin, pair<int, int> destination, char curColor)
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
	pair<int, int> slope = Slope(origin, destination);
	int rowStep = slope.first;
	int colStep = slope.second;



	//get starting space to check (origin + a step in direction we are moving)
	int row = origin.first + rowStep;
	int col = origin.second + colStep;

	//iterate from that space to destination checking for collision
	// stop 1 before destination
	for (int i = 0; i < steps - 1; i++)
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
};

int Board::CountPieces(char color)
{
	//iterate through board, if char is equal to color, increment num pieces
	int numPieces = 0;

	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {
			if (board[i][j] == color) {
				numPieces++;
			}
		}
	}

	return numPieces;
};

int Board::CountGroups(char color)
{
	int groups = 0;
	vector<vector<bool>> visited(8, vector<bool>(8, false));

	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {
			if (board[i][j] == color && !visited[i][j]) {
				// Found a new group
				groups++;
				// Perform flood fill to mark all connected pieces
				FloodFill(i, j, color, visited);
			}
		}
	}
	cout << "number of groups for " << color << ": " << groups << endl;
	return groups;
};

void Board::FloodFill(int row, int col, char color, vector<vector<bool>>& visited)
{
	// if space is out of bounds, piece is not the same as color, or space has been visited, return
	if (row < 0 || row >= 8 || col < 0 || col >= 8 || board[row][col] != color || visited[row][col]) {
		return;
	}
	// mark space as visited
	visited[row][col] = true;

	// recursively check adjacent spaces
	FloodFill(row - 1, col, color, visited); 
	FloodFill(row + 1, col, color, visited);
	FloodFill(row, col - 1, color, visited);
	FloodFill(row, col + 1, color, visited);
	// check diagonals
	FloodFill(row - 1, col + 1, color, visited);
	FloodFill(row + 1, col - 1, color, visited);
	FloodFill(row + 1, col + 1, color, visited);
	FloodFill(row - 1, col - 1, color, visited);
};

pair<int, int> Board::parseOrigin(string move) {
	int row = move[1] - '0'; // get int from ascii number
	row -= 1; // subtract 8 and flip sign to get proper row
	int col = lettersToNumbers[tolower(move[0])]; //use map to get column number
	//cout << "coordinate of origin is: [" << row << "][" << col << ']' << endl;
	return make_pair(row, col);
};

pair<int, int> Board::parseDestination(string move) {
	int row = move[5] - '0'; // get int from ascii number
	row -= 1; // subtract 8 and flip sign to get proper row
	int col = lettersToNumbers[tolower(move[4])]; //use map to get column number
	//cout << "coordinate of destination is: [" << row << "][" << col << ']' << endl;
	return make_pair(row, col);
};
