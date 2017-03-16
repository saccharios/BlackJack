/*
 * BlackJack.cpp
 *
 *  Created on: 10.10.2016
 *      Author: Stefan
 */
#include <memory>
#include "Game.h"
#include "Card.h"
#include "GlobalDeclarations.h"
#include "HoleCards.h"
// TODO Write Unittest with gtest (Game.h)
// TODO EV calculation for "always hit" "always stand" "dealer" "optimal" strategies. Do this in a unit test, so the game can be adapted, s.t. it no longer uses any user console input.
// TODO Use make_unique instead of new. Problem: Eclipse indexer does not recoginze make_unique<T>()

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

