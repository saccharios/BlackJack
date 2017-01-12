/*
 * HandManager.h
 *
 *  Created on: 07.01.2017
 *      Author: Stefan
 */

#ifndef HANDMANAGER_H_
#define HANDMANAGER_H_

#include "HoleCards.h"
#include "Card.h"
#include <memory>
#include "Deck.h"

// The HandManager is a wrapper Class for the HoleCards for a Player.
// Note that a Dealer is not a Player, as a Player has many more options available.
// In comparison this Class lets you set wagers on HoleCards, evaluate the payout,
// keeps track whether a player can keep playing these HoleCards.
class HandManager {
	typedef std::unique_ptr<Card> pCard;
public:
	HandManager (Deck & deck, float const & wager, std::size_t const & handNumber);

	// Not allowed to copy or assign
	HandManager (HandManager const & player) = delete;
	HandManager & operator= (const HandManager & other) = delete;

	void Start();
	void Start( pCard card1 );
	bool IsFirstAction() const { return (_holeCards.NumCards() == 2); }
	void ActionSplit();
	void ActionDouble();
	void ActionHit();
	void ActionStand();
	void SetWager(float const & wager) { _wager = wager; }
	float const & GetWager() const { return _wager; }
	void PrintCards() const { _holeCards.PrintCards(); }
	unsigned int GetValue() const { return _holeCards.GetValue(); }
	bool const & IsPair() const { return _holeCards.ArePair(); }
	bool const & IsPairAces() const { return _holeCards.ArePairAces(); }
	bool const & IsBusted() const { return _holeCards.AreBusted(); }
	bool const & IsBlackJack();
	bool IsEmpty() const { return _holeCards.IsEmpty(); }
	pCard RemoveLastCard() { return _holeCards.RemoveLastCard(); }
	void AddCard( pCard  card) { _holeCards.AddCard(std::move(card)); }
	void PrintNumCards() const { _holeCards.PrintNumCards(); }
	float PayoutPush ();
	float PayoutLoose ();
	float PayoutWin ();
	float PayoutBlackJack ();
	std::size_t const & GetHandNumber() const { return _handNumber; }
	void PrintHandNumber() const;
	bool const & IsPlayed() const { return _isPlayed; }

private:
	Deck & _deck;
	HoleCards _holeCards;
	float _wager;
	const std::size_t _handNumber;
	bool _isPlayed;

};


#endif /* HANDMANAGER_H_ */
