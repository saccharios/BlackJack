/*
 * Simulations_BlackJack.cpp
 *
 *  Created on: 21.03.2017
 *      Author: Stefan
 */


// TODO Make always build upon click run, ctrl f11 and in console c/c++ unit run

#include <memory>
#include "../../BlackJack/src/Game.h"
#include "../../BlackJack/src/Card.h"
#include "../../BlackJack/src/GlobalDeclarations.h"
#include "../../BlackJack/src/HoleCards.h"

int main(int argc, char ** argv)
{
	Game game;
	game.PrintRules();
	game.AddDecks();
	game.AddHumanPlayers();
	game.AddAIPlayers();
	do
	{
		game.PlayRound();
	}while ( game.PlayAnotherRound() );


	return 0;
}

