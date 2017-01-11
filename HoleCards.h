/*
 * HoleCards.h
 *
 *  Created on: 15.10.2016
 *      Author: Stefan
 */

#ifndef HOLECARDS_H_
#define HOLECARDS_H_

#include "CardCollection.h"
#include <memory>

class HoleCards : public CardCollection{
	typedef CardCollection Base;
	typedef std::unique_ptr<Card> pCard;
public:
	HoleCards();
	void StartCards(pCard card);
	void StartCards(pCard card1, pCard card2);
	void AddCard(pCard card);
	unsigned int GetValue() const;
	bool const & AreBlackJack() const { return _areBlackJack; }
	bool const & ArePair() const { return _arePair; }
	bool const & ArePairAces() const { return _arePairAces; }
	bool const & AreBusted() const { return _areBusted; }
	void Reset();
	void PrintCards() const;
	void PrintNumCards() const;



private:
	bool _areBlackJack;
	bool _arePair;
	bool _arePairAces;
	bool _areBusted;

};

#endif /* HOLECARDS_H_ */
