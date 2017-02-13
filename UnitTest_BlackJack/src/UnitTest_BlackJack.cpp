/*
 * UnitTest.cpp
 *
 *  Created on: 21.01.2017
 *      Author: Stefan
 */

#include "gtest/gtest.h"
// TODO Make always build upon click run, ctrl f11 and in console c/c++ unit run

int main(int argc, char ** argv)
{ ::testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}
