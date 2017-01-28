/*
 * Dealer_Test.h
 *
 *  Created on: 28.01.2017
 *      Author: Stefan
 */

#ifndef SRC_DEALER_TEST_H_
#define SRC_DEALER_TEST_H_
#include "../../BlackJack/src/Dealer.h"
#include "../../BlackJack/src/Deck.h"
#include "../../BlackJack/src/Card.h"

class DealerTest : public ::testing::Test
{
public:
	typedef std::unique_ptr<Card> pCard;
	DealerTest() : _deck(0), _dealer(_deck) {}
	void SetUp()
	{
		Test::SetUp();
		Deck deck(0);
	}

	void TearDown()
	{
		Test::TearDown();
	}


private:
	Deck _deck;
	Dealer _dealer;

};


TEST(Dealer, Start)
{
	typedef std::unique_ptr<Card> pCard;
	Deck deck(0);
	Dealer dealer(deck);
	deck.AddCard(pCard(new Card("2","s")));
	deck.AddCard(pCard(new Card("3","s")));
	deck.AddCard(pCard(new Card("4","s")));
	deck.AddCard(pCard(new Card("5","s")));
	deck.AddCard(pCard(new Card("6","s")));
	deck.AddCard(pCard(new Card("7","s")));
	deck.AddCard(pCard(new Card("8","s")));

	dealer.Start();
	EXPECT_EQ(1u, dealer.GetHoleCards().Size());
}

TEST(Dealer, Play)
{
	typedef std::unique_ptr<Card> pCard;
	Deck deck(0);
	Dealer dealer(deck);
	deck.AddCard(pCard(new Card("2","s")));
	deck.AddCard(pCard(new Card("3","s")));
	deck.AddCard(pCard(new Card("4","s")));
	deck.AddCard(pCard(new Card("5","s")));
	deck.AddCard(pCard(new Card("6","s")));
	deck.AddCard(pCard(new Card("7","s")));
	deck.AddCard(pCard(new Card("8","s")));

	dealer.Play();
	EXPECT_EQ(20u, dealer.GetValue());
	EXPECT_EQ(5u, dealer.GetHoleCards().Size());
	EXPECT_EQ(2u,deck.Size());

}
TEST(Dealer, ActionHit)
{
	typedef std::unique_ptr<Card> pCard;
	Deck deck(0);
	Dealer dealer(deck);
	auto N = 2u;
	for(auto i = 0u; i < N; ++i)
	{
		deck.AddCard(pCard(new Card("A","s")));
	}
	EXPECT_EQ(N,deck.Size());
	dealer.ActionHit();
	EXPECT_EQ(1u, dealer.GetHoleCards().Size());
	EXPECT_EQ(N - 1, deck.Size());
}


TEST(Dealer, PutCardsBack)
{
	typedef std::unique_ptr<Card> pCard;
	Deck deck(0);
	Dealer dealer(deck);
	auto N = 52u;
	for(auto i = 0u; i < N; ++i)
	{
		deck.AddCard(pCard(new Card("A","s")));
	}
	EXPECT_EQ(N,deck.Size());
	for(auto i = 0u; i < N; ++i)
	{
		dealer.ActionHit();
	}
	EXPECT_EQ(N, dealer.GetHoleCards().Size());
	EXPECT_EQ(0u, deck.Size());
	dealer.PutCardsBack();
	EXPECT_EQ(0u, dealer.GetHoleCards().Size());
	EXPECT_EQ(N, deck.Size());
}
TEST(Dealer, BlackJack)
{
	typedef std::unique_ptr<Card> pCard;
	Deck deck(0);
	Dealer dealer(deck);
	deck.AddCard(pCard(new Card("A","s")));
	dealer.ActionHit();
	EXPECT_EQ(11u,dealer.GetValue());
	deck.AddCard(pCard(new Card("K","s")));
	dealer.ActionHit();
	EXPECT_TRUE(dealer.HasBlackJack());
}
TEST(Dealer, IsBusted)
{
	typedef std::unique_ptr<Card> pCard;
	Deck deck(0);
	Dealer dealer(deck);
	deck.AddCard(pCard(new Card("K","s")));
	deck.AddCard(pCard(new Card("K","s")));
	deck.AddCard(pCard(new Card("K","s")));
	dealer.ActionHit();
	dealer.ActionHit();
	dealer.ActionHit();
	EXPECT_TRUE(dealer.IsBusted());
}
TEST(Dealer, GetValue)
{
	typedef std::unique_ptr<Card> pCard;
	Deck deck(0);
	Dealer dealer(deck);
	deck.AddCard(pCard(new Card("A","s")));
	dealer.ActionHit();
	EXPECT_EQ(11u,dealer.GetValue());
	deck.AddCard(pCard(new Card("K","s")));
	dealer.ActionHit();
	EXPECT_EQ(21u,dealer.GetValue());
	deck.AddCard(pCard(new Card("2","s")));
	dealer.ActionHit();
	EXPECT_EQ(13u,dealer.GetValue());
	deck.AddCard(pCard(new Card("9","s")));
	dealer.ActionHit();
	EXPECT_EQ(22u,dealer.GetValue());
}


#endif /* SRC_DEALER_TEST_H_ */
