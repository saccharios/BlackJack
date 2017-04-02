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

