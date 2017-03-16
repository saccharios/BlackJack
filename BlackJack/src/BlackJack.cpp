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
// TODO Write Unittest with gtest (Game) (that would be then a simulation)
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

