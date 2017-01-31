/*
 * Card.cpp
 *
 *  Created on: 11.01.2017
 *      Author: Stefan
 */

#include <iostream>
#include <array>
#include <string>
#include <algorithm>
#include <stdexcept>
#include "Card.h"
#include "GlobalDeclarations.h"
#include "assert.h"



Card::Card(std::string const & face, std::string const & suit):
_face(face),
_suit(suit)
{
	// Can only add faces and suits that are in the set
	bool faceExists = (FACE.count(face) != 0);
	bool suitExists = std::any_of(std::begin(SUIT), std::end(SUIT), [&](std::string suit) { return suit == _suit; });

	assert(faceExists);
	assert(suitExists);

	if(!faceExists || !suitExists)
	{
		throw std::invalid_argument( "Cannot create Card " + face + suit+ ".");
	}

	_value = FACE.at(face);
}



