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

Player::Player(Deck & deck, std::string name, float balance) :
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
	std::vector<HandManager>::size_type i = 0;
	while(i < _handManager.size()) // Spliting cards creates more hands
	{
		while( !_handManager[i]->IsPlayed() ) // Play current hand as long as you are allowed to
		{
			std::cout<< GetName() << " Playing Hand ";
			_handManager[i]->PrintHandNumber();
			_handManager[i]->PrintCards();

			// Can't keep playing if you have BlackJack
			if(_handManager[i]->IsBlackJack())
			{
				break;
			}

			// Get action from user
			auto availableactions = GetAvailableActionSet(_handManager[i]);
			std::cout << "Enter action: ";
			auto action = UserInput::ReadInAction(availableactions);
//			auto action = PlayBasicStrategy(); // AutoPlayer
			std::cout << "You choose to ";

			// Evaluate action
			if(action == "h") // Hit
			{
				std::cout << "Hit. ";
				_handManager[i]->ActionHit();
			}
			else if(action == "d") // Double
			{
				std::cout << "Double. ";
				_balance -= _orignialWager;
				_handManager[i]->ActionDouble();
			}
			else if(action == "p") // Split
			{
				std::cout << "Split Hand Nr "<< i << "."<<std::endl;
				_balance -= _orignialWager;
				// Save if starting hand is pair of aces, because if split Aces do not allow to continue playing.
				bool wasAces = _handManager[i]->IsPairAces();
				auto card = _handManager[i]->ActionSplit();
				auto nextNr = _handManager[i]->GetHandNumber() + 1;
				_handManager.push_back(std::move(pHandManager(new HandManager(_deck, _orignialWager,nextNr))));
				_handManager.back()->PrintHandNumber();
				_handManager.back()->Start(std::move(card));
				if(wasAces)
				{
					_handManager[i]->ActionStand();
					_handManager.back()->ActionStand();
				}
			}
			else // Stand
			{
				std::cout << "Stand." << std::endl;
				_handManager[i]->ActionStand();
			}
		}
		++i; // Increment players hand counter
	}


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
	_orignialWager = UserInput::ReadInNumber<float>( MIN_WAGER, _balance);
	_balance -= _orignialWager;
	PrintWager();
}


void Player::PrintWager () const
{
	std::cout << GetName() <<"'s wager is: " << _orignialWager << std::endl;
}

float const & Player::GetBalance () const
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


