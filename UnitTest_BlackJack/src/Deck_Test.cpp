/*
 * Deck_Tets.cpp
 *
 *  Created on: 02.02.2017
 *      Author: Stefan
 */

#include "Deck_Test.h"
#include <memory>
#include "gtest/gtest.h"
#include "../../BlackJack/src/Deck.h"
#include "../../BlackJack/src/Card.h"
#include "string"
#include "../../BlackJack/src/GlobalDeclarations.h"



void DeckTest::Run_AddAndRemoveOneCard()
{
	_deck.AddCard(pCard(new Card("A","s")));
	EXPECT_EQ(1u, _deck.Size());
	_deck.Draw();
	EXPECT_EQ(0u, _deck.Size());
}

void DeckTest::Run_RemoveOneCard_EmptyDesk_DEATH()
{
	EXPECT_DEATH(_deck.Draw(), "");
	EXPECT_DEATH(_deck.Draw(1), "");
}

void DeckTest::Run_AddEigthSets()
{
	std::size_t NumDecks = 8;
	std::size_t NumCardsDeck = 52;
	_deck.AddSets(NumDecks);
	EXPECT_EQ(NumDecks*NumCardsDeck, _deck.Size());
	for(std::size_t i = 0; i < NumDecks*NumCardsDeck; ++i)
	{
		_deck.Draw();
	}
	EXPECT_EQ(0u, _deck.Size());
}
void DeckTest::Run_AddMAX1Sets()
{
	std::size_t NumDecks = MAX_SETS +1 ;
	std::size_t NumCardsDeck = 52;
	_deck.AddSets(NumDecks);
	EXPECT_EQ(MAX_SETS*NumCardsDeck, _deck.Size());
}
void DeckTest::Run_AddZeroSets()
{
	std::size_t NumDecks = 0;
	std::size_t NumCardsDeck = 52;
	_deck.AddSets(NumDecks);
	EXPECT_EQ(NumCardsDeck, _deck.Size());
}
