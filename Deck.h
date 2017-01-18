/*
 * Deck.h
 *
 *  Created on: 10.10.2016
 *      Author: Stefan
 */

#ifndef DECK_H_
#define DECK_H_

#include "CardCollection.h"
#include "Card.h"
#include <cstdlib>
#include <memory>
#include <random>


class Deck : public CardCollection
{
	typedef CardCollection Base;
	typedef std::unique_ptr<Card> pCard;
public:

	// Class Deck is a Singleton
	static Deck & getInstance()
	{
		static Deck instance;
		return instance;
	}
	Deck(Deck const &) = delete ;
	void operator=(Deck const&) = delete;

	void AddSets(std::size_t N);
	pCard Draw();
	pCard  Draw(int number) { return Base::RemoveCard(number); }
	void PrintNumCards() const;

private:
	Deck() {}
	void AddCompleteSet();

	std::random_device _rd; // only used once to initialise (seed) engine
};

#endif /* DECK_H_ */
