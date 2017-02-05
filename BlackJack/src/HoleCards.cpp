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
_arePair(false),
_arePairAces(false),
_numSoftAces(0),
_status(),
_cardContainer()
{}

void HoleCards::StartCards(pCard card)
{
	if(!IsEmpty())
	{
		throw std::invalid_argument( "Cannot start hand, hand is non-empty");
	}
	else{

		Reset();
		AddCard(std::move(card));
	}
}

void HoleCards::StartCards(pCard card1, pCard card2)
{
	assert(IsEmpty());//, "Cannot start hand, hand is non-empty"));
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
	// Transfer ownership to cardContainer
	 _cardContainer.push_back(std::move(card));
	CalculateValue();
	auto value = GetValue();
	if( _cardContainer.size() == 2 && value ==  21)
	{
		_status.blackJack = true;
		std::cout << "BLACK JACK!" << std::endl;
	}
	else if ( value > 21)
	{
		_status.busted = true;
	}

}

void HoleCards::CalculateValue()
{
	_status.value = 0u;
	_numSoftAces = 0u;
	for( const auto & card : _cardContainer)
	{
		_status.value += card->GetValue();
		if(card->IsAce())
		{
			++_numSoftAces;
		}
	}
	while( _status.value > 21u && _numSoftAces > 0u)
	{
		_status.value -= 10;
		--_numSoftAces;
	}
}
unsigned int HoleCards::GetValue() const
{
	return _status.value;
}

void HoleCards::Reset()
{
	_arePair = false;
	_arePairAces = false;
	_numSoftAces = 0;
	_status.Reset();
}

void HoleCards::PrintCards() const
{
	for(pCard const & card : _cardContainer)
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
	auto	Card =  std::move(_cardContainer.back());
	_cardContainer.pop_back();

	return Card;
}



