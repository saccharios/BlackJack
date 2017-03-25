/*
 * BlackJack.cpp
 *
 *  Created on: 10.10.2016
 *      Author: Stefan
 */
#include <memory>
#include "ConsoleGame.h"
#include "Card.h"
#include "GlobalDeclarations.h"
#include "HoleCards.h"
// TODO Write Unittest with gtest (SimulationgGame and PlayerGame)

// TODO Use make_unique instead of new. Problem: Eclipse indexer does not recoginze make_unique<T>()

int main(int argc, char ** argv)
{
	ConsoleGame game;
	game.PrintRules();
	game.AddDecks();
	game.AddHumanPlayers();
	do
	{
		game.PlayRound();
	}while ( game.PlayAnotherRound() );


	return 0;
}

