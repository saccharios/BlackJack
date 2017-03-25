/*
 * SimulationGame.cpp
 *
 *  Created on: 25.03.2017
 *      Author: Stefan
 */

#include "SimulationGame.h"
#include "PlayerStrategy.h"
void
SimulationGame::Setup(std::size_t N_Sets, std::size_t N_AIPlayers)
{
	_deck.AddSets(N_Sets);
	for( std::size_t i = 0; i < N_AIPlayers; ++i )
	{
		std::ostringstream stm ;
		stm << "AIPlayer_" << i ;
		_players.push_back(std::move(pAIPlayer_Optimal(new AIPlayer_Optimal(_deck, stm.str(), MAX_INIT_BALANCE, _dealer))));
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

bool SimulationGame::PlayAnotherRound () const
{
	return false;
}
