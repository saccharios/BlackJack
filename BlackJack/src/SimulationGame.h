/*
 * SimulationGame.h
 *
 *  Created on: 25.03.2017
 *      Author: Stefan
 */

#ifndef SIMULATIONGAME_H_
#define SIMULATIONGAME_H_

#include "Game.h"
#include "PlayerStrategy.h"
#include <ostream>

class SimulationGame : public Game{
	using Base = Game;
	using pAIPlayer_Basic = std::unique_ptr<AIPlayer_Basic>;
//	using pAIPlayer_Conservative = std::unique_ptr<AIPlayer_Conservative>;
//	using pAIPlayer_Aggressive = std::unique_ptr<AIPlayer_Aggressive>;
//	using pAIPlayer_Optimal = std::unique_ptr<AIPlayer_Optimal>;
public:

	struct Setup {
		std::size_t N_Simulation_Steps;
		std::size_t N_Sets;
		double initialBalance;
		std::size_t N_Basic_AIPlayers;
		std::size_t N_Conservative_AIPlayers;
		std::size_t N_Aggressive_AIPlayers;
		std::size_t N_Optimal_AIPlayers;
	};

	SimulationGame(Setup setup);
	void SetWagers() override;
	bool PlayAnotherRound () override;
	void RemoveBrokePlayers() override {}; // In the simulation, players are not removed if they are broke
	void PrintStatistics(std::ostream & ostrm);
	void Simulate();
private:
	const std::size_t _simulationRounds;
	std::size_t _currentRound = 0;
	static constexpr double _balanceLowLimit = 100.0 * MIN_WAGER;
	static constexpr double _wager = MIN_WAGER;

};

#endif /* SIMULATIONGAME_H_ */
