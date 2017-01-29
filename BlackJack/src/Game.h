/*
 * Game.h
 *
 *  Created on: 30.12.2016
 *      Author: Stefan
 */

#include "Deck.h"
#include "player.h"
#include "Dealer.h"
#include "GlobalDeclarations.h"

#ifndef GAME_H_
#define GAME_H_

// Class game is the glue code which binds all other classes together.
// It guides the game.
class Game {
	using pPlayer = std::unique_ptr<Player>;
public:

	// Class Game is a Singleton
	static Game & getInstance()
	{
		static Game instance;
		return instance;
	}
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
	static void PrintRules();
	void PrintNumPlayers () const;
	bool PlayAnotherRound () const;

private:
	Game();

	Deck _deck;
	Dealer _dealer;
	// Players are pointers to avoid issues with card pointers
	std::vector<pPlayer> _players;
};

#endif /* GAME_H_ */
