/*
 * SimulationGame.cpp
 *
 *  Created on: 25.03.2017
 *      Author: Stefan
 */

#include "SimulationGame.h"
#include "PlayerStrategy.h"
void
SimulationGame::Setup(std::size_t N_Sets, std::size_t N_AIPlayers, double initialBalance)
{
	_deck.AddSets(N_Sets);

	if(initialBalance < _balanceLowLimit)
	{
		initialBalance = _balanceLowLimit;
	}

	for( std::size_t i = 0; i < N_AIPlayers; ++i )
	{
		std::ostringstream stm ;
		stm << "AIPlayer_" << i ;
		_players.push_back(std::move(pAIPlayer_Optimal(new AIPlayer_Optimal(_deck, stm.str(), initialBalance, _dealer))));
	}

}

void
SimulationGame::SetWagers()
{
	double wager = 1.0;
	console.WriteString("-------Set Wagers------\n");
	for(auto const & player : _players)
	{
		player->SetWager(wager);
	}
}

bool SimulationGame::PlayAnotherRound ()
{
	for(auto const & player : _players)
	{
		if(player->GetBalance() < _balanceLowLimit)
		{
			player->ResetBalance();
			std::stringstream strm;
			strm << player->GetName()<< "'s balance is too low. Resetting to " << player->GetBalance() << "\n";
			console.Write(strm);
		}
	}

	return (++_currentRound < _numRounds);
}



void SimulationGame::PrintStatistics()
{
	for(auto const & player : _players)
	{
		std::cout << "Player total investment = " << player->GetTotalInvestedBalance() << std::endl;
	}


}
