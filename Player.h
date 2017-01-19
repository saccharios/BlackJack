/*
 * Player.h
 *
 *  Created on: 15.10.2016
 *      Author: Stefan
 */

#ifndef PLAYER_H_
#define PLAYER_H_
#include <memory>
#include <set>
#include "HoleCards.h"
#include "Card.h"
#include "HandManager.h"
#include "Deck.h"
class Player {
	typedef std::unique_ptr<Card> pCard;
	typedef std::unique_ptr<HandManager> pHandManager;
public:

	Player(Deck & deck, std::string name);
	Player (Player const & player) = delete;
	Player & operator= (const Player & other) = delete;

	void Start();
	void Play();
	std::string PlayBasicStrategy();
	std::set<std::string> GetAvailableActionSet(pHandManager const & currentHand);
	void Evaluate(	bool const & dealerHasBlackJack, bool const & dealerIsBusted, unsigned int const & dealerValue);
	void PrintCards() const;
	void PutCardsBack();
	void SetWager ();
	void PrintWager () const;
	void SetBalance();
	float const & GetBalance () const;
	void PrintBalance () const;
	std::string const & GetName() const;
	void PrintName () const;

private:
	float _balance;
	float _orignialWager;
	Deck & _deck;
	std::vector<pHandManager> _handManager;
	std::string _name;

	// The actions of a player are identified by a string
	const std::set<std::string> ACTION_SPLIT_DOUBLE{"h","s","d","p"};
	const std::set<std::string> ACTION_DOUBLE{"h","s","d"};
	const std::set<std::string> ACTION_STANDARD{"h","s"};

};




#endif /* PLAYER_H_ */
