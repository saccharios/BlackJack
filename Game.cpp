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

void Game::AddDecks()
{
	std::cout << "With how many decks do you want to play?" << std::endl;
	auto NSets = UserInput::ReadInNumber<std::size_t>(1, MAX_DECKS);
	_deck.AddSets(NSets);
}

void Game::AddPlayers()
{
	std::cout <<"How many players want to play?" << std::endl;
	auto NPlayers = UserInput::ReadInNumber<std::size_t>(1, MAX_PLAYERS);
	std::cout << "Enter names for each player:" << std::endl;
	for( std::size_t i = 0; i < NPlayers; ++i )
	{
		auto name = UserInput::ReadInName(i);
		_players.push_back(std::move(pPlayer(new Player(_deck,name))));
		std::cout << "Welcome " << name <<"."<< std::endl;
	}
}


void Game::PlayRound()
{
	std::cout << "-------New Round------" << std::endl;
	SetWagers();
	GetStartCards();
	PlayCards();
	Evaluate();
	PutCardsBack();
	RemoveBrokePlayers();
}

void Game::SetBalances()
{
	for(auto const & player : _players)
	{
		player->SetBalance();

	}
}
void Game::SetWagers()
{
	std::cout << "-------Set Wagers------" << std::endl;
	for(auto const & player : _players)
	{
		player->SetWager();

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
	std::cout << "-------Players are playing------" << std::endl;
	//	Let all player play, then the dealer
	for(auto const & player : _players)
	{
		player->Play();
	}
	_dealer.Play();

}
void Game::Evaluate()
{
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
	for(auto const & player : _players)
	{
		player->PutCardsBack();
	}
	_dealer.PutCardsBack();
}

void Game::RemoveBrokePlayers()
{
	for( std::vector<pPlayer>::size_type i = 0; i <_players.size(); ++i)
	{
		if(_players[i]->GetBalance() < MIN_WAGER)
		{
			_players.erase(_players.begin()+i);
			--i; // Dont forget to decrement the counter as you just have removed player i
		}
	}
}


void Game::PrintRules()
{
	std::cout<< "-------------WELCOME TO BLACKJACK--------------" << std::endl;
	std::cout<< "                                              	" << std::endl;
	std::cout<< "   The goal is:                               	" << std::endl;
	std::cout<< "                                              	" << std::endl;
	std::cout<< "   Get as close to 21 with your cards, but not	" << std::endl;
	std::cout<< "   over it. If you have more points than the  	" << std::endl;
	std::cout<< "   dealer, you win.						   	" << std::endl;
	std::cout<< "                                              	" << std::endl;
	std::cout<< "   The Rules are:                             	" << std::endl;
	std::cout<< "                                              	" << std::endl;
	std::cout<< "1) Each player places a wager at the beginning	" << std::endl;
	std::cout<< "   of a round. The minimum wager is "<<MIN_WAGER<<"." << std::endl;
	std::cout<< "                                              	" << std::endl;
	std::cout<< "2) Each player is dealt two cards. The dealer 	" << std::endl;
	std::cout<< "   receives one card. If you have 21 points	" << std::endl;
	std::cout<< "   with your two starting cards, you have		" << std::endl;
	std::cout<< "   BlackJack.           					   	" << std::endl;
	std::cout<< "                                              	" << std::endl;
	std::cout<< "3) The players have the following actions:	   	" << std::endl;
	std::cout<< "                                              	" << std::endl;
	std::cout<< "   Stand (s). The player has finished his hand." << std::endl;
	std::cout<< "                                              	" << std::endl;
	std::cout<< "   Hit (h). Receive one card. If the sum of    " << std::endl;
	std::cout<< "   your cards exceeds 21, you have instantly   " << std::endl;
	std::cout<< "   lost.                  						" << std::endl;
	std::cout<< "                                              	" << std::endl;
	std::cout<< "   Double (d). Only available as your first    " << std::endl;
	std::cout<< "   action. Double your wager and receive		" << std::endl;
	std::cout<< "   exactly one more card. Finishes your turn.	" << std::endl;
	std::cout<< "                                              	" << std::endl;
	std::cout<< "   Split (p). Only available as your first    	" << std::endl;
	std::cout<< "   action if you have a pair.					" << std::endl;
	std::cout<< "   Splits your two cards into two hands and	" << std::endl;
	std::cout<< "   each hand receives one new card. The player " << std::endl;
	std::cout<< "   then continues with both hands.			 	" << std::endl;
	std::cout<< "   You are allowed to split again after you	" << std::endl;
	std::cout<< "   split your original hand. For each split,	" << std::endl;
	std::cout<< "   you need to have sufficient funds available," << std::endl;
	std::cout<< "   as you have to put the same wager on a    	" << std::endl;
	std::cout<< "   split hand.									" << std::endl;
	std::cout<< "   A pair of Aces is an exception. 			" << std::endl;
	std::cout<< "   On each split Ace, you receive exactly one 	" << std::endl;
	std::cout<< "   more card and your turn is over. 			" << std::endl;
	std::cout<< "                                              	" << std::endl;
	std::cout<< "4) The value of a cards is its number, face 	" << std::endl;
	std::cout<< "   cards are worth 10 points. Aces can either 	" << std::endl;
	std::cout<< "   be 11 or 1 point.				 			" << std::endl;
	std::cout<< "                                              	" << std::endl;
	std::cout<< "5) The dealer plays last. He must hit cards 	" << std::endl;
	std::cout<< "   until he has more than 16 points. If the	" << std::endl;
	std::cout<< "   dealer gets busted, every remaining player	" << std::endl;
	std::cout<< "   wins.										" << std::endl;
	std::cout<< "   											" << std::endl;
	std::cout<< "-------------------GOOD LUCK-------------------" << std::endl;

}

void Game::PrintNumPlayers () const
{
	std::cout << "There are " << _players.size() << " players in the game." << std::endl;
}

bool Game::PlayAnotherRound () const
{
	if ( _players.size() < 1)
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


Game::Game() :
				_dealer (_deck),
				_players()
{}



