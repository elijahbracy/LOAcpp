#include "Board.h"
#include "Round.h"
#include "Human.h"
#include "Computer.h"
#include "Tournament.h"

int main() {
	Board* board = new Board;
	Round round;
	Human* p1 = new Human;
	Player* p2 = new Computer;
	Tournament tournament;
	vector<Player*> players = { p1, p2 };

	//ask to resume game on startup
	if (round.resumeGame())
	{
		// parameters probably unnecessary
		round.loadGameState(board, p1, p2);
	}

	//game loop
	do {

		//if first turn and not continuing game, initialize board and round
		if (round.getTurnsPlayed() == 0 && round.getResumeGame() == false)
		{
			//initialize round
			round.roundStart(p1, p2);

			// initialize board
			board->resetBoard();
		}

		// print board
		//board->printBoard();

		//display current player
		cout << "Current player: ";
		round.getCurPlayer()->displayName();
		cout << " Color: " << round.getCurPlayer()->getColor() << endl;

		// have player make their turn
		round.getCurPlayer()->play(board);

		// for each player, update pieces on board
		for (int i = 0; i < players.size(); i++)
		{
			players[i]->UpdateNumPieces(board);
		}

		// check for win
		if (board->CountGroups(round.getCurPlayer()->getColor()) == 1)
		{
			// score round
			round.Score(round.getCurPlayer(), round.getNextPlayer()->getPiecesOnBoard());

			// announce winner
			round.announceRoundWin(round.getCurPlayer(), round.getNextPlayer());

			// ask to play again
			round.PlayAgain();

			// set turns played to 0
			round.setTurnsPlayed(0);

			// if play again, start gameloop over
			if (round.getPlayAgain())
			{
				continue;
			}

			// else, announce tournament result
			break;
		}

		//increment turns played
		round.setTurnsPlayed(round.getTurnsPlayed() + 1);

		// ask if they would like to suspend game
		// parameters unneeccessacry
		round.suspendGame();

		// get next player
		round.SwitchPlayers();

	} while (!round.getSuspend());

	// announce tournament ending stats, skip if suspending game
	if (!round.getSuspend())
	{
		tournament.announceTournamentResult(round.getCurPlayer(), round.getNextPlayer());
	}


}