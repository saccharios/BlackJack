/*
 * Deck.cpp
 *
 *  Created on: 11.01.2017
 *      Author: Stefan
 */

#include <memory>
#include <random>
#include <chrono>
#include "Deck.h"
#include "Card.h"
#include "GlobalDeclarations.h"

void Deck::AddSets(std::size_t N)
{
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

Deck::pCard Deck::Draw()
{
	// Use the time for a new seed each time a card is darwn
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine rng(seed);
	std::uniform_int_distribution<int> uniformDist(0, _cardContainer.size()-1);
	auto random_integer = uniformDist(rng);
	// Transfers ownership of the drawn card to the caller
	return Draw(random_integer);
}
Deck::pCard Deck::Draw(unsigned int number)
{
	Deck::pCard Card;
	if(!_cardContainer.empty() && Size() > number)
	{
		Card =  std::move(_cardContainer.at(number));
		_cardContainer.erase(_cardContainer.begin()+number);
	}
	else
	{
		std::cerr << "ERROR - cannot draw card " << number << std::endl;
	}
	return Card;
}



void Deck::PrintNumCards() const
{
	std::cout << "Cards in Deck = " << Size() << std::endl;
}










