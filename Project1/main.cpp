#include "Board.h"
#include "Round.h"
#include "Human.h"
#include "Tournament.h"

int main() {
	Board *board = new Board;
	Round round;
	Human *p1 = new Human;
	Human *p2 = new Human;
	Tournament tournament;
	
	// added for further modularity of how many players in a game, just 2 will be used for now
	vector<Player*> players = { p1, p2 };

	//ask to resume game on startup
	if (round.resumeGame())
	{
		round.loadGameState(board, p1, p2);
	}

	//game loop
	do {
		//if first turn and not continuing game, initialize board and round
		if (round.turnsPlayed == 0 && round.resumingGame == false)
		{
			//initialize round
			round.roundStart(p1, p2);

			// initialize board
			board->setBoard(board->defaultBoard);
		}

		// print board
		board->printBoard();

		// have player make their turn
		round.curPlayer->play(board);

		// for each player, update pieces on board
		for (int i = 0; i < players.size(); i++)
		{
			players[i]->UpdateNumPieces(board);
		}

		// check for win
		if (board->CountGroups(round.curPlayer->color) == 1)
		{
			// score round
			round.Score(round.curPlayer, round.nextPlayer->totalPieces);

			// announce winner
			round.announceRoundWin(round.curPlayer, round.nextPlayer);

			// ask to play again
			round.PlayAgain();

			// set turns played to 0
			round.turnsPlayed = 0;

			// if play again, start gameloop over
			if (round.playAgain)
			{
				continue;
			}

			// else, announce tournament result
			break;
		}

		//increment turns played
		round.turnsPlayed += 1;

		// ask if they would like to suspend game
		round.suspendGame(board, p1, p2);

		// get next player
		round.nextPlayer = round.GetNextPlayer(players, round.nextPlayer);

	} while (round.playAgain);

	// announce tournament ending stats, skip if suspending game
	if (!round.suspend)
	{
		tournament.announceTournamentResult(round.curPlayer, round.nextPlayer);
	}
	

}