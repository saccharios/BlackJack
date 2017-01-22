/*
 * Deck_test.h
 *
 *  Created on: 21.01.2016
 *      Author: Stefan
 */

#ifndef DECK_TEST_H_
#define DECK_TEST_H_
#include <memory>
#include "gtest/gtest.h"
#include "Deck.h"
#include "Card.h"
#include "string"

TEST(Deck, AddOneCard)
{
	typedef std::unique_ptr<Card> pCard;
	Deck & deck = Deck::getInstance();
	std::string face = "5";
	std::string suit = "s";
	pCard card(new Card(face ,  suit ));

	deck.AddCard(std::move(card));
	EXPECT_EQ(1u, deck.Size());

}

#endif
