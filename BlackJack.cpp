/*
 * BlackJack.cpp
 *
 *  Created on: 10.10.2016
 *      Author: Stefan
 */
#include "Game.h"
#include <memory>
#include "Card.h"
#include "HoleCards.h"


// TODO Write Unittest with gtest
// TODO check for const correctness


void basicHoleCardsUnittest();
int main() {
	Game::PrintRules();
	Game & game = Game::getInstance();
	game.AddDecks();
	game.AddPlayers();
	game.SetBalances();
	do
	{
		game.PlayRound();
	}while ( game.PlayAnotherRound() );
//
//	basicHoleCardsUnittest();

	return 0;
}


void basicHoleCardsUnittest()
{
	HoleCards holeCards;
	holeCards.AddCard(std::unique_ptr<Card>(new Card("A","s")));
	holeCards.PrintCards();
	holeCards.AddCard(std::unique_ptr<Card>(new Card("A","d")));
	holeCards.PrintCards();
	holeCards.AddCard(std::unique_ptr<Card>(new Card("A","c")));
	holeCards.PrintCards();
	holeCards.AddCard(std::unique_ptr<Card>(new Card("K","c")));
	holeCards.PrintCards();
	try {
		holeCards.AddCard(std::unique_ptr<Card>(new Card("P","c")));
	}
	catch( const std::invalid_argument& e ) {
		std::cerr << e.what() << std::endl;
	}
	holeCards.PrintCards();
	holeCards.AddCard(std::unique_ptr<Card>(new Card("3","c")));
	holeCards.PrintCards();
}
