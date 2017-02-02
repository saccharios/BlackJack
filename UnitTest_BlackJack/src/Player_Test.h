/*
 * Player_Test.h
 *
 *  Created on: 28.01.2017
 *      Author: Stefan
 */

#ifndef SRC_PLAYER_TEST_H_
#define SRC_PLAYER_TEST_H_


#include "gtest/gtest.h"
#include "../../BlackJack/src/Player.h"
#include "../../BlackJack/src/Deck.h"

class PlayerTest : public ::testing::Test
{
private:
	const double _initBalance = 10.0;
	const std::size_t _numDecks = 1;
	const std::string _name = "Player_A";
public:
	using pCard = std::unique_ptr<Card>;
	PlayerTest() : _deck(0), _player(_deck, _name, _initBalance)
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
	void Run_Create();

private:
	Deck _deck;
	Player _player;
};
TEST_F(PlayerTest, Create)
{
	Run_Create();
}






#endif /* SRC_PLAYER_TEST_H_ */
