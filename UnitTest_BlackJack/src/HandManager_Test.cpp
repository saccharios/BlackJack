/*
 * HandManager_Test.cpp
 *
 *  Created on: 29.01.2017
 *      Author: Stefan
 */

#include "gtest/gtest.h"
#include "HandManager_Test.h"
#include "../../BlackJack/src/GlobalDeclarations.h"
#include "../../BlackJack/src/Card.h"
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
	// Thus we can use the normal start method.
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
	for(std::size_t i = 0; i < 10; ++i)
	{
		_handManager.ActionHit();
		EXPECT_EQ(i+1u, _handManager.GetHoleCards().Size());
		if(_handManager.GetValue() > 20)
		{
			EXPECT_TRUE(_handManager.IsPlayed());
		}
		else
		{
			EXPECT_FALSE(_handManager.IsPlayed());
		}
	}
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

void HandManagerTest::Run_EvaluateBlackJack()
{// This test case is easier if the deck contains only certain cards
	Deck deck(0);
	double wager = 10.0;
	HandManager hand (deck, wager, 0);
	deck.AddCard(pCard(new Card("A","s")));
	deck.AddCard(pCard(new Card("K","s")));
	hand.Start(); // handManager now holds BlackJack
	auto payout = hand.Evaluate(true, false, 21); // Dealer also has Black Jack
	EXPECT_EQ(wager, payout);
	payout = hand.Evaluate(false, true, 22); // Dealer is busted
	EXPECT_EQ(2.5*wager, payout);
	payout = hand.Evaluate(false, false, 18); // Dealer has 18 points
	EXPECT_EQ(2.5*wager, payout);
}
void HandManagerTest::Run_EvaluateBusted()
{// This test case is easier if the deck contains only certain cards
	Deck deck(0);
	double wager = 10.0;
	HandManager hand (deck, wager, 0);
	deck.AddCard(pCard(new Card("K","s")));
	deck.AddCard(pCard(new Card("K","s")));
	deck.AddCard(pCard(new Card("6","s")));
	hand.Start(); // hand is busted
	hand.ActionHit();
	auto payout = hand.Evaluate(true, false, 21); // Dealer has Black Jack
	EXPECT_EQ(0.0, payout);
	payout = hand.Evaluate(false, true, 22); // Dealer is busted
	EXPECT_EQ(0.0, payout);
	payout = hand.Evaluate(false, false, 18); // Dealer has 18 points
	EXPECT_EQ(0.0, payout);
}
void HandManagerTest::Run_EvaluateValue()
{// This test case is easier if the deck contains only certain cards
	Deck deck(0);
	double wager = 10.0;
	HandManager hand (deck, wager, 0);
	deck.AddCard(pCard(new Card("6","s")));
	deck.AddCard(pCard(new Card("6","s")));
	hand.Start(); // hand has 12 points
	auto payout = hand.Evaluate(true, false, 21); // Dealer has Black Jack
	EXPECT_EQ(0.0, payout);
	payout = hand.Evaluate(false, true, 22); // Dealer is busted
	EXPECT_EQ(2.0*wager, payout);
	payout = hand.Evaluate(false, false, 18); // Dealer has 18 points
	EXPECT_EQ(0.0, payout);
	payout = hand.Evaluate(false, false, 12); // Dealer has 12 points
	EXPECT_EQ(1.0*wager, payout);
	payout = hand.Evaluate(false, false, 10); // Dealer has 10 points
	EXPECT_EQ(2.0*wager, payout);
}
void HandManagerTest::Run_PutCardsBack()
{
	_handManager.Start();
	_handManager.ActionHit();
	_handManager.ActionHit();
	_handManager.ActionHit();
	EXPECT_EQ(5u, _handManager.GetHoleCards().Size());
	EXPECT_EQ(_numDecks*52 - 5u, _deck.Size());
	_handManager.PutCardsBack();
	EXPECT_EQ(0u, _handManager.GetHoleCards().Size());
	EXPECT_EQ(_numDecks*52, _deck.Size());
}

void HandManagerTest::Run_GetAvailableActionSet()
{// This test case is easier if the deck contains only certain cards
	Deck deck(0);
	double wager = 10.0;
	HandManager hand (deck, wager, 0);
	deck.AddCard(pCard(new Card("6","s")));
	deck.AddCard(pCard(new Card("6","s")));
	hand.Start(); // hand has a pair
	EXPECT_EQ(ACTION_SPLIT_DOUBLE, hand.GetAvailableActionSet());
	deck.AddCard(pCard(new Card("3","s")));
	hand.ActionHit(); // hand has a pair
	EXPECT_EQ(ACTION_STANDARD, hand.GetAvailableActionSet());
	deck.AddCard(pCard(new Card("K","s")));
	deck.AddCard(pCard(new Card("6","s")));
	hand.PutCardsBack();
	hand.Start(); // hand hols Ks6s
	EXPECT_EQ(ACTION_DOUBLE, hand.GetAvailableActionSet());
}
