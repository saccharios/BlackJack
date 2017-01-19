/*
 * StaticDeclarations.h
 *
 *  Created on: 17.10.2016
 *      Author: Stefan
 */

#ifndef GLOBALDECLARATIONS_H_
#define GLOBALDECLARATIONS_H_


#include <set>
#include <map>

static constexpr float minWager = 1.0;
static constexpr std::size_t maxDecks = 8;
static constexpr std::size_t maxPlayers = 8;
static constexpr float minInitBalance = 1.0;
static constexpr float maxInitBalance = 100000.0;
constexpr std::string::size_type maxChars = 20 ;

const std::set<std::string> Suit{"h","d","c","s"};
// Face is a map, so assigning the value to a card is easy.
const std::map<std::string, unsigned int> Face = {{"2", 2}, {"3", 3}, {"4", 4}, {"5", 5}, {"6", 6}, {"7", 7}, {"8", 8}, {"9", 9}, {"T", 10}, {"J", 10}, {"Q", 10}, {"K", 10}, {"A", 11}};

// Allowed action sets
const std::set<std::string> SplitDouble{"h","s","d","p"};
const std::set<std::string> Double{"h","s","d"};
const std::set<std::string> Standard{"h","s"};


#endif
