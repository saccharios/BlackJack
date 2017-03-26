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
class SimulationGame : public Game{
	using Base = Game;
	using pAIPlayer = std::unique_ptr<AIPlayer_Basic>;
	using pAIPlayer_Optimal = std::unique_ptr<AIPlayer_Optimal>;
public:
	SimulationGame(std::size_t numRounds) : Game(), _numRounds(numRounds) {}
	void Setup(std::size_t N_Decks, std::size_t N_AIPlayers, double initialBalance);
	void SetWagers() override;
	bool PlayAnotherRound () override;
	void RemoveBrokePlayers() override {}; // In the simulation, players are not removed if they are broke
	void PrintStatistics();
private:
	const std::size_t _numRounds;
	std::size_t _currentRound = 0;
	static constexpr double _balanceLowLimit = 100.0 * MIN_WAGER;

};

#endif /* SIMULATIONGAME_H_ */
