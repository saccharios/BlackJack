/*
 * Card_Test.h
 *
 *  Created on: 28.01.2017
 *      Author: Stefan
 */

#ifndef SRC_CARD_TEST_H_
#define SRC_CARD_TEST_H_

#include "gtest/gtest.h"
#include "../../BlackJack/src/Card.h"
#include <string>
#include "../../BlackJack/src/GlobalDeclarations.h"

//TEST(Card, CreateCard_Face_DEATH)
//{
//	EXPECT_DEATH(Card card("P","s"),""); // False face
//}
//TEST(Card, CreateCard_Suit_DEATH)
//{
//	EXPECT_DEATH(Card card("A","l"),""); // False suit
//}

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
	// Check if all faces and values are assigned correctly
	for(const auto & face : FACE)
	{
		Card card(face.first, "s");
		EXPECT_EQ(face.first, card.GetFace()) << "Error assigning face " << face.first;
		EXPECT_EQ(face.second, card.GetValue()) << "Error assigning value " << face.second;
	}
}



#endif /* SRC_CARD_TEST_H_ */
