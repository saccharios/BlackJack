/*
 * HoleCards.cpp
 *
 *  Created on: 11.01.2017
 *      Author: Stefan
 */
#include <memory>
#include <iostream>
#include "HoleCards.h"
#include <stdexcept>
#include "assert.h"

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

//	if(!IsEmpty())
//	{
//		throw std::invalid_argument( "Cannot start hand, hand is non-empty");
//	}
//	else{
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
//	}
}

void HoleCards::AddCard(pCard card)
{
	// Transfer ownership to cardContainer
	 _cardContainer.push_back(std::move(card));
	CalculateValue();
	auto value = GetValue();
	if( _cardContainer.size() == 2 && value ==  21)
	{
		_areBlackJack = true;
		std::cout << "BLACK JACK!" << std::endl;
	}
	else if ( value > 21)
	{
		_areBusted = true;
	}

}

void HoleCards::CalculateValue()
{
	_value = 0u;
	_numSoftAces = 0u;
	for( const auto & card : _cardContainer)
	{
		_value += card->GetValue();
		if(card->IsAce())
		{
			++_numSoftAces;
		}
	}
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
	pCard Card = nullptr;
	if(!IsEmpty())
	{
		Card =  std::move(_cardContainer.back());
		_cardContainer.pop_back();
	}
	else
	{
		// TODO Get better error handling
		//std::cerr << "ERROR - Card container is empty!" << std::endl;
	}

	return Card;
}



