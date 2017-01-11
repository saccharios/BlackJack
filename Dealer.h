/*
 * Dealer.h
 *
 *  Created on: 15.10.2016
 *      Author: Stefan
 */

#ifndef DEALER_H_
#define DEALER_H_

#include <memory>
#include "HoleCards.h"
#include "Deck.h"

class Dealer {
	typedef std::unique_ptr<Card> pCard;
public:

	Dealer(Deck & deck);
	void Start();
	void Play();
	void ActionHit();
	void PutCardsBack();
	bool const & IsBusted () const { return _holeCards.AreBusted(); }
	bool const & HasBlackJack() const { return _holeCards.AreBlackJack(); }
	unsigned int GetValue () const { return _holeCards.GetValue(); }
	void PrintCards() const;

private:
	Deck & _deck;
	HoleCards _holeCards;

};

#endif /* DEALER_H_ */