/*
 * Player.cpp
 *
 *  Created on: 11.01.2017
 *      Author: Stefan
 */

#include "Player.h"
#include <memory>
#include <sstream>
#include <iostream>
#include "HoleCards.h"
#include "Card.h"
#include "HandManager.h"
#include "Deck.h"
#include "StaticDeclarations.h"


Player::Player(Deck & deck, std::string name) :
_balance(0),
_orignialWager(0),
_deck(deck),
_handManager(),
_name(name)
{};

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
	while(i < _handManager.size()) // Spliting creates more hands
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
			auto action = UserInput::ReadInStr(availableactions);
//			auto action = PlayBasicStrategy(); // AutoPlayer
			std::cout << "You choose to ";

			// Evaluate action
			if(action == "h")
			{
				std::cout << "Hit. ";
				_handManager[i]->ActionHit();
			}
			else if(action == "d")
			{
				std::cout << "Double. ";
				_balance -= _orignialWager;
				_handManager[i]->ActionDouble();
			}
			else if(action == "p")
			{
				std::cout << "Split Hand Nr "<< i << "."<<std::endl;
				_balance -= _orignialWager;
				const bool _wasAces = _handManager[i]->IsPairAces(); // Save if starting hand is pair of aces, because if split Aces do not allow to continue playing.
				// Remove the two cards from the current hand
				auto card1 = _handManager[i]->RemoveLastCard();
				auto card2 = _handManager[i]->RemoveLastCard();
				_handManager[i]->PrintHandNumber();
				// Restart the the current hand with one card
				_handManager[i]->Start(std::move(card1));
				// Create a new hand with index i +1,
				auto nextNr = _handManager[i]->GetHandNumber() + 1;
				_handManager.push_back(std::move(pHandManager(new HandManager(_deck, _orignialWager,nextNr))));
				_handManager.back()->PrintHandNumber();
				_handManager.back()->Start(std::move(card2));
				if( _wasAces )
				{
					_handManager[i]->ActionStand();
					_handManager.back()->ActionStand();
				}
			}
			else
			{
				std::cout << "Stand." << std::endl;
				_handManager[i]->ActionStand();
			}
		}
		++i;
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


std::set<std::string> Player::GetAvailableActionSet(pHandManager const & currentHand)
{
	if(currentHand->IsFirstAction() &&  _balance >= _orignialWager)
	{
		if(  currentHand->IsPair())
		{
			return SplitDouble;
		}
		else
		{
			return Double;
		}
	}
	else if(currentHand->IsFirstAction() && currentHand->IsPair() &&  _balance < _orignialWager)
	{
		std::cout << "Your balance is too low to Split or Double." << std::endl;
	}
	return Standard;
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

	for( auto const & currentHand : _handManager)
	{
		while(!currentHand->IsEmpty())
		{
			_deck.AddCard(std::move(currentHand->RemoveLastCard()));
		}
	}
	_handManager.clear();

}
void Player::SetWager ()
{
	std::cout << GetName()<< " set your Wager: " << std::endl;
	_orignialWager = UserInput::ReadInNumber<float>( minWager, _balance);
	_balance -= _orignialWager;
	PrintWager();
}


void Player::PrintWager () const
{
	std::cout << GetName() <<"'s wager is: " << _orignialWager << std::endl;
}

void Player::SetBalance()
{
	std::cout << "Set Balance of " << GetName() << ": " << std::endl;
	_balance = UserInput::ReadInNumber<float>( minInitBalance, maxInitBalance);
	PrintBalance();
}

float const & Player::GetBalance () const
{
	return _balance;
}

void Player::PrintBalance () const
{
	if(GetBalance() > 0)
	{
		std::cout << GetName()<< "'s new balance is " << GetBalance() << "." << std::endl;
	}
	else
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


