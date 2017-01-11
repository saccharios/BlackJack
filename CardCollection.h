/*
 * CardCollection.h
 *
 *  Created on: 14.10.2016
 *      Author: Stefan
 */

#ifndef CARDCOLLECTION_H_
#define CARDCOLLECTION_H_
#include "Card.h"
#include <vector>
#include <memory>

class CardCollection {
	typedef std::unique_ptr<Card> pCard;
public:
	CardCollection(){}
	bool IsEmpty() const { return _card_container.empty(); }
	void AddCard( pCard  card) { _card_container.push_back(std::move(card)); }
	pCard RemoveCard(unsigned int num);
	pCard RemoveLastCard();
	void Print() const;
	std::size_t NumCards() const { return _card_container.size(); }

protected:
	std::vector<pCard> _card_container;
};

#endif /* CARDCOLLECTION_H_ */
