/*
 * Dealer_Test.cpp
 *
 *  Created on: 28.01.2017
 *      Author: Stefan
 */

#include "Dealer_Test.h"
#include "../../BlackJack/src/Card.h"
void DealerTest::Run_Start()
{
	_dealer.Start();
	EXPECT_EQ(1u, _dealer.GetHoleCards().Size());
}
void DealerTest::Run_Play()
{
	_dealer.Play();
	// Depends on the order of the cards in the deck.
	EXPECT_EQ(20u, _dealer.GetValue());
	EXPECT_EQ(5u, _dealer.GetHoleCards().Size());
	_dealer.PrintCards();
}
void DealerTest::Run_ActionHit()
{

	_dealer.ActionHit();
	EXPECT_EQ(1u, _dealer.GetHoleCards().Size());
	EXPECT_EQ(_numDecks*52u - 1, _deck.Size());
}


void DealerTest::Run_PutCardsBack()
{
	_dealer.ActionHit();
	EXPECT_EQ(1u, _dealer.GetHoleCards().Size());
	EXPECT_EQ(_numDecks*52u - 1u, _deck.Size());
	_dealer.PutCardsBack();
	EXPECT_EQ(0u, _dealer.GetHoleCards().Size());
	EXPECT_EQ(_numDecks*52u, _deck.Size());
}
void DealerTest::Run_BlackJack()
{ // This test case is easier if the deck contains only {As, Ks}
	Deck deck(0);
	Dealer dealer(deck);
	deck.AddCard(pCard(new Card("A","s")));
	deck.AddCard(pCard(new Card("K","s")));
	dealer.Start();
	dealer.ActionHit();
	EXPECT_TRUE(dealer.HasBlackJack());
}
void DealerTest::Run_IsBusted()
{
	for(auto i = 0u; i < 7u; ++i)
	{
		_dealer.ActionHit();
	}
	EXPECT_TRUE(_dealer.IsBusted());
}
void DealerTest::Run_GetValue()
{
	auto sum = 0u;
	// Draw cards from 2 to K an check value
	for(auto i = 0u; i < 13u; ++i)
	{
		if( i < 8)
		{
			sum += i+2;
		}
		else if( i == 8 )
		{
			sum += 1u;
		}
		else
		{
			sum += 10u;
		}
		_dealer.ActionHit();
		EXPECT_EQ(sum,_dealer.GetValue()) << "i = " << i;
	}

}
