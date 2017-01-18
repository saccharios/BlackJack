/*
 * Card.h
 *
 *  Created on: 10.10.2016
 *      Author: Stefan
 */

#ifndef CARD_H_
#define CARD_H_

#include <string>
#include "StaticDeclarations.h"


class Card {
public:
	Card(std::string const & face, std::string const & suit);
	std::string const & GetFace() const { return _face; }
	std::string const & GetSuit() const { return _suit; }
	unsigned int const & GetValue() const {	return _value; }
	void Print() const { std::cout << _face << _suit; }

private:
	std::string _face;
	std::string _suit;
	unsigned int _value;
};


#endif /* CARD_H_ */
