/*
 * Game.cpp
 *
 *  Created on: 11.01.2017
 *      Author: Stefan
 */

#include <string>
#include <sstream>
#include "Game.h"
#include "Deck.h"
#include "Player.h"
#include "Dealer.h"
#include <sstream>

#include "Console.h"
#include "GlobalDeclarations.h"

void Game::AddDecks()
{
	// Adds sets to the deck
	console.WriteString("With how many decks do you want to play?\n");
	auto NSets = console.ReadInNumber(1u, MAX_SETS);
	_deck.AddSets(NSets);
}


void Game::PlayRound()
{
	// Play one round.
	console.WriteString("-------New Round------\n");
	SetWagers();
	GetStartCards();
	PlayCards();
	Evaluate();
	PutCardsBack();
	RemoveBrokePlayers();
}

void Game::GetStartCards()
{
	// Deal start cards to each player and the dealer
	console.WriteString("-------Dealing Start Cards------\n");
	for(auto const & player : _players)
	{
		player->Start();
	}
	_dealer.Start();
}
void Game::PlayCards()
{
	//	Let all players play, then the dealer
	console.WriteString("-------Players are playing------\n");
	for(auto const & player : _players)
	{
		player->Play();
	}
	_dealer.Play();

}
void Game::Evaluate()
{
	// Evaluate payout for each player
	console.WriteString("------Payout Time------\n");
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




void Game::PrintNumPlayers () const
{
	std::stringstream strm;
	strm << "There are " << _players.size() << " players in the game." << std::endl;
	console.Write(strm);
}



