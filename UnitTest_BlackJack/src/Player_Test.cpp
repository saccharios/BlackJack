/*
 * Player_Test.cpp
 *
 *  Created on: 30.01.2017
 *      Author: Stefan
 */


#include "Player_Test.h"
#include "../../BlackJack/src/HandManager.h"
#include "../../BlackJack/src/GlobalDeclarations.h"
#include <iostream>
#include <fstream>

void PlayerTest::Run_Create()
{
	EXPECT_EQ(_name,_player.GetName());
	EXPECT_EQ(_initBalance,_player.GetBalance());
}

void PlayerTest::Run_Start()
{
	EXPECT_EQ(0u,_player.GetNumHands());
	_player.Start();
	EXPECT_EQ(1u,_player.GetNumHands());
}


void PlayerTest::Run_Hit()
{
	_player.SetWager(_originalWager);
	_player.Hit(_hand);
	EXPECT_EQ(_initBalance- _originalWager, _player.GetBalance());
}
void PlayerTest::Run_Stand()
{
	_player.SetWager(_originalWager);
	_player.Stand(_hand);
	EXPECT_EQ(_initBalance - _originalWager, _player.GetBalance());
}
void PlayerTest::Run_Split()
{
	_player.SetWager(_originalWager);
	_hand->Start();
	_player.Split(_hand);
	EXPECT_EQ(_initBalance - 2.0*_originalWager, _player.GetBalance());
	EXPECT_EQ(1u, _player.GetNumHands());
}
void PlayerTest::Run_Double()
{
	_player.SetWager(_originalWager);
	_player.Double(_hand);
	EXPECT_EQ(_initBalance - 2.0*_originalWager, _player.GetBalance());
}

void PlayerTest::Run_SetWager()
{
	_player.SetWager(_originalWager);
	EXPECT_EQ(_initBalance - _originalWager, _player.GetBalance());
}


void PlayerTest::Run_SetWagerMin_DEATH()
{
	EXPECT_DEATH(_player.SetWager(MIN_WAGER-1),"");
}
void PlayerTest::Run_SetWagerMax_DEATH()
{
	EXPECT_DEATH(_player.SetWager(MAX_WAGER+1),"");
}

void PlayerTest::Run_AddToBalance()
{
	double value = 1.0;
	_player.AddToBalance(value);
	EXPECT_EQ(_initBalance + value, _player.GetBalance());
}
void PlayerTest::Run_SubractFromBalance()
{
	double value = 1.0;
	_player.SubtractFromBalance(value);
	EXPECT_EQ(_initBalance - value, _player.GetBalance());
}

void PlayerTest::Run_PutCardsBack()
{
	_player.Start();
	auto hand = pHandManager(new HandManager(_deck, _originalWager,1));
	hand->Start();
	_player.AddHand(std::move(hand));
	EXPECT_EQ(2u, _player.GetNumHands());
	EXPECT_EQ(_numDecks*52u - 4u, _deck.Size());
	_player.PutCardsBack();
	EXPECT_EQ(0u, _player.GetNumHands());
	EXPECT_EQ(_numDecks*52u, _deck.Size());
}
void PlayerTest::Run_GetAvailableActionSet()
{
	_player.SetWager(_player.GetBalance()/2.0 + 1.0); // wager is more than half the balance
	_player.Start();
	EXPECT_EQ(ACTION_STANDARD, _player.GetAvailableActionSet(ACTION_DOUBLE));
	EXPECT_EQ(ACTION_STANDARD, _player.GetAvailableActionSet(ACTION_SPLIT_DOUBLE));
	EXPECT_EQ(ACTION_STANDARD, _player.GetAvailableActionSet(ACTION_STANDARD));

	_player.PrintBalance();
	_player.PutCardsBack();
	_player.SetWager(_player.GetBalance()/2.0 - 1.0); // wager is less than half the balance
	_player.Start();
	EXPECT_EQ(ACTION_DOUBLE, _player.GetAvailableActionSet(ACTION_DOUBLE));
	EXPECT_EQ(ACTION_SPLIT_DOUBLE, _player.GetAvailableActionSet(ACTION_SPLIT_DOUBLE));
	EXPECT_EQ(ACTION_STANDARD, _player.GetAvailableActionSet(ACTION_STANDARD));
}

void PlayerTest::Run_Play()
{

	std::string file_name = "file_Player";
	std::ifstream in_stream_cin(file_name + "_in.txt");
	auto cinbuf = std::cin.rdbuf(in_stream_cin.rdbuf()); //save and redirect
	std::ofstream out_stream_cout(file_name + "_out.txt");
	auto coutbuf = std::cout.rdbuf(out_stream_cout.rdbuf()); //save and redirect

	// First test, play one hand
	std::ofstream out_stream;
	out_stream.open(file_name + "_in.txt");
	out_stream << "h\n" << "h\n" << "h\n" << "s" << std::endl;
	out_stream << "d\n" << "h\n" << "h\n" << "s\n" << std::endl;
	out_stream.close();
	_player.SetWager(1.0);
	_player.Start();
	_player.Play();
	_player.Evaluate(false, false, 17);
	_player.PrintBalance();
	// The cards drawn (and hence their value) depend on the seed of the deck.
	EXPECT_EQ( _initBalance + _originalWager, _player.GetBalance());
	_player.PutCardsBack();
	auto balance = _player.GetBalance();
	// Second test with double as action and two hands
	_player.SetWager(1.0);
	_player.Start();
	// Emulate splitting (cant set balance though)
	auto newHand = std::unique_ptr<HandManager>(new HandManager(_deck, _originalWager, handNr + 1 ));
	newHand->Start();
	_player.AddHand(std::move(newHand));
	_player.Play();
	_player.Evaluate(false, false, 17);
	_player.PrintBalance();
	EXPECT_EQ( balance - 2.0*_originalWager, _player.GetBalance());
	_player.PutCardsBack();


    std::cin.rdbuf(cinbuf);   //reset to standard input again
    std::cout.rdbuf(coutbuf); //reset to standard output again
}
