/*
 * Player_Test.cpp
 *
 *  Created on: 30.01.2017
 *      Author: Stefan
 */


#include "Player_Test.h"

void PlayerTest::Run_Create()
{
	EXPECT_EQ(_name,_player.GetName());
	EXPECT_EQ(_initBalance,_player.GetBalance());

}
