/*
 * Deck.cpp
 *
 *  Created on: 11.01.2017
 *      Author: Stefan
 */

#include <memory>
#include <random>
#include <stdexcept>
#include "Deck.h"
#include "Card.h"
#include "GlobalDeclarations.h"
#include "assert.h"
#include <sstream>

void Deck::AddSets(std::size_t  N)
{
	// Can only have between 1 and MAX_SETS sets.
	assert(N <= MAX_SETS);
	assert(N > 0);

	for(std::size_t i = 0; i < N; ++i)
	{
		AddCompleteSet();
	}
}

void Deck::AddCompleteSet()
{
	// Adds single cards to the deck. The cards are owned by the desk unless it is drawn.
	for( const auto & suit : SUIT)
	{
		for(const auto & face : FACE)
		{
			_cardContainer.push_back(std::move(pCard( new Card(face.first, suit))));
		}
	}
}


Deck::pCard Deck::Draw(std::size_t number)
{
	// Draw card at position number if it is within bounds and return it to the caller.
	assert(number < Size());
	assert(!_cardContainer.empty());
	auto Card =  std::move(_cardContainer.at(number));
	_cardContainer.erase(_cardContainer.begin()+number);
	return Card;
}

Deck::pCard Deck::Draw()
{
	// Draw random card from the deck
	std::default_random_engine rng(_seed);
	std::uniform_int_distribution<int> uniformDist(0, _cardContainer.size()-1);
	auto random_integer = uniformDist(rng);
	// Transfers ownership of the drawn card to the caller
	return Draw(random_integer);
}

void Deck::PrintNumCards() const
{
	std::stringstream strm;
	strm << "Cards in Deck = " << Size() << std::endl;
	console.Write(strm);
}










