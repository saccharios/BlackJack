/*
 * Deck.cpp
 *
 *  Created on: 11.01.2017
 *      Author: Stefan
 */

#include <memory>
#include <random>
#include "Deck.h"
#include "Card.h"
#include "GlobalDeclarations.h"
#include <chrono>

void Deck::AddSets(std::size_t N)
{
	for(std::size_t i = 0; i < N; ++i)
	{
		AddCompleteSet();
	}
}

Deck::pCard Deck::Draw()
{
	// Use the time for a new seed each time a card is darwn
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine rng(seed);
	std::uniform_int_distribution<int> uniformDist(0, Base::NumCards()-1);
	auto random_integer = uniformDist(rng);
	return Base::RemoveCard(random_integer);
}


void Deck::PrintNumCards() const
{
	std::cout << "Cards in Deck = " << Base::NumCards() << std::endl;
}



void Deck::AddCompleteSet()
{
	for( const auto & suit : SUIT)
	{
		for(const auto & face : FACE)
		{
			AddCard(pCard(new Card(face.first, suit)));
		}
	}
}




