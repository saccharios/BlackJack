/*
 * Game.h
 *
 *  Created on: 30.12.2016
 *      Author: Stefan
 */

#include "Deck.h"
#include "Player.h"
#include "Dealer.h"
#include <memory>
#include "GlobalDeclarations.h"


// Forward declaration to avoid #include
class UserInput;

#ifndef GAME_H_
#define GAME_H_

// Class game is the glue code which binds all other classes together.
// It guides the game.
class Game {
	using pPlayer = std::unique_ptr<Player>;
public:
	Game (UserInput & usrin) : _console(usrin), _deck(), _dealer(_deck), _players() {}

	// Not allowed to copy or assign game
	Game(Game const &) = delete ;
	void operator=(Game const&) = delete;

	void AddDecks();
	void AddPlayers();
	void PlayRound();
	void SetWagers();
	void GetStartCards();
	void PlayCards();
	void Evaluate();
	void PutCardsBack();
	void RemoveBrokePlayers();
	void PrintRules();
	void PrintNumPlayers () const;
	bool PlayAnotherRound () const;

private:

	UserInput & _console;
	Deck _deck;
	Dealer _dealer;
	// Players are pointers to avoid issues with card pointers
	std::vector<pPlayer> _players;
};

#endif /* GAME_H_ */
