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
#include "../../BlackJack/src/Card.h"
#include "../../BlackJack/src/HandManager.h"

class HandManagerTest : public ::testing::Test
{
private:
	const float _wager = 10.0;
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
	void Run_Actions();
	void Run_Wager();
	void Run_Start();

private:
	Deck _deck;
	HandManager _handManager;
};
TEST_F(HandManagerTest, Payouts)
{
	Run_Payouts();
}
TEST_F(HandManagerTest, Actions)
{
	Run_Actions();
}
TEST_F(HandManagerTest, Wager)
{
	Run_Wager();
}

TEST_F(HandManagerTest, Start)
{
	Run_Start();
}



#endif /* SRC_HANDMANAGER_TEST_H_ */
