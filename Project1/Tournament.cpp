#pragma once
#include "Tournament.h"


void Tournament::announceTournamentResult(Player* p1, Player* p2)
{
	// if tie
	if (p1->getRoundsWon() == p2->getRoundsWon())
	{
		cout << "Tournament ended in a draw, both players won " << p1->getRoundsWon() << " rounds." << endl;

		cout << "Player ";
		p1->displayName();
		cout << " scored " << p1->getTournamentScore() << " points." << endl;


		cout << "Player ";
		p2->displayName();
		cout << " scored " << p2->getTournamentScore() << " points." << endl;
	}

	// is p1 wins
	else if (p1->getRoundsWon() > p2->getRoundsWon())
	{
		cout << "Player ";
		p1->displayName();
		cout << " won the tournament!" << endl;

		cout << "They won " << p1->getRoundsWon() << " rounds." << endl;


		cout << "Player ";
		p1->displayName();
		cout << " scored " << p1->getTournamentScore() << " points." << endl;


		cout << "Player ";
		p2->displayName();
		cout << " scored " << p2->getTournamentScore() << " points." << endl;
	}

	// else p2 won
	else
	{
		cout << "Player ";
		p2->displayName();
		cout << " won the tournament!" << endl;

		cout << "They won " << p2->getRoundsWon() << " rounds." << endl;

		cout << "Player ";
		p2->displayName();
		cout << " scored " << p2->getTournamentScore() << " points." << endl;


		cout << "Player ";
		p1->displayName();
		cout << " scored " << p1->getTournamentScore() << " points." << endl;
	}
};