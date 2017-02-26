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
// TODO Write Unittest with gtest (Game)
// TODO Use make_unique instead of new. Problem: Eclipse indexer does not recoginze make_unique<T>()
// TODO Where needed, replace "handmanager" by "hand", only the player has a vector of hands, which is the handmanager

int main(int argc, char ** argv)
{
	Game game;
	game.PrintRules();
	game.AddDecks();
	game.AddPlayers();
	do
	{
		game.PlayRound();
	}while ( game.PlayAnotherRound() );


	return 0;
}

