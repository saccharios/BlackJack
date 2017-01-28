/*
 * Card_Test.h
 *
 *  Created on: 28.01.2017
 *      Author: Stefan
 */

#ifndef SRC_CARD_TEST_H_
#define SRC_CARD_TEST_H_

#include "gtest/gtest.h"
#include "Card.h"
#include <string>
#include "GlobalDeclarations.h"

TEST(Card, CreateCard)
{
	// Catch exceptions thrown by card ctor
	EXPECT_NO_THROW(Card card("A","s")); // Vaild face and suit
	EXPECT_THROW(Card card("P","s"), std::invalid_argument); // False face
	EXPECT_THROW(Card card("A","l"), std::invalid_argument); // False suit
}

TEST(Card, TestSuits)
{
	// Check if all suits are assigned correctly
	for( const auto & suit : SUIT)
	{
		Card card("A", suit);
		EXPECT_EQ(suit, card.GetSuit()) << "Error assigning suit " << suit;
	}
}

TEST(Card, TestFaces)
{
	// Check if all faces and values are assignedn correctly
	for(const auto & face : FACE)
	{
		Card card(face.first, "s");
		EXPECT_EQ(face.first, card.GetFace()) << "Error assigning face " << face.first;
		EXPECT_EQ(face.second, card.GetValue()) << "Error assigning value " << face.second;

	}
}



#endif /* SRC_CARD_TEST_H_ */
