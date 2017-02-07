/*
 * HoleCards.cpp
 *
 *  Created on: 11.01.2017
 *      Author: Stefan
 */
#include <memory>
#include <iostream>
#include <stdexcept>
#include "assert.h"
#include "HoleCards.h"
#include "Card.h"

HoleCards::HoleCards():
_areBlackJack(false),
_arePair(false),
_arePairAces(false),
_areBusted(false),
_value(0),
_numSoftAces(0),
_cardContainer()
{}

void HoleCards::StartCards(pCard card)
{
	// Start method for the dealer. Can only start the hand is empty.
	assert(IsEmpty());
	Reset();
	AddCard(std::move(card));
}

void HoleCards::StartCards(pCard card1, pCard card2)
{
	// Start method for the player. Can only start if the hand if it is empty.
	// Save if the two start hands are paired or even paired aces
	assert(IsEmpty());
	Reset();
	// Check for a pair at start:
	if ( card1->GetFace() == card2->GetFace())
	{
		_arePair = true;
		if ( card1->IsAce())
		{
			_arePairAces = true;
		}
	}

	AddCard(std::move(card1));
	AddCard(std::move(card2));
}

void HoleCards::AddCard(pCard card)
{
	// Adds card to the container and evaluates if it is blackjack or busted
	_cardContainer.push_back(std::move(card));
	CalculateValue();
	auto value = GetValue();
	if( _cardContainer.size() == 2u && value ==  21u)
	{
		_areBlackJack = true;
		std::cout << "BLACK JACK!" << std::endl;
	}
	else if ( value > 21u)
	{
		_areBusted = true;
	}

}

void HoleCards::CalculateValue()
{
	// Calculates the value of the cards in the container.
	// Stores the number of soft aces.
	_value = 0u;
	_numSoftAces = 0u;
	for( auto const & card : _cardContainer)
	{
		_value += card->GetValue();
		if(card->IsAce())
		{
			++_numSoftAces; // All aces are counted as soft
		}
	}
	// If the values is above 21 and there are soft aces,
	// transform as many soft aces into hard aces.
	while( _value > 21u && _numSoftAces > 0u)
	{
		_value -= 10;
		--_numSoftAces;
	}
}
unsigned int HoleCards::GetValue() const
{
	return _value;
}

void HoleCards::Reset()
{
	_areBlackJack = false;
	_arePair = false;
	_arePairAces = false;
	_areBusted = false;
	_value = 0;
	_numSoftAces = 0;
}

void HoleCards::PrintCards() const
{
	for(auto const & card : _cardContainer)
	{
		card->Print();
	}

	if( AreBlackJack() )
	{
		std::cout << ", you have BLACKJACK."<<std::endl;;
	}
	else if (AreBusted())
	{
		std::cout <<" you are BUSTED (" << GetValue() <<")."<<std::endl;;
	}
	else
	{
		std::cout << ", value is ";
		if( _numSoftAces > 0)
		{
			std::cout << "soft ";
		}
		std::cout << GetValue() << "."<<std::endl;
	}
}

void HoleCards::PrintNumCards() const
{
	std::cout << "You have = " << _cardContainer.size() <<" Cards" << std::endl;
}

HoleCards::pCard HoleCards::RemoveLastCard()
{
	assert(!IsEmpty());
	auto Card =  std::move(_cardContainer.back());
	_cardContainer.pop_back();

	return Card;
}



