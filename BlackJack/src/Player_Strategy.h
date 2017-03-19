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
#include "PlayerHand.h"

class HumanPlayer : public Player{
	using pPlayerHand = std::unique_ptr<PlayerHand>;
public:
	HumanPlayer(Deck & deck, std::string name, double balance) : 	Player(deck, name, balance) {}

	std::string
	strategy(std::set<std::string> const & stringSet, pPlayerHand const & hand) const override
	{
		return console.ReadInAction(stringSet);
	}
};
class AIPlayer_Basic : public Player{
	using pPlayerHand = std::unique_ptr<PlayerHand>;
public:
	AIPlayer_Basic(Deck & deck, std::string name, double balance) : 	Player(deck, name, balance) {}

	// Play like the dealer
	std::string
	strategy(std::set<std::string> const & stringSet, pPlayerHand const & hand) const override
	{
	if( hand->GetValue() < 17 )
	{
		return "h";
	}
	else
	{
		return "s";
	}
	}

};

class AIPlayer_Conservative : public Player{
	using pPlayerHand = std::unique_ptr<PlayerHand>;
public:
	AIPlayer_Conservative(Deck & deck, std::string name, double balance) : 	Player(deck, name, balance) {}

	// Always stand
	std::string
	strategy(std::set<std::string> const & stringSet, pPlayerHand const & hand) const override
	{
		return "s";
	}

};
class AIPlayer_Aggressive : public Player{
	using pPlayerHand = std::unique_ptr<PlayerHand>;
public:
	AIPlayer_Aggressive(Deck & deck, std::string name, double balance) : 	Player(deck, name, balance) {}

	// Always hit
	std::string
	strategy(std::set<std::string> const & stringSet, pPlayerHand const & hand) const override
	{
		return "h";
	}

};
class AIPlayer_Optimal: public Player{
	using pPlayerHand = std::unique_ptr<PlayerHand>;
public:
	AIPlayer_Optimal(Deck & deck, std::string name, double balance) : 	Player(deck, name, balance) {}

	// Always hit
	std::string
	strategy(std::set<std::string> const & stringSet, pPlayerHand const & hand) const override
	{
		return "s"; // TODO Implement optimal strategy
	}

};

#endif /* SRC_PLAYER_STRATEGY_H_ */
