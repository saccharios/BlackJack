/*
 * UnitTest.cpp
 *
 *  Created on: 21.01.2017
 *      Author: Stefan
 */

#include <iostream>
#include "gtest/gtest.h"
#include "Deck_Test.h"
#include "Card_Test.h"


int main(int argc, char ** argv)
{ ::testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}
