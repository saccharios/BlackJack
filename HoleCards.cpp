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
	unsigned int value = 0;
	unsigned int numAces = 0;

	for(auto const & Card : _cardContainer)
	{
		value += Card->GetValue();
		if(Card->GetFace() == "A") // While adding the values, count how many aces you have
		{
			++numAces;
		}
	}
	// If the value is > 21 and you have aces, you use as many aces as you need to get value <= 21
	while( value > 21 && numAces >0)
	{
		value -= 10;
		--numAces;
	}
	return value;
}

void HoleCards::Reset()
{
	_areBlackJack = false;
	_arePair = false;
	_arePairAces = false;
	_areBusted = false;
}

void HoleCards::PrintCards() const
{
	for(pCard const & card : _cardContainer)
		{
			card->Print();
		}
	std::cout << ", Value is = ";
	if( AreBlackJack() )
	{
		std::cout << "BlackJack";
	}
	else if (AreBusted())
	{
		std::cout <<"(" << GetValue() <<") Busted";
	}
	else
	{
		std::cout << GetValue();
	}
	std::cout << "."<<std::endl;;
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

