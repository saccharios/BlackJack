/*
 * Card.cpp
 *
 *  Created on: 11.01.2017
 *      Author: Stefan
 */

#include "Card.h"
#include <iostream>
#include <array>
#include <string>
#include <algorithm>
#include <stdexcept>
#include "StaticDeclarations.h"




Card::Card(std::string const & face, std::string const & suit):
_face(face),
_suit(suit)
{
	const bool faceExists = std::any_of(std::begin(Face), std::end(Face), [&](std::string face) { return face == _face; });
	const bool suitExists = std::any_of(std::begin(Suit), std::end(Suit), [&](std::string suit) { return suit == _suit; });
	if(!faceExists || !suitExists)
	{
		throw std::invalid_argument( "Cannot create Card "+face + suit+ ".");
	}
	ConvertFaceToValue(face);
}

void Card::ConvertFaceToValue(std::string const & face)
{
	if (face == Face[0])
		_value = 2;
	else if (face == Face[1])
		_value = 3;
	else if (face == Face[2])
		_value = 4;
	else if (face == Face[3])
		_value = 5;
	else if (face == Face[4])
		_value = 6;
	else if (face == Face[5])
		_value = 7;
	else if (face == Face[6])
		_value = 8;
	else if (face == Face[7])
		_value = 9;
	else if (face == Face[8] ||
			face == Face[9] ||
			face == Face[10] ||
			face == Face[11])
		_value = 10;
	else if (face == Face[12])
	{
		_value = 11;
	}
}



