/*
 * Player.cpp
 *
 *  Created on: 11.01.2017
 *      Author: Stefan
 */

#include <memory>
#include <sstream>
#include <iostream>
#include "Player.h"
#include "Card.h"
#include "HoleCards.h"
#include "HandManager.h"
#include "Deck.h"
#include "UserInput.h"
#include "GlobalDeclarations.h"
#include "assert.h"

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
	_handManager.push_back(std::move(pHandManager(new HandManager(_deck, _orignialWager, 0))));
	_handManager.at(0)->Start();
	PrintCards();
}
void Player::Play()
{
	std::cout << "-------" << GetName() <<  "'s turn-------" << std::endl;
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
	std::cout<< GetName() << " Playing Hand ";
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
		auto availableactions = GetAvailableActionSet(hand);
		std::cout << "Enter action: ";
		auto action = UserInput::ReadInAction(availableactions);
		//			auto action = PlayBasicStrategy(); // AutoPlayer

		PlayAction(action, hand);
	}
}
void Player::PlayAction(std::string action, pHandManager const & hand)
{
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
	std::cout << "You choose to Hit. ";
	hand->ActionHit();
}
void Player::Stand(pHandManager const & hand)
{
	std::cout << "You choose to Stand." << std::endl;
	hand->ActionStand();
}
void Player::Double(pHandManager const & hand)
{
	std::cout << "You choose to Double. ";
	_balance -= _orignialWager;
	hand->ActionDouble();
}
void Player::Split(pHandManager const & hand)
{
	std::cout << "You choose to Split. "<<std::endl;
	_balance -= _orignialWager;
	auto newHand = hand->ActionSplit();
	_handManager.push_back(std::move(newHand));
}

std::string Player::PlayBasicStrategy()
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

// Available actions depend on two things:
// 1) The wager and balance of a player
// 2) State of the hand
// TODO Can those two be separated in a better way?
// Take the intersection of two sets maybe?
std::set<std::string> Player::GetAvailableActionSet(pHandManager const & currentHand)
{
	if(currentHand->IsFirstAction() &&  _balance >= _orignialWager)
	{
		if(  currentHand->IsPair())
		{
			return ACTION_SPLIT_DOUBLE;
		}
		else
		{
			return ACTION_DOUBLE;
		}
	}
	else if(currentHand->IsFirstAction() && currentHand->IsPair() &&  _balance < _orignialWager)
	{
		std::cout << "Your balance is too low to Split or Double." << std::endl;
	}
	return ACTION_STANDARD;
}

void Player::Evaluate(	bool const & dealerHasBlackJack,
		bool const & dealerIsBusted,
		unsigned int const & dealerValue)
{
	for( auto const & currentHand : _handManager)
	{
		std::cout << GetName() <<"'s ";
		currentHand->PrintHandNumber();
		if( dealerHasBlackJack)
		{
			if(currentHand->IsBlackJack())
			{
				_balance += currentHand->PayoutPush();
			}
			else
			{
				_balance += currentHand->PayoutLoose();
			}

		}
		else if ( currentHand->IsBlackJack() )
		{
			_balance += currentHand->PayoutBlackJack();
		}
		else if ( currentHand->IsBusted())
		{
			_balance += currentHand->PayoutLoose();
		}
		else if(dealerIsBusted)
		{
			_balance += currentHand->PayoutWin();
		}
		else if(currentHand->GetValue() > dealerValue)
		{
			_balance += currentHand->PayoutWin();
		}
		else if(currentHand->GetValue() < dealerValue)
		{
			_balance += currentHand->PayoutLoose();
		}
		else
		{
			_balance += currentHand->PayoutPush();
		}
	}
}


void Player::PrintCards() const
{
	std::cout << GetName() << "'s Cards are: ";
	std::vector<HandManager>::size_type i = 0;
	for( auto const & currentHand : _handManager)
	{
		std::cout << "Hand Nr " << i << " ";
		currentHand->PrintCards();
		++i;
	}
}

void Player::PutCardsBack()
{
	// Put all cards of each hand back to the deck
	for( auto const & currentHand : _handManager)
	{
		while(!currentHand->IsEmpty())
		{
			_deck.AddCard(std::move(currentHand->RemoveLastCard()));
		}
	}
	// Clear all ptrs that now point to empty hole cards
	_handManager.clear();

}
void Player::SetWager ()
{
	std::cout << GetName()<< " set your Wager: " << std::endl;
	_orignialWager = UserInput::ReadInNumber<double>( MIN_WAGER, _balance);
	_balance -= _orignialWager;
	PrintWager();
}


void Player::PrintWager () const
{
	std::cout << GetName() <<"'s wager is: " << _orignialWager << std::endl;
}

double const & Player::GetBalance () const
{
	return _balance;
}

void Player::PrintBalance () const
{
	std::cout << GetName()<< "'s new balance is " << GetBalance() << "." << std::endl;
	if( GetBalance() < MIN_WAGER)
	{
		std::cout << GetName() << " is broke! You will be removed from the game." << std::endl;
	}
}

std::string const & Player::GetName() const
{
	return _name;
}

void Player::PrintName () const
{
	std::cout << GetName() << std::endl;
}


