#include "Computer.h"

using namespace std;

void Computer::play(Board* board)
{
	// print board before making move
	board->printBoard();

	// fisrt iteration, just do random moves
	vector<string> moves = board->getPossibleMoves(this->color);

	// need to know if opponents next move is win
	// first need to know opponents color
	char opponentColor;
	if (this->color == 'W')
	{
		opponentColor = 'B';
	}
	else
	{
		opponentColor = 'W';
	}

	// get opponents possible moves and see if win is imminent
	vector<string> opponentMoves = board->getPossibleMoves(opponentColor);

	// vector to hold all moves and their effectiveness
	vector<pair<string, int>> opponentsMovesGauged;

	// judge each move, add it vector
	for (int i = 0; i < opponentMoves.size(); i++)
	{
		opponentsMovesGauged.push_back(board->gaugeMove(opponentMoves[i], opponentColor, this->color, 0));
	}

	// sort vector based on smallest int, ie, most effective move
	sort(opponentsMovesGauged.begin(), opponentsMovesGauged.end(), [](pair<string, int>& left, pair<string, int>& right) {return left.second < right.second; });
	
	
	// take first move from list
	//board->MakeMove(moves[0], this->color);

	// switch statement to provide "best" move
	// 
	// winning is priority, winning tournament is based on rounds won only, round only cares about having 1 group, what is point of points?
	
	for (int i = 0; i < moves.size(); i++)
	{
		board->gaugeMove(moves[i], this->color, opponentColor, opponentsMovesGauged[0].second);
	}
	// if cannot win, thwarting should be next, ie delaying the opponents win by at least 1 turn to give oppurtunity to win
	// 
	// connecting groups should be another strategy, making it easier for computer to win
	// 
	// capture can be next
	//

	// print board to reflect move
	board->printBoard();
};