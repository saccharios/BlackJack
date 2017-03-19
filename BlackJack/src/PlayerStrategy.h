/*
 * PayerStrategy.h
 *
 *  Created on: 16.03.2017
 *      Author: Stefan
 */

#ifndef SRC_PLAYERSTRATEGY_H_
#define SRC_PLAYERSTRATEGY_H_

#include "Player.h"
#include <string>
#include "console.h"
#include "GlobalDeclarations.h"
#include "PlayerHand.h"
#include "Dealer.h"

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
	AIPlayer_Optimal(Deck & deck, std::string name, double balance, Dealer & dealer) : 	Player(deck, name, balance), _dealer(dealer) {}

	std::string
	strategy(std::set<std::string> const & stringSet, pPlayerHand const & hand) const override
	{

		return strategy_optimal(stringSet, hand, _dealer.GetValue());
	}
	// Optimal strategy depends on the first card of the dealer.
	std::string
	strategy_optimal(std::set<std::string> const & stringSet, pPlayerHand const & hand, unsigned int dealerValue) const
	{
		return "s";
	}


private:
	Dealer & _dealer;
};

#endif /* SRC_PLAYERSTRATEGY_H_ */
