/*
 * Deck.h
 *
 *  Created on: 10.10.2016
 *      Author: Stefan
 */

#ifndef DECK_H_
#define DECK_H_

#include <cstdlib>
#include <memory>
#include <vector>
#include "Card.h"


class Deck
{
	typedef std::unique_ptr<Card> pCard;
public:

	// Class Deck is a Singleton
	static Deck & getInstance()
	{
		static Deck instance;
		return instance;
	}
	Deck() : _cardContainer(){}
	// Not allowed to copy or assign,
	Deck(Deck const &) = delete ;
	void operator=(Deck const&) = delete;

	void AddSets(std::size_t N);
	void AddCard( pCard  card) { _cardContainer.push_back(std::move(card)); }
	pCard Draw();
	pCard Draw(unsigned int number);
	void PrintNumCards() const;
	std::size_t Size() const {return _cardContainer.size();}

private:

	void AddCompleteSet();
	std::vector<pCard> _cardContainer;
};

#endif /* DECK_H_ */
