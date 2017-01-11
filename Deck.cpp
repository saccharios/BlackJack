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
	// Randomggenerator, copied from http://stackoverflow.com/questions/5008804/generating-random-integer-from-a-range
	std::mt19937 rng(_rd());    // random-number engine used (Mersenne-Twister in this case)
	std::uniform_int_distribution<int> uniformDist(0, Base::NumCards()-1); // guaranteed unbiased
	auto random_integer = uniformDist(rng);
	return Base::RemoveCard(random_integer);
}


void Deck::PrintNumCards()
{
	std::cout << "Cards in Deck = " << Base::NumCards() << std::endl;
}



void Deck::AddCompleteSet()
{
	for( int i = 0; i < 4;++i) // Iterate over Suits
	{
		for( int j = 0; j < 13;++j) // Iterate over Numbers
		{
			try {
				AddCard(pCard(new Card(Face[j], Suit[i])));
			}
			catch( const std::invalid_argument& e ) {
				std::cerr << e.what() << std::endl;
			}
		}
	}
}




