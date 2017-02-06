/*
 * Dealer.cpp
 *
 *  Created on: 11.01.2017
 *      Author: Stefan
 */


#include <memory>
#include <iostream>
#include "Dealer.h"
#include "Deck.h"
#include "HoleCards.h"
#include "Card.h"


Dealer::Dealer(Deck & deck) :
_deck(deck)
{}
void Dealer::Start()
{
	pCard card1 = _deck.Draw();
	_holeCards.StartCards(std::move(card1));
	PrintCards();
}

void Dealer::Play()
{
// Dealer has to hit until their value is above 17
	std::cout << "-------Dealer-------" << std::endl;
	while(_holeCards.GetValue() < 17) // Basic Strategy
	{
		ActionHit();
	}
}

void Dealer::ActionHit()
{
	std::cout << "Draw a card.... The card drawn is the ";
	pCard card = _deck.Draw();
	card->Print();
	std::cout << std::endl;
	_holeCards.AddCard(std::move(card));
	PrintCards();
}

void Dealer::PutCardsBack()
{
	while(!_holeCards.IsEmpty())
	{
		_deck.AddCard(_holeCards.RemoveLastCard());
	}
}


void Dealer::PrintCards() const
{
	std::cout << "Dealer's Cards are: ";
	_holeCards.PrintCards();
}

