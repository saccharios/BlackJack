/*
 * CardCollection.cpp
 *
 *  Created on: 11.01.2017
 *      Author: Stefan
 */

#include <vector>
#include <memory>
#include "CardCollection.h"
#include "Card.h"


CardCollection::pCard CardCollection::RemoveCard(unsigned int num)
{
	pCard Card;
	if(!IsEmpty() && NumCards() > num)
	{
		Card =  std::move(_card_container.at(num));
		_card_container.erase(_card_container.begin()+num);
	}
	return Card;
}

CardCollection::pCard CardCollection::RemoveLastCard()
{
	pCard Card;
	if(!IsEmpty())
	{
		Card =  std::move(_card_container.back());
		_card_container.pop_back();
	}

	return Card;
}

void CardCollection::Print() const
{
	for(pCard const & card : _card_container)
	{
		card->Print();
	}
}




