/*
 * Deck_test.h
 *
 *  Created on: 21.01.2016
 *      Author: Stefan
 */

#ifndef SRC_DECK_TEST_H_
#define SRC_DECK_TEST_H_
#include "gtest/gtest.h"
#include "../../BlackJack/src/Deck.h"

class DeckTest : public ::testing::Test
{
public:
	using pCard = std::unique_ptr<Card>;
//	void SetUp()
//	{
//		Test::SetUp();
//	}

//	void TearDown()
//	{
//		Test::TearDown();
//	}
	void Run_AddAndRemoveOneCard();
	void Run_RemoveOneCard_EmptyDesk_DEATH();
	void Run_AddEigthSets();
	void Run_AddMAX1Sets();
	void Run_AddZeroSets();


private:
	Deck _deck;

};


TEST_F(DeckTest, AddAndRemoveOneCard)
{
	Run_AddAndRemoveOneCard();
}
//TEST_F(DeckTest, RemoveOneCard_EmptyDesk)
//{
//	Run_RemoveOneCard_EmptyDesk_DEATH();
//}
TEST_F(DeckTest, AddEigthSets)
{
	Run_AddEigthSets();
}
TEST_F(DeckTest, AddMAX1Sets)
{
	Run_AddMAX1Sets();
}
TEST_F(DeckTest, AddZeroSets)
{
	Run_AddZeroSets();
}



#endif
