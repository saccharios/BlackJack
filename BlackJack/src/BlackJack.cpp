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

// TODO Write Unittest with gtest
// TODO Check where "auto" can be used
// TODO Check instantiation with auto, and () {}
// TODO Find better way for cards characteristics instead of strings
// TODO Add exception handling


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
