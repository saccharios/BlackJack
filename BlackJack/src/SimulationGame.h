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
	void Setup(std::size_t N_Decks, std::size_t N_AIPlayers);
	void SetWagers() override;
	bool PlayAnotherRound () const override;
};

#endif /* SIMULATIONGAME_H_ */
