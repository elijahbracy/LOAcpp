#include "Player.h"

using namespace std;

void Player::UpdateNumPieces(Board* board)
{
	this->totalPieces = board->CountPieces(this->getColor());
	//cout << "total num of " << this->color << " pieces: " << this->totalPieces << endl;
};

