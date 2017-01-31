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

void Deck::AddSets(std::size_t  N)
{
	// The calling function must make sure that N is not negative (which results in a high integer for size_t type)
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
			_cardContainer.push_back(std::move(pCard(new Card(face.first, suit))));
		}
	}
}


Deck::pCard Deck::Draw(std::size_t number)
{
	if( number >= Size() || _cardContainer.empty())
	{
		throw std::invalid_argument("ERROR - Card to draw exceeds index");
		return nullptr;
	}
	else
	{
		Deck::pCard Card = nullptr;
		Card =  std::move(_cardContainer.at(number));
		_cardContainer.erase(_cardContainer.begin()+number);
		return Card;
	}
}

Deck::pCard Deck::Draw()
{
	std::default_random_engine rng(_seed);
	std::uniform_int_distribution<int> uniformDist(0, _cardContainer.size()-1);
	auto random_integer = uniformDist(rng);
	// Transfers ownership of the drawn card to the caller
	return Draw(random_integer);
}
// TODO Maybe add function DrawAce()?



void Deck::PrintNumCards() const
{
	std::cout << "Cards in Deck = " << Size() << std::endl;
}










