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
#include <chrono>
#include "Card.h"



class Deck
{
	typedef std::unique_ptr<Card> pCard;
public:
	Deck() : _cardContainer(){}
	Deck(unsigned int seed ) : _cardContainer(), _seed(seed){}
	// Not allowed to copy or assign,
	Deck(Deck const &) = delete ;
	void operator=(Deck const&) = delete;

	void AddSets(std::size_t N);
	void AddCard( pCard  card) { _cardContainer.push_back(std::move(card)); }
	pCard Draw();
	pCard Draw(unsigned int number);
	void PrintNumCards() const;
	std::size_t Size() const {return _cardContainer.size();}
	void SetSeed(unsigned int seed) { _seed = seed; }

private:
	void AddCompleteSet();
	std::vector<pCard> _cardContainer;
	unsigned int _seed = std::chrono::system_clock::now().time_since_epoch().count();
};

#endif /* DECK_H_ */
