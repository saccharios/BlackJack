/*
 * HandManager_Test.h
 *
 *  Created on: 28.01.2017
 *      Author: Stefan
 */

#ifndef SRC_HANDMANAGER_TEST_H_
#define SRC_HANDMANAGER_TEST_H_

#include "gtest/gtest.h"
#include "../../BlackJack/src/Deck.h"
#include "../../BlackJack/src/HandManager.h"

// Forward declaration
class Card;

class HandManagerTest : public ::testing::Test
{
private:
	const double _wager = 10.0;
	const std::size_t _numDecks = 1;
public:
	using pCard = std::unique_ptr<Card>;
	HandManagerTest() : _deck(0), _handManager (_deck, _wager, 0)
	// Use seed 0 to always draw the same card.
	// The card drawn depends only on their order in the deck.
	{
		_deck.AddSets(_numDecks);
	}
//	void SetUp()
//	{
//		Test::SetUp();
//	}

//	void TearDown()
//	{
//		Test::TearDown();
//	}
	void Run_Payouts();
	void Run_ActionDouble();
	void Run_ActionHit();
	void Run_ActionStand();
	void Run_ActionSplit();
	void Run_ActionSplit_Aces();
	void Run_Wager();
	void Run_Start();
	void Run_IsBlackJack();
	void Run_EvaluateValue();
	void Run_EvaluateBlackJack();
	void Run_EvaluateBusted();
	void Run_PutCardsBack();

private:
	Deck _deck;
	HandManager _handManager;
};
TEST_F(HandManagerTest, Payouts)
{
	Run_Payouts();
}
TEST_F(HandManagerTest, ActionDouble)
{
	Run_ActionDouble();
}
TEST_F(HandManagerTest, ActionHit)
{
	Run_ActionHit();
}
TEST_F(HandManagerTest, ActionStand)
{
	Run_ActionStand();
}
TEST_F(HandManagerTest, ActionSplit)
{
	Run_ActionSplit();
}
TEST_F(HandManagerTest, ActionSplitAces)
{
	Run_ActionSplit_Aces();
}
TEST_F(HandManagerTest, Wager)
{
	Run_Wager();
}

TEST_F(HandManagerTest, Start)
{
	Run_Start();
}
TEST_F(HandManagerTest, EvaluateValue)
{
	Run_EvaluateValue();
}
TEST_F(HandManagerTest, EvaluateBlackJack)
{
	Run_EvaluateBlackJack();
}
TEST_F(HandManagerTest, EvaluateBusted)
{
	Run_EvaluateBusted();
}
TEST_F(HandManagerTest, PutCardsBack)
{
	Run_PutCardsBack();
}



#endif /* SRC_HANDMANAGER_TEST_H_ */
