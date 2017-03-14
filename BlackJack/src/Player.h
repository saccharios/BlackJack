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
#include "PlayerHand.h"

// Forward declaration to avoid #include
class Deck;

class Player {
	using pPlayerHand = std::unique_ptr<PlayerHand>;
public:

	Player(Deck & deck, std::string name, double balance);
	// Not allowed to copy or assign
	Player (Player const & player) = delete;
	Player & operator= (const Player & other) = delete;

	void Start();
	void Play();
	void PlayOneHand(pPlayerHand const & hand);
	void PlayAction(std::string action, pPlayerHand const & hand);
	std::string PlayBasicStrategy() const;
	std::set<std::string> GetAvailableActionSet(std::set<std::string> const & actionSet) const;
	void Evaluate(	bool const & dealerHasBlackJack, bool const & dealerIsBusted, unsigned int const & dealerValue);
	void PutCardsBack();
	void SetWagerUser ();
	void SetWager (double const & wager);
	void PrintWager () const;
	double const & GetBalance () const;
	void PrintBalance () const;
	std::string const & GetName() const;
	void PrintName () const;
	void Hit(pPlayerHand const & hand);
	void Split(pPlayerHand const & hand);
	void Double(pPlayerHand const & hand);
	void Stand(pPlayerHand const & hand);
	void AddToBalance(double const & value);
	void SubtractFromBalance(double const & value);
	std::size_t GetNumHands() {return _handManager.size();}
	void AddHand(pPlayerHand hand);

private:
	double _balance;
	double _orignialWager;
	Deck & _deck;
	std::vector<pPlayerHand> _handManager;
	std::string _name;
};




#endif /* PLAYER_H_ */
