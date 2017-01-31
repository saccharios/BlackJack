/*
 * HandManager_Test.cpp
 *
 *  Created on: 29.01.2017
 *      Author: Stefan
 */

#include "gtest/gtest.h"
#include "HandManager_Test.h"
#include "../../BlackJack/src/GlobalDeclarations.h"

void HandManagerTest::Run_Payouts()
{
	EXPECT_EQ(_wager, _handManager.PayoutPush ());
	EXPECT_EQ(0.0f, _handManager.PayoutLoose ());
	EXPECT_EQ(_wager*2.0f, _handManager.PayoutWin ());
	EXPECT_EQ(_wager*2.5f, _handManager.PayoutBlackJack ());
}
void HandManagerTest::Run_ActionDouble()
{
	_handManager.ActionDouble();
	EXPECT_EQ(1u, _handManager.GetHoleCards().Size());
	EXPECT_TRUE(_handManager.IsPlayed());
	EXPECT_EQ(_wager*2.0f, _handManager.GetWager() );
}
void HandManagerTest::Run_ActionSplit()
{
	// To test spliting it does not matter whether it is a pair or not, the mechanism is the same.
	// Thus we can use the normal start method
	_handManager.Start();
	auto newHand = _handManager.ActionSplit();
	EXPECT_EQ(2u, _handManager.GetHoleCards().Size());
	EXPECT_FALSE(_handManager.IsPlayed());
	EXPECT_EQ(2u, newHand->GetHoleCards().Size());
	EXPECT_EQ(_wager, newHand->GetWager());
	EXPECT_EQ(_handManager.GetHandNumber() + 1, newHand->GetHandNumber());
	EXPECT_FALSE(newHand->IsPlayed());

}

void HandManagerTest::Run_ActionSplit_Aces()
{
	// This is a special case and can best be tested with a special deck.
	// Thus the deck and handManager are not the member variables
	Deck deck;
	deck.AddCard(pCard(new Card("A","s")));
	deck.AddCard(pCard(new Card("A","d")));

	HandManager handManager(deck,_wager, 0);
	handManager.Start();
	// Add more cards to the deck, so spliting is ok
	deck.AddCard(pCard(new Card("2","d")));
	deck.AddCard(pCard(new Card("3","d")));
	auto newHand = handManager.ActionSplit();
	EXPECT_TRUE( handManager.IsPlayed());
	EXPECT_TRUE(newHand->IsPlayed());

}
void HandManagerTest::Run_ActionHit()
{
	_handManager.ActionHit();
	EXPECT_EQ(1u, _handManager.GetHoleCards().Size());
}
void HandManagerTest::Run_ActionStand()
{
	_handManager.ActionStand();
	EXPECT_TRUE(_handManager.IsPlayed());
}
void HandManagerTest::Run_Wager()
{
	// First test with member
	EXPECT_EQ(_wager, _handManager.GetWager());
	// But this tests needs some more values for wager, but the wager can only be set at creation
	HandManager _handManagerLow(_deck, MIN_WAGER - 1.0, 1);
	EXPECT_EQ(MIN_WAGER, _handManagerLow.GetWager());
	HandManager _handManagerHigh(_deck, MAX_WAGER + 1.0, 2);
	EXPECT_EQ(MAX_WAGER, _handManagerHigh.GetWager());
}
void HandManagerTest::Run_Start()
{
	_handManager.Start();
	EXPECT_EQ(2u, _handManager.GetHoleCards().Size());
	EXPECT_FALSE(_handManager.IsPlayed());
}
void HandManagerTest::Run_IsBlackJack()
{ // This test case is easier if the deck contains only {As, Ks}
	Deck deck(0);
	double wager = 10.0;
	HandManager handManager (deck, wager, 0);
	deck.AddCard(pCard(new Card("A","s")));
	deck.AddCard(pCard(new Card("K","s")));
	handManager.Start();
	EXPECT_TRUE(handManager.IsBlackJack());
}
