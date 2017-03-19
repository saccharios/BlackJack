/*
 * PlayerStrategy_Test.cpp
 *
 *  Created on: 16.03.2017
 *      Author: Stefan
 */

#include "PlayerStrategy_Test.h"
#include "../../BlackJack/src/PlayerStrategy.h"
#include <string>
void
AIPlayer_OptimalTest::Run_OptimalStrategy()
{
	std::string action = "s";
	// Loop over all values and dealervalues, with no pair and no aces
	unsigned int value = 0;
	bool isSoft = false;
	bool isPair = false;
	bool isAces = false;
	unsigned int dealerValue = 0;
	for( value = 5; value <= 20; ++value )
	{
		for( dealerValue = 2; dealerValue <= 11; ++dealerValue )
		{
			action = _AIPlayer.strategy_optimal(value, isSoft, isPair, isAces, dealerValue);
			if(value >= 17)
			{
				EXPECT_EQ("s",action) << "Normal. Value = " <<value << ", dealer = " << dealerValue;
			}
			else if ( (16 >= value && value >= 13 ) && dealerValue <= 6)
			{
				EXPECT_EQ("s",action) << "Normal. Value = " <<value << ", dealer = " << dealerValue;
			}
			else if (value == 12 && (4 >= dealerValue && dealerValue  <= 6))
			{
				EXPECT_EQ("s",action) << "Normal. Value = " <<value << ", dealer = " << dealerValue;
			}
			else if (value == 11 && dealerValue <= 10 )
			{
				EXPECT_EQ("d",action) << "Normal. Value = " <<value << ", dealer = " << dealerValue;
			}
			else if (value == 10 && dealerValue  <= 9)
			{
				EXPECT_EQ("d",action) << "Normal. Value = " <<value << ", dealer = " << dealerValue;
			}
			else if (value == 9 && (3 >= dealerValue && dealerValue  <= 6))
			{
				EXPECT_EQ("d",action) << "Normal. Value = " <<value << ", dealer = " << dealerValue;
			}
			else
			{
				EXPECT_EQ("h",action) << "Normal. Value = " <<value << ", dealer = " << dealerValue;
			}
		}
	}

	// Loop over all values and dealervalues, with soft ace
	isSoft = true;
	isPair = false;
	isAces = false;
	for( value = 5; value <= 20; ++value )
	{
		for( dealerValue = 2; dealerValue <= 11; ++dealerValue )
		{
			action = _AIPlayer.strategy_optimal(value, isSoft, isPair, isAces, dealerValue);
			if(value >= 19)
			{
				EXPECT_EQ("s",action) << "Soft. Value = " <<value << ", dealer = " << dealerValue;
			}
			else if ( value == 18 &&  dealerValue  <= 8)
			{
				if( 3 >= dealerValue && dealerValue  <= 6)
				{
					EXPECT_EQ("d",action) << "Soft. Value = " <<value << ", dealer = " << dealerValue;
				}
				else
				{
					EXPECT_EQ("s",action) << "Soft. Value = " <<value << ", dealer = " << dealerValue;
				}
			}
			else if (value == 17 && (3 >= dealerValue && dealerValue  <= 6))
			{
				EXPECT_EQ("d",action) << "Soft. Value = " <<value << ", dealer = " << dealerValue;
			}
			else if ( (16 >= value && value >= 15 ) && (4 >= dealerValue && dealerValue  <= 6) )
			{
				EXPECT_EQ("d",action) << "Soft. Value = " <<value << ", dealer = " << dealerValue;
			}
			else if ( (14 >= value && value >= 13 ) && (5 >= dealerValue && dealerValue  <= 6) )
			{
				EXPECT_EQ("d",action) << "Soft. Value = " <<value << ", dealer = " << dealerValue;
			}
			else
			{
				EXPECT_EQ("h",action) << "Soft. Value = " <<value << ", dealer = " << dealerValue;
			}
		}
	}
	// Handle each pair separately, because pairs are more complicated.
	// Loop over all values and dealervalues, with pairs
	isSoft = false;
	isPair = true;
	isAces = false;
	// Pair of Aces
	isAces = true;
	value = 12;
	for( dealerValue = 2; dealerValue <= 11; ++dealerValue )
	{
		action = _AIPlayer.strategy_optimal(value, isSoft, isPair, isAces, dealerValue);
		EXPECT_EQ("p",action) << "Pair Aces. Value = " <<value << ", dealer = " << dealerValue;
	}
	isAces = false;
	// Pair of Tens, Jacks, Queens, Kings
	value = 20;
	for( dealerValue = 2; dealerValue <= 11; ++dealerValue )
	{
		action = _AIPlayer.strategy_optimal(value, isSoft, isPair, isAces, dealerValue);
		EXPECT_EQ("s",action) << "Pair Tens, Jacks, Queens, Kings. Value = " <<value << ", dealer = " << dealerValue;
	}
	// Pair of Nines
	value = 18;
	for( dealerValue = 2; dealerValue <= 11; ++dealerValue )
	{
		action = _AIPlayer.strategy_optimal(value, isSoft, isPair, isAces, dealerValue);
		if( dealerValue <=6 || dealerValue == 8 || dealerValue == 9)
		{
			EXPECT_EQ("p",action) << "Pair Nines. Value = " <<value << ", dealer = " << dealerValue;
		}
		else
		{
			EXPECT_EQ("s",action) << "Pair Nines. Value = " <<value << ", dealer = " << dealerValue;
		}
	}
	// Pair of Eights
	value = 16;
	for( dealerValue = 2; dealerValue <= 11; ++dealerValue )
	{
		action = _AIPlayer.strategy_optimal(value, isSoft, isPair, isAces, dealerValue);
		EXPECT_EQ("p",action) << "Pair Eights. Value = " <<value << ", dealer = " << dealerValue;
	}
	// Pair of Sevens
	value = 14;
	for( dealerValue = 2; dealerValue <= 11; ++dealerValue )
	{
		action = _AIPlayer.strategy_optimal(value, isSoft, isPair, isAces, dealerValue);
		if(dealerValue <= 7 )
		{
			EXPECT_EQ("p",action) << "Pair Sevens. Value = " <<value << ", dealer = " << dealerValue;
		}
		else
		{
			EXPECT_EQ("h",action) << "Pair Sevens. Value = " <<value << ", dealer = " << dealerValue;
		}
	}
	// Pair of Sixes
	value = 12;
	for( dealerValue = 2; dealerValue <= 11; ++dealerValue )
	{
		action = _AIPlayer.strategy_optimal(value, isSoft, isPair, isAces, dealerValue);
		if(dealerValue <= 6 )
		{
			EXPECT_EQ("p",action) << "Pair Sixes. Value = " <<value << ", dealer = " << dealerValue;
		}
		else
		{
			EXPECT_EQ("h",action) << "Pair Sixes. Value = " <<value << ", dealer = " << dealerValue;
		}
	}
	// Pair of Fives
	value = 10;
	for( dealerValue = 2; dealerValue <= 11; ++dealerValue )
	{
		action = _AIPlayer.strategy_optimal(value, isSoft, isPair, isAces, dealerValue);
		if( dealerValue <= 9 )
		{
			EXPECT_EQ("d",action) << "Pair Fives. Value = " <<value << ", dealer = " << dealerValue;
		}
		else
		{
			EXPECT_EQ("h",action) << "Pair Fives. Value = " <<value << ", dealer = " << dealerValue;
		}
	}
	// Pair of Fours
	value = 8;
	for( dealerValue = 2; dealerValue <= 11; ++dealerValue )
	{
		action = _AIPlayer.strategy_optimal(value, isSoft, isPair, isAces, dealerValue);
		if( dealerValue == 5 || dealerValue == 6 )
		{
			EXPECT_EQ("p",action) << "Pair Fours. Value = " <<value << ", dealer = " << dealerValue;
		}
		else
		{
			EXPECT_EQ("h",action) << "Pair Fours. Value = " <<value << ", dealer = " << dealerValue;
		}
	}
	// Pair of Threes
	value = 6;
	for( dealerValue = 2; dealerValue <= 11; ++dealerValue )
	{
		action = _AIPlayer.strategy_optimal(value, isSoft, isPair, isAces, dealerValue);
		if(dealerValue <= 7 )
		{
			EXPECT_EQ("p",action) << "Pair Threes. Value = " <<value << ", dealer = " << dealerValue;
		}
		else
		{
			EXPECT_EQ("h",action) << "Pair Threes. Value = " <<value << ", dealer = " << dealerValue;
		}
	}
	// Pair of Twos
	value = 4;
	for( dealerValue = 2; dealerValue <= 11; ++dealerValue )
	{
		action = _AIPlayer.strategy_optimal(value, isSoft, isPair, isAces, dealerValue);
		if(dealerValue <= 7 )
		{
			EXPECT_EQ("p",action) << "Pair Twos. Value = " <<value << ", dealer = " << dealerValue;
		}
		else
		{
			EXPECT_EQ("h",action) << "Pair Twos. Value = " <<value << ", dealer = " << dealerValue;
		}
	}


























}
