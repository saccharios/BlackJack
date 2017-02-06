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

// TODO Write Unittest with gtest (Player, Game)
// TODO Check where "auto" can be used
// TODO Check instantiation with auto, and () {}
// TODO Add exception handling, use assert() where possible
// TODO Use make_unique instead of new. Problem: Eclipse indexer does not recoginze make_unique<T>()
// TODO Where needed, replace handmanager by hand, only the player has a vector of hands, which is the handmanager
int main(int argc, char ** argv)
{

	Game::PrintRules();
	Game & game = Game::getInstance();
	game.AddDecks();
	game.AddPlayers();
	do
	{
		game.PlayRound();
	}while ( game.PlayAnotherRound() );


	return 0;
}
