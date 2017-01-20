/*
 * HoleCards.cpp
 *
 *  Created on: 11.01.2017
 *      Author: Stefan
 */
#include <memory>
#include <iostream>
#include "HoleCards.h"

HoleCards::HoleCards():
_areBlackJack(false),
_arePair(false),
_arePairAces(false),
_areBusted(false),
_value(0),
_numSoftAce(0),
_cardContainer()
{}

void HoleCards::StartCards(pCard card)
{
	Reset();
	AddCard(std::move(card));
}

void HoleCards::StartCards(pCard card1, pCard card2)
{

	Reset();
	// Check for a pair at start:
	if ( card1->GetFace() == card2->GetFace())
	{
		_arePair = true;
		if ( card1->GetFace() == "A")
		{
			_arePairAces = true;
		}
	}

	AddCard(std::move(card1));
	AddCard(std::move(card2));
}

void HoleCards::AddCard(pCard card)
{
	// Keep track of the value while adding a card, deal with aces and save how many aces are used soft
	if( card->GetFace() == "A")
	{
		++_numSoftAce;
	}
	_value += card->GetValue();
	if( _value > 21 && _numSoftAce > 0)
	{
		_value -= 10;
		--_numSoftAce;
	}

	// Transfer ownership to cardContainer
	 _cardContainer.push_back(std::move(card));
	unsigned int value = GetValue();
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
	_numSoftAce = 0;
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
		if( _numSoftAce > 0)
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
	pCard Card;
	if(!IsEmpty())
	{
		Card =  std::move(_cardContainer.back());
		_cardContainer.pop_back();
	}
	else
	{
		std::cerr << "ERROR - Card container is empty!" << std::endl;
	}

	return Card;
}

