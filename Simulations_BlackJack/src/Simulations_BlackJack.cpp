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

	for(int i = 0; i < 4; ++i)
	{
		game.Simulation_PlayRound();

	}

	return 0;
}

