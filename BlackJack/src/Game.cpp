/*
 * Game.cpp
 *
 *  Created on: 11.01.2017
 *      Author: Stefan
 */

#include <iostream>
#include <string>
#include <sstream>
#include "Game.h"
#include "Deck.h"
#include "Player.h"
#include "Dealer.h"
#include "UserInput.h"
#include <sstream>
void Game::AddDecks()
{
	// Adds sets to the deck
	std::cout << "With how many decks do you want to play?" << std::endl;
	auto NSets = UserInput::ReadInNumber<std::size_t>(1, MAX_SETS);
	_deck.AddSets(NSets);
}

void Game::AddPlayers()
{
	// Player creator function. Needs user input.
	std::cout <<"How many players want to play?" << std::endl;
	auto NPlayers = UserInput::ReadInNumber<std::size_t>(1, MAX_PLAYERS);
	std::cout << "Enter names and balances for each player:" << std::endl;
	for( std::size_t i = 0; i < NPlayers; ++i )
	{
		auto name = UserInput::ReadInName(i);

		std::cout << "Welcome " << name <<". Set your balance. "<< std::endl;
		auto balance = UserInput::ReadInNumber<double>( MIN_INIT_BALANCE, MAX_INIT_BALANCE);

		_players.push_back(std::move(pPlayer(new Player(_deck, name, balance))));
	}
}


void Game::PlayRound()
{
	// Play one round.
	std::cout << "-------New Round------" << std::endl;
	SetWagers();
	GetStartCards();
	PlayCards();
	Evaluate();
	PutCardsBack();
	RemoveBrokePlayers();
}

void Game::SetWagers()
{
	// Set wager for each player
	std::cout << "-------Set Wagers------" << std::endl;
	for(auto const & player : _players)
	{
		player->SetWagerUser();
	}
}

void Game::GetStartCards()
{
	std::cout << "-------Dealing Start Cards------" << std::endl;
	// Deal start cards to each player and the dealer
	for(auto const & player : _players)
	{
		player->Start();
	}
	_dealer.Start();
}
void Game::PlayCards()
{
	//	Let all players play, then the dealer
	std::cout << "-------Players are playing------" << std::endl;
	for(auto const & player : _players)
	{
		player->Play();
	}
	_dealer.Play();

}
void Game::Evaluate()
{
	// Evaluate payout for each player
	std::cout <<"------Payout Time------" << std::endl;
	for(auto const & player : _players)
	{
		player->Evaluate(_dealer.HasBlackJack(),
				_dealer.IsBusted(),
				_dealer.GetValue());
		player->PrintBalance();
	}
}


void Game::PutCardsBack()
{
	// As you would in the real card game, at the end of a round all players and the dealer
	// put their cards back to the deck
	for(auto const & player : _players)
	{
		player->PutCardsBack();
	}
	_dealer.PutCardsBack();
}

void Game::RemoveBrokePlayers()
{
	// If a player has less than the minimum wager, they are removed.
	// Conventional for loop because it beed access to the index to remove it
	for( std::size_t i = 0; i <_players.size(); ++i)
	{
		if(_players[i]->GetBalance() < MIN_WAGER)
		{
			_players.erase(_players.begin()+i);
			--i; // Don't forget to decrement the counter as you just have removed player nr i
		}
	}
}


void Game::PrintRules()
{
	// Introduction text
	std::stringstream strm;
	strm
	<< "-------------WELCOME TO BLACKJACK--------------\n"
	<< "                                              	\n"
	<< "   The goal is:                               	\n"
	<< "                                              	\n"
	<< "   Get as close to 21 with your cards, but not	\n"
	<< "   over it. If you have more points than the  	\n"
	<< "   dealer, you win.						   	\n"
	<< "                                              	\n"
	<< "   The Rules are:                             	\n"
	<< "                                              	\n"
	<< "1) Each player places a wager at the beginning	\n"
	<< "   of a round. The minimum wager is "<<MIN_WAGER<<".\n"
	<< "                                              	\n"
	<< "2) Each player is dealt two cards. The dealer 	\n"
	<< "   receives one card. If you have 21 points	\n"
	<< "   with your two starting cards, you have		\n"
	<< "   BlackJack.           					   	\n"
	<< "                                              	\n"
	<< "3) The players have the following actions:	   	\n"
	<< "                                              	\n"
	<< "   Stand (s). The player has finished his hand.\n"
	<< "                                              	\n"
	<< "   Hit (h). Receive one card. If the sum of    \n"
	<< "   your cards exceeds 21, you have instantly   \n"
	<< "   lost.                  						\n"
	<< "                                              	\n"
	<< "   Double (d). Only available as your first    \n"
	<< "   action. Double your wager and receive		\n"
	<< "   exactly one more card. Finishes your turn.	\n"
	<< "                                              	\n"
	<< "   Split (p). Only available as your first    	\n"
	<< "   action if you have a pair.					\n"
	<< "   Splits your two cards into two hands and	\n"
	<< "   each hand receives one new card. The player \n"
	<< "   then continues with both hands.			 	\n"
	<< "   You are allowed to split again after you	\n"
	<< "   split your original hand. For each split,	\n"
	<< "   you need to have sufficient funds available,\n"
	<< "   as you have to put the same wager on a    	\n"
	<< "   split hand.									\n"
	<< "   A pair of Aces is an exception. 			\n"
	<< "   On each split Ace, you receive exactly one 	\n"
	<< "   more card and your turn is over. 			\n"
	<< "                                              	\n"
	<< "4) The value of a cards is its number, face 	\n"
	<< "   cards are worth 10 points. Aces can either 	\n"
	<< "   be 11 or 1 point.				 			\n"
	<< "                                              	\n"
	<< "5) The dealer plays last. He must hit cards 	\n"
	<< "   until he has more than 16 points. If the	\n"
	<< "   dealer gets busted, every remaining player	\n"
	<< "   wins.										\n"
	<< "   											\n"
	<< "-------------------GOOD LUCK-------------------\n"
	;
	_console.write(strm);
}

void Game::PrintNumPlayers () const
{
	std::cout << "There are " << _players.size() << " players in the game." << std::endl;
}

bool Game::PlayAnotherRound () const
{
	// Ask the user if they want to play another round if there are still players with enough money
	if ( _players.size() < 1u)
	{
		std::cout << "There are no more players left!" << std::endl;
		std::cout << "--------------------BYE BYE--------------------" << std::endl;
		return false;
	}
	std::cout << "Do you want to play another round?";
	auto yesOrNo = UserInput::ReadInAction({"y","n"});
	if( yesOrNo == "y" )
	{
		return true;
	}
	else if( yesOrNo == "n" )
	{
		std::cout << "--------------------BYE BYE--------------------" << std::endl;
		return false;
	}
	else
	{
		std::cout << "ERROR! User Input failed!" << std::endl;
		return false;
	}

}




