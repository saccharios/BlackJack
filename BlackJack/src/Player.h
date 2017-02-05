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
#include "Card.h"
#include "HandManager.h"

// Forward declaration to avoid #include
class Deck;

class Player {
	using pHandManager = std::unique_ptr<HandManager>;
public:

	Player(Deck & deck, std::string name, double balance);
	// Not allowed to copy or assign
	Player (Player const & player) = delete;
	Player & operator= (const Player & other) = delete;

	void Start();
	void Play();
	void PlayOneHand(pHandManager const & hand);
	void PlayAction(std::string action, pHandManager const & hand);
	std::string PlayBasicStrategy();
	std::set<std::string> GetAvailableActionSet(pHandManager const & currentHand);
	void Evaluate(	bool const & dealerHasBlackJack, bool const & dealerIsBusted, unsigned int const & dealerValue);
	void PrintCards() const;
	void PutCardsBack();
	void SetWagerUser ();
	void SetWager (double const & wager);
	void PrintWager () const;
	double const & GetBalance () const;
	void PrintBalance () const;
	std::string const & GetName() const;
	void PrintName () const;
	void Hit(pHandManager const & hand);
	void Split(pHandManager const & hand);
	void Double(pHandManager const & hand);
	void Stand(pHandManager const & hand);
	void AddToBalance(double const & value);
	void SubtractFromBalance(double const & value);
	std::size_t GetNumHands() {return _handManager.size();}
	void AddHand(pHandManager hand);

private:
	void EvaluateOneHand(pHandManager const & hand,
			bool const & dealerHasBlackJack,
			bool const & dealerIsBusted,
			unsigned int const & dealerValue);
	double _balance;
	double _orignialWager;
	Deck & _deck;
	std::vector<pHandManager> _handManager;
	std::string _name;

	// The actions of a player are identified by a string
	const std::set<std::string> ACTION_SPLIT_DOUBLE{"h","s","d","p"};
	const std::set<std::string> ACTION_DOUBLE{"h","s","d"};
	const std::set<std::string> ACTION_STANDARD{"h","s"};

};




#endif /* PLAYER_H_ */
