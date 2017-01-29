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
void HandManagerTest::Run_Actions()
{

}
void HandManagerTest::Run_Wager()
{
	// Test with member
	EXPECT_EQ(_wager, _handManager.GetWager());
	// But this tests needs some more values for wager, but the wager can only be set at creation
	HandManager _handManagerLow(_deck, MIN_WAGER - 1.0, 1);
	EXPECT_EQ(MIN_WAGER, _handManagerLow.GetWager());
	HandManager _handManagerHigh(_deck, MAX_WAGER + 1.0, 2);
	EXPECT_EQ(MAX_WAGER, _handManagerHigh.GetWager());

}
void HandManagerTest::Run_Start()
{

}
