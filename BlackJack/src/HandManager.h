/*
 * HandManager.h
 *
 *  Created on: 07.01.2017
 *      Author: Stefan
 */

#ifndef HANDMANAGER_H_
#define HANDMANAGER_H_

#include <memory>
#include "HoleCards.h"
#include "Card.h"
#include "Deck.h"

// The HandManager is a wrapper class for the hole cards for a player.
// Note that a dealer is not a player, as a player has more options available.
// A dealer also has hole cards. In addition, this class lets you set wagers
// on hole cards, evaluate the payout, keeps track whether a player can keep playing
// and evaluates possible user actions.
class HandManager {
	using pCard = std::unique_ptr<Card>;
public:
	HandManager (Deck & deck, float const & wager, std::size_t const & handNumber);

	// Not allowed to copy or assign, because it contains a card container (which has unique_ptrs)
	HandManager (HandManager const & player) = delete;
	HandManager & operator= (const HandManager & other) = delete;

	void Start();
	void Start( pCard card1 );
	bool IsFirstAction() const { return (_holeCards.Size() == 2); }
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
