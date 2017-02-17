/*
 * Player.cpp
 *
 *  Created on: 11.01.2017
 *      Author: Stefan
 */

#include <memory>
#include <sstream>
#include "Player.h"
#include "Card.h"
#include "HoleCards.h"
#include "HandManager.h"
#include "Deck.h"
#include "GlobalDeclarations.h"
#include "assert.h"
#include "Console.h"

Player::Player(Deck & deck, std::string name, double balance) :
_balance(balance),
_orignialWager(0),
_deck(deck),
_handManager(),
_name(name)
{
	assert(_balance >= MIN_INIT_BALANCE);
	assert(_balance <= MAX_INIT_BALANCE);
};

void Player::Start()
{
	// Initial start routine for the player
	_handManager.push_back(std::move(pHandManager(new HandManager(_deck, _orignialWager, 0))));
	_handManager.at(0)->Start();
	PrintCards();
}
void Player::Play()
{
	std::stringstream strm;
	// Player plays his hands. Number of hands can increase due to spliting
	strm << "-------" << GetName() <<  "'s turn-------\n";
	console.Write(strm);
	std::size_t  handNr = 0;
	while(handNr < _handManager.size()) // Spliting cards creates more hands
	{
		while( !_handManager[handNr]->IsPlayed() ) // Play current hand as long as you are allowed to
		{
			PlayOneHand(_handManager[handNr]);
		}
		++handNr; // Increment players hand counter
	}
}

void Player::PlayOneHand(pHandManager const & hand)
{

	std::stringstream strm;
	// Plays one hand of a player, function may create more hands that the player can play.
	strm << GetName() << " Playing Hand ";
	console.Write(strm);
	hand->PrintHandNumber();
	hand->PrintCards();

	// Can't keep playing if you have BlackJack
	if(hand->IsBlackJack())
	{
		hand->ActionStand();
	}
	else
	{
		// Get action from user
		auto actionSetCards = hand->GetAvailableActionSet();
		auto actionSetPlayer = GetAvailableActionSet(actionSetCards);
		console.WriteString("Enter action: ");
		auto action = console.ReadInAction(actionSetPlayer);
		// TODO			auto action = PlayBasicStrategy(); // AutoPlayer

		PlayAction(action, hand);
	}
}
void Player::PlayAction(std::string action, pHandManager const & hand)
{
	// Actions are identified by a string. Using polymorphism to deal with actions would require
	// to introduce an interface action class and four derivatives. However, one still would
	// not get rid of a switch or if/else statements like those below, because the input
	// from the user is a string. This string needs to be mapped to a derived class anyways.
	if(action == "h") // Hit
	{
		Hit(hand);
	}
	else if(action == "d") // Double
	{
		Double(hand);
	}
	else if(action == "p") // Split
	{
		Split(hand);
	}
	else // Stand
	{
		Stand(hand);
	}
}
void Player::Hit(pHandManager const & hand)
{
	console.WriteString("You choose to Hit.");
	hand->ActionHit();
}
void Player::Stand(pHandManager const & hand)
{
	console.WriteString("You choose to Stand.\n");
	hand->ActionStand();
}
void Player::Double(pHandManager const & hand)
{
	console.WriteString("You choose to Double.");
	SubtractFromBalance(_orignialWager);
	hand->ActionDouble();
}
void Player::Split(pHandManager const & hand)
{
	console.WriteString("You choose to Split.");
	SubtractFromBalance(_orignialWager);
	auto newHand = hand->ActionSplit();
	AddHand(std::move(newHand));
}

void Player::AddHand(pHandManager hand)
{
	// Routine is used for testing PutCardsBack()
	_handManager.push_back(std::move(hand));
}

std::string Player::PlayBasicStrategy() const
{
	if( _handManager.at(0)->GetValue() < 17 )
	{
		return "h";
	}
	else
	{
		return "s";
	}

}

std::set<std::string> Player::GetAvailableActionSet(std::set<std::string> const & actionSet) const
{
	// Depending on the balance of the player and the input, return the available actionSet
	if(_balance < _orignialWager && actionSet == ACTION_SPLIT_DOUBLE)
	{
		console.WriteString("Your balance is too low to Split or Double.");
		return ACTION_STANDARD;
	}
	else if(_balance < _orignialWager && actionSet == ACTION_DOUBLE)
	{
		console.WriteString("Your balance is too low to Double.");
		return ACTION_STANDARD;
	}
	else
	{
		return actionSet;
	}
}

void Player::Evaluate(	bool const & dealerHasBlackJack,
		bool const & dealerIsBusted,
		unsigned int const & dealerValue)
{
	std::stringstream strm;
	for( auto const & currentHand : _handManager)
	{
		strm << GetName() <<"'s ";
		console.Write(strm);
		auto payout = currentHand->Evaluate(dealerHasBlackJack,dealerIsBusted, dealerValue);
		AddToBalance(payout);
	}
}


void Player::PrintCards() const
{
	std::stringstream strm;
	strm << GetName() << "'s Cards are: ";
	console.Write(strm);
	auto i = 0u;
	for( auto const & currentHand : _handManager)
	{
		strm << "Hand Nr " << i << " ";
		console.Write(strm);
		currentHand->PrintCards();
		++i;
	}
}

void Player::PutCardsBack()
{
	// Put all cards of each hand back to the deck.
	for( auto const & currentHand : _handManager)
	{
		currentHand->PutCardsBack();
	}
	// Clear all ptrs that now point to empty hole cards.
	_handManager.clear();

}
void Player::SetWagerUser ()
{
	// Reads in the wager from the user / console.
	std::stringstream strm;
	strm << GetName()<< " set your Wager: \n";
	console.Write(strm);
	auto wager = console.ReadInNumber( MIN_WAGER, _balance);
	SetWager(wager);
	PrintWager();
}
void Player::SetWager (double const & wager)
{
	// Wager must be within bounds.
	assert(wager >= MIN_WAGER);
	assert(wager <= MAX_WAGER);
	_orignialWager = wager;
	SubtractFromBalance(_orignialWager);
}


void Player::PrintWager () const
{
	std::stringstream strm;
	strm << GetName() <<"'s wager is: " << _orignialWager << std::endl;
	console.Write(strm);
}

double const & Player::GetBalance () const
{
	return _balance;
}

void Player::PrintBalance () const
{
	std::stringstream strm;
	strm  << GetName()<< "'s new balance is " << GetBalance() << ".\n";
	if( GetBalance() < MIN_WAGER)
	{
		strm << GetName() << " is broke! You will be removed from the game.\n";
	}
	console.Write(strm);
}

std::string const & Player::GetName() const
{
	return _name;
}

void Player::PrintName () const
{
	std::stringstream strm;
	strm << GetName() << std::endl;
	console.Write(strm);
}

void Player::AddToBalance(double const & value)
{
	_balance += value;
}
void Player::SubtractFromBalance(double const & value)
{
	_balance -= value;
}
