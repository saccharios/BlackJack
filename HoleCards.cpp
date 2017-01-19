/*
 * HoleCards.cpp
 *
 *  Created on: 11.01.2017
 *      Author: Stefan
 */
#include <memory>
#include "HoleCards.h"
#include <iostream>

HoleCards::HoleCards():
_areBlackJack(false),
_arePair(false),
_arePairAces(false),
_areBusted(false)
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
	auto face = card->GetFace();
	Base::AddCard(std::move(card));

	const unsigned int value = GetValue();
	if( Base::NumCards() == 2 && value ==  21)
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

	for(auto const & Card : Base::_card_container)
	{
		value += Card->GetValue();
		if(Card->GetFace() == "A") // While adding the values, count how many aces you have
		{
			++numAces;
		}
	}
	// If the value is >21 and you have aces, you use the ace as a 1
	while( value > 21 && numAces >0)
	{
		value -=10;
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
	Base::Print();
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
	std::cout << "You have = " << Base::NumCards() <<" Cards" << std::endl;
}




