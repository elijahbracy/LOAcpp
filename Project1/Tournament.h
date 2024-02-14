#pragma once


class Tournament
{
public:
	Tournament() {};

	void announceTournamentResult(Player* p1, Player* p2)
	{
		// if tie
		if (p1->roundsWon == p2->roundsWon)
		{
			cout << "Tournament ended in a draw, both players won " << p1->roundsWon << " rounds." << endl;
			cout << "Player " << p1->color << " scored " << p1->score << " points." << endl;
			cout << "Player " << p2->color << " scored " << p2->score << " points." << endl;
		}

		// is p1 wins
		else if (p1->roundsWon > p2->roundsWon)
		{
			cout << "Player " << p1->color << " won the tournament!" << endl;
			cout << "They won " << p1->roundsWon << " rounds." << endl;
			cout << "Player " << p1->color << " scored " << p1->score << " points." << endl;
			cout << "Player " << p2->color << " scored " << p2->score << " points." << endl;
		}

		// else p2 won
		else
		{
			cout << "Player " << p2->color << " won the tournament!" << endl;
			cout << "They won " << p2->roundsWon << " rounds." << endl;
			cout << "Player " << p2->color << " scored " << p2->score << " points." << endl;
			cout << "Player " << p1->color << " scored " << p1->score << " points." << endl;
		}
	};
private:
};