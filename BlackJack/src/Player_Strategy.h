/*
 * AIPlayer.h
 *
 *  Created on: 16.03.2017
 *      Author: Stefan
 */

#ifndef SRC_PLAYER_STRATEGY_H_
#define SRC_PLAYER_STRATEGY_H_

#include "Player.h"
#include <string>
#include "console.h"
#include "GlobalDeclarations.h"

class HumanPlayer : public Player{
public:
	HumanPlayer(Deck & deck, std::string name, double balance) : 	Player(deck, name, balance) {}

	std::string
	strategy(std::set<std::string> const & stringSet) const override
	{
		return console.ReadInAction(stringSet);
	}
};
class AIPlayer : public Player{
public:
	AIPlayer(Deck & deck, std::string name, double balance) : 	Player(deck, name, balance) {}



	std::string
	strategy(std::set<std::string> const & stringSet) const override
	{
		return Player::PlayBasicStrategy();
	}

};

#endif /* SRC_PLAYER_STRATEGY_H_ */
