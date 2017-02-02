/*
 * Deck_test.h
 *
 *  Created on: 21.01.2016
 *      Author: Stefan
 */

#ifndef SRC_DECK_TEST_H_
#define SRC_DECK_TEST_H_
#include <memory>
#include "gtest/gtest.h"
#include "../../BlackJack/src/Deck.h"
#include "../../BlackJack/src/Card.h"
#include "string"
#include "../../BlackJack/src/GlobalDeclarations.h"

// Deck tests are individual unit tests and not done with macro TEST_F and a dedicated class, because removing cards
// from the deck is not allowed. All tests should start with an empty deck, thus need to declare it anyways.
TEST(Deck, AddAndRemoveOneCard)
{
	using pCard = std::unique_ptr<Card>;
	Deck deck;
	deck.AddCard(pCard(new Card("A","s")));
	EXPECT_EQ(1u, deck.Size());
	deck.Draw();
	EXPECT_EQ(0u, deck.Size());
}

TEST(Deck, RemoveOneCard_EmptyDesk)
{
	Deck deck;
	EXPECT_THROW(deck.Draw(), std::invalid_argument);
	EXPECT_THROW(deck.Draw(1), std::invalid_argument);
}

TEST(Deck, AddEigthSets)
{
	Deck deck;
	std::size_t NumDecks = 8;
	std::size_t NumCardsDeck = 52;
	deck.AddSets(NumDecks);
	EXPECT_EQ(NumDecks*NumCardsDeck, deck.Size());
	for(std::size_t i = 0; i < NumDecks*NumCardsDeck; ++i)
	{
		deck.Draw();
	}
	EXPECT_EQ(0u, deck.Size());
}
TEST(Deck, AddMAX1Sets)
{
	Deck deck;
	std::size_t NumDecks = MAX_SETS +1 ;
	std::size_t NumCardsDeck = 52;
	deck.AddSets(NumDecks);
	EXPECT_EQ(MAX_SETS*NumCardsDeck, deck.Size());
}
TEST(Deck, AddZeroSets)
{
	Deck deck;
	std::size_t NumDecks = 0;
	std::size_t NumCardsDeck = 52;
	deck.AddSets(NumDecks);
	EXPECT_EQ(NumCardsDeck, deck.Size());
}



#endif
