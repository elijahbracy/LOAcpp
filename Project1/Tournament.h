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

			cout << "Player ";
			p1->displayName();
			cout << " scored " << p1->tournamentScore << " points." << endl;


			cout << "Player ";
			p2->displayName();
			cout << " scored " << p2->tournamentScore << " points." << endl;
		}

		// is p1 wins
		else if (p1->roundsWon > p2->roundsWon)
		{
			cout << "Player ";
			p1->displayName();
			cout << " won the tournament!" << endl;

			cout << "They won " << p1->roundsWon << " rounds." << endl;


			cout << "Player ";
			p1->displayName();
			cout << " scored " << p1->tournamentScore << " points." << endl;


			cout << "Player ";
			p2->displayName();
			cout << " scored " << p2->tournamentScore << " points." << endl;
		}

		// else p2 won
		else
		{
			cout << "Player ";
			p2->displayName();
			cout << " won the tournament!" << endl;

			cout << "They won " << p2->roundsWon << " rounds." << endl;

			cout << "Player ";
			p2->displayName();
			cout << " scored " << p2->tournamentScore << " points." << endl;


			cout << "Player ";
			p1->displayName();
			cout << " scored " << p1->tournamentScore << " points." << endl;
		}
	};

	void announceTournamentScores()
	{

	}
private:
};