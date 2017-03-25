/*
 * Game.h
 *
 *  Created on: 30.12.2016
 *      Author: Stefan
 */

#include "Deck.h"
#include "Dealer.h"
#include <memory>
#include "GlobalDeclarations.h"
#include "PlayerStrategy.h"

#ifndef GAME_H_
#define GAME_H_

// Class game is the glue code which binds all other classes together.
// It guides the game.
class Game {
	using pPlayer = std::unique_ptr<Player>;

public:
	Game () : _deck(), _dealer(_deck), _players() {}
	// Not allowed to copy or assign game
	Game(Game const &) = delete ;
	void operator=(Game const&) = delete;

	void AddDecks();
	void PlayRound();
	void GetStartCards();
	void PlayCards();
	void Evaluate();
	void PutCardsBack();
	void RemoveBrokePlayers();
	void PrintNumPlayers () const;

	virtual void SetWagers() = 0;
	virtual bool PlayAnotherRound () const = 0;

protected:
	virtual ~Game(){}; // Not allowed to polymorphic delete derivatives

	Deck _deck;
	Dealer _dealer;
	// Players are pointers to avoid issues with card pointers
	std::vector<pPlayer> _players;
};

#endif /* GAME_H_ */
