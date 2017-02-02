/*
 * HoleCards_Test.h
 *
 *  Created on: 28.01.2017
 *      Author: Stefan
 */

#ifndef SRC_HOLECARDS_TEST_H_
#define SRC_HOLECARDS_TEST_H_
#include "gtest/gtest.h"
#include "../../BlackJack/src/HoleCards.h"
#include "../../BlackJack/src/Card.h"

TEST(HoleCards, AddAndRemoveOneCard)
{
	using pCard = std::unique_ptr<Card>;
	HoleCards holeCards;
	holeCards.AddCard(pCard(new Card("A","s")));
	EXPECT_EQ(1u, holeCards.Size());
	holeCards.RemoveLastCard();
	EXPECT_EQ(0u, holeCards.Size());
}
//TEST(HoleCards, RemoveCard_DEATH)
//{
//	HoleCards holeCards;
//	// Remove on card from empty hole cards
//	EXPECT_DEATH(holeCards.RemoveLastCard(),"");
//}
TEST(HoleCards, OneStartCard)
{
	using pCard = std::unique_ptr<Card>;
	HoleCards holeCards;
	// Add 1 Card and then invoke StartCard(Card), expect throw
	holeCards.AddCard(pCard(new Card("A","s")));
	EXPECT_THROW( holeCards.StartCards(pCard(new Card("K","s"))), std::invalid_argument);
	EXPECT_EQ(1u, holeCards.Size());
	// Remove Card and test StartCard(Card) with empty container.
	holeCards.RemoveLastCard();
	EXPECT_NO_THROW( holeCards.StartCards(pCard(new Card("A","s"))));
	EXPECT_EQ(1u, holeCards.Size());
}

//TEST(HoleCards, TwoStartCard_Death)
//{
//	using pCard = std::unique_ptr<Card>;
//	HoleCards holeCards;
//	// Add 1 Card and then invoke StartCard(Card, Card), expect throw
//	holeCards.AddCard(pCard(new Card("A","s")));
//	EXPECT_DEATH( holeCards.StartCards(pCard(new Card("K","s")),pCard(new Card("Q","s"))),"");
//}

TEST(HoleCards, TwoStartCard)
{
	using pCard = std::unique_ptr<Card>;
	HoleCards holeCards;
	EXPECT_NO_THROW( holeCards.StartCards(pCard(new Card("K","s")),pCard(new Card("Q","s"))));
	EXPECT_EQ(2u, holeCards.Size());
}
TEST(HoleCards, GetValue)
{
	using pCard = std::unique_ptr<Card>;
	HoleCards holeCards;
	auto valueSum(0u);
	// Test Value for all cards of spades, handle the ace special
	for(const auto & face : FACE)
	{
		holeCards.AddCard(pCard(new Card(face.first,"s")));
		valueSum += face.second;
		if( face.first == "A" && valueSum > 21)
		{
			valueSum -= 10;
		}
		EXPECT_EQ(valueSum, holeCards.GetValue());
	}
	// By now value is busted
	EXPECT_TRUE(holeCards.AreBusted());
	holeCards.Reset();
	EXPECT_FALSE(holeCards.AreBusted());
}

TEST(HoleCards, Pair)
{
	using pCard = std::unique_ptr<Card>;
	HoleCards holeCards;
	holeCards.StartCards(pCard(new Card("K","s")),pCard(new Card("K","d")));
	EXPECT_TRUE(holeCards.ArePair());
}
TEST(HoleCards, PairAces)
{
	using pCard = std::unique_ptr<Card>;
	HoleCards holeCards;
	holeCards.StartCards(pCard(new Card("A","s")),pCard(new Card("A","d")));
	EXPECT_TRUE(holeCards.ArePair());
	EXPECT_TRUE(holeCards.ArePairAces());
	holeCards.Reset();
	EXPECT_FALSE(holeCards.ArePair());
	EXPECT_FALSE(holeCards.ArePairAces());
}
TEST(HoleCards, BlackJack)
{
	using pCard = std::unique_ptr<Card>;
	HoleCards holeCards;
	holeCards.StartCards(pCard(new Card("A","s")),pCard(new Card("K","s")));
	EXPECT_TRUE(holeCards.AreBlackJack());
	EXPECT_EQ(21u, holeCards.GetValue());
	holeCards.Reset();
	EXPECT_FALSE(holeCards.AreBlackJack());
}

TEST(HoleCards, SoftAces)
{
	using pCard = std::unique_ptr<Card>;
	HoleCards holeCards;
	// Add 21 Aces
	for( auto i = 0u; i < 21u; ++i)
	{
		holeCards.AddCard(pCard(new Card("A","s")));
		if( i < 11 )
		{
			EXPECT_EQ(11u + i, holeCards.GetValue()) <<" at " << i;
		}
		else
		{
			EXPECT_EQ(i+1, holeCards.GetValue()) << " at " << i;
		}
	}
}



#endif /* SRC_HOLECARDS_TEST_H_ */
