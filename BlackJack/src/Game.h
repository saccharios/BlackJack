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
	using pHumanPlayer = std::unique_ptr<HumanPlayer>;
	using pAIPlayer = std::unique_ptr<AIPlayer_Basic>;
	using pAIPlayer_Optimal = std::unique_ptr<AIPlayer_Optimal>;
public:
	Game () : _deck(), _dealer(_deck), _players() {}

	// Not allowed to copy or assign game
	Game(Game const &) = delete ;
	void operator=(Game const&) = delete;

	void AddDecks();
	void AddHumanPlayers();
	void AddAIPlayers();
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
	void Simulation_Setup(std::size_t N_Decks, std::size_t N_AIPlayers);
	void Simulation_PlayRound();
private:

	Deck _deck;
	Dealer _dealer;
	// Players are pointers to avoid issues with card pointers
	std::vector<pPlayer> _players;
};

#endif /* GAME_H_ */
