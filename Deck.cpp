/*
 * Deck.cpp
 *
 *  Created on: 11.01.2017
 *      Author: Stefan
 */

#include "Deck.h"
#include "Card.h"
#include <memory>
#include <random>

void Deck::AddSets(std::size_t N)
{
	for(std::size_t i = 0; i < N; ++i)
	{
		AddCompleteSet();
	}
}

Deck::pCard Deck::Draw()
{
	// Random generator, copied from http://stackoverflow.com/questions/5008804/generating-random-integer-from-a-range
	std::mt19937 rng(_rd());    // random-number engine used (Mersenne-Twister in this case)
	std::uniform_int_distribution<int> uniformDist(0, Base::NumCards()-1); // guaranteed unbiased
	auto random_integer = uniformDist(rng);
	return Base::RemoveCard(random_integer);
}


void Deck::PrintNumCards() const
{
	std::cout << "Cards in Deck = " << Base::NumCards() << std::endl;
}



void Deck::AddCompleteSet()
{
	for( const auto & suit : Suit)
	{
		for(const auto & face : Face)
		{
			AddCard(pCard(new Card(face.first, suit)));
		}
	}
}




