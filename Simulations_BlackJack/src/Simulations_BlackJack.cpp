/*
 * Simulations_BlackJack.cpp
 *
 *  Created on: 21.03.2017
 *      Author: Stefan
 */


// TODO Make always build upon click run, ctrl f11 and in console c/c++ unit run
// Use Scons (Sconsolidate) for building three different builds in one project.
#include <memory>
#include "../../BlackJack/src/Game.h"
#include "../../BlackJack/src/Card.h"
#include "../../BlackJack/src/GlobalDeclarations.h"
#include "../../BlackJack/src/HoleCards.h"

int main(int argc, char ** argv)
{
	Game game;
	game.Simulation_Setup(8,1);

	int N_Simulation_Steps = 4;
	for(int i = 0; i < N_Simulation_Steps; ++i)
	{
		game.Simulation_PlayRound();
		// TODO Add statistics for first decision of player.
		// TODO Add mechanic to restart the game if player is broke but N_Simulation_Steps is not done yet.
		// Simulation does not print to the console. Maybe, it should not print the game, but only some statistics at the end to a file.
	}

	return 0;
}

