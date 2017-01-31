/*
 * HandManager.cpp
 *
 *  Created on: 11.01.2017
 *      Author: Stefan
 */


#include <memory>
#include <iostream>
#include "HandManager.h"
#include "HoleCards.h"
#include "Card.h"
#include "Deck.h"
#include "GlobalDeclarations.h"

HandManager::HandManager (Deck & deck, float const & wager, std::size_t const & handNumber):
_deck(deck),
_handNumber(handNumber),
_isPlayed(false)
{
	// Make sure that the wager at the creation is within bounds. Hard force it.
	if( wager < MIN_WAGER)
	{
		_wager = MIN_WAGER;
		std::cout << "Your wager is too low, setting to minimum wager (1.0)" << std::endl;
	}
	else if (wager > MAX_WAGER)
	{
		std::cout << "Your wager is too high, setting to maximum wager (500.0)" << std::endl;
		_wager = MAX_WAGER;
	}
	else
	{
		_wager = wager;
	}
}


void HandManager::Start()
{
	pCard card1 = _deck.Draw();
	pCard card2 = _deck.Draw();
	// TODO Debugging only
//			pCard card1 = _deck.Draw(1); //Pair 3
//			pCard card2 = _deck.Draw(13); //Pair 3
//	pCard card1 = _deck.Draw(8); //Pair  A
//	pCard card2 = _deck.Draw(20); //Pair  A

	_holeCards.StartCards(std::move(card1), std::move(card2));
	_isPlayed = false;
}

void HandManager::Start( pCard card1 )
{
	if(!_holeCards.IsEmpty())
	{
		std::cout << "ERROR, cannot start. HoleCards are not empty" << std::endl;
		return;
	}

	std::cout <<"Draw second card: " ;
	pCard card2 = _deck.Draw();
	card2 ->Print();
	std::cout << " ";
	_holeCards.StartCards(std::move(card1), std::move(card2));
	PrintCards();
	_isPlayed = false;
}

// TODO Action Split should return one of the hole cards and add a new card to the current hand.

HandManager::pHandManager HandManager::ActionSplit()
{
	// Save if pair is Aces
	bool wasAces = IsPairAces();
	// Remove the two cards from the current hand
	auto card1 = RemoveLastCard();
	auto cardForNewHand = RemoveLastCard();
	PrintHandNumber();
	// Restart the the current hand with one card
	Start(std::move(card1));
	// Create new hand with incremented hand number
	auto nextNr = GetHandNumber() + 1;
	auto newHand = pHandManager(new HandManager(_deck, _wager,nextNr));

	newHand->PrintHandNumber();
	newHand->Start(std::move(cardForNewHand));
	// Don't allow to play if Aces were split
	if(wasAces)
	{
		_isPlayed = true;
		newHand->ActionStand();
		std::cout << "-------------------------------------ACES\n";
	}

	return newHand;
}
void HandManager::ActionDouble()
{
	_wager *= 2.0;
	ActionHit();
	_isPlayed = true;
}
void HandManager::ActionHit()
{
	std::cout << "Draw a card...."<<std::endl;
	pCard card = _deck.Draw();
	std::cout <<"The card drawn is the ";
	card->Print();
	std::cout << ". ";
	_holeCards.AddCard(std::move(card));
	PrintHandNumber();
	PrintCards();
	_isPlayed = GetValue() > 20;
}
void HandManager::ActionStand()
{
	_isPlayed = true;
}

bool const & HandManager::IsBlackJack()
{
	_isPlayed = true;
	return _holeCards.AreBlackJack();
}

float HandManager::PayoutPush ()
{
	std::cout << "is a push" << std::endl;
	return GetWager();
}
float HandManager::PayoutLoose ()
{
	std::cout << "looses" << std::endl;
	return 0.0;

}
float HandManager::PayoutWin ()
{
	std::cout << "wins" << std::endl;
	return 2.0*GetWager();
}
float HandManager::PayoutBlackJack ()
{
	std::cout << "BlackJack pays 5 to 2" << std::endl;
	return 2.5*GetWager();
}


void HandManager::PrintHandNumber() const
{
	std::cout << "Hand " << GetHandNumber() << ": ";
}




