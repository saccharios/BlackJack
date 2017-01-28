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
