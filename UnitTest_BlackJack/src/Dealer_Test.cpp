/*
 * Dealer_Test.cpp
 *
 *  Created on: 28.01.2017
 *      Author: Stefan
 */

#include "Dealer_Test.h"

void DealerTest::runStart()
{
	_dealer.Start();
	EXPECT_EQ(1u, _dealer.GetHoleCards().Size());
}
void DealerTest::runPlay()
{
	_dealer.Play();
	// Depends on the order of the cards in the deck.
	EXPECT_EQ(20u, _dealer.GetValue());
	EXPECT_EQ(5u, _dealer.GetHoleCards().Size());
	_dealer.PrintCards();
}
