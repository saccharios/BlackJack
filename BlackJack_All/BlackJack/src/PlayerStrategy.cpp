/*
 * PlayerStrategy.cpp
 *
 *  Created on: 16.03.2017
 *      Author: Stefan
 */

#include "PlayerStrategy.h"
#include <map>
#include <string>
#include "GlobalDeclarations.h"

// Build strategy at compile time
using Key = std::tuple<unsigned int, bool, bool, bool, unsigned int>;

const std::map<Key,std::string> AIPlayer_Optimal::optimalStrategy = {
		// Define not-soft, not-paired hands
		//{Key{  Value, isSoft, isPair, isAces, Dealer Value}, Action }
		//  Value 21
		{Key{21,false,false,false,2},STAND},
		{Key{21,false,false,false,3},STAND},
		{Key{21,false,false,false,4},STAND},
		{Key{21,false,false,false,5},STAND},
		{Key{21,false,false,false,6},STAND},
		{Key{21,false,false,false,7},STAND},
		{Key{21,false,false,false,8},STAND},
		{Key{21,false,false,false,9},STAND},
		{Key{21,false,false,false,10},STAND},
		{Key{21,false,false,false,11},STAND},
		//  Value 20
		{Key{20,false,false,false,2},STAND},
		{Key{20,false,false,false,3},STAND},
		{Key{20,false,false,false,4},STAND},
		{Key{20,false,false,false,5},STAND},
		{Key{20,false,false,false,6},STAND},
		{Key{20,false,false,false,7},STAND},
		{Key{20,false,false,false,8},STAND},
		{Key{20,false,false,false,9},STAND},
		{Key{20,false,false,false,10},STAND},
		{Key{20,false,false,false,11},STAND},
		//  Value 19
		{Key{19,false,false,false,2},STAND},
		{Key{19,false,false,false,3},STAND},
		{Key{19,false,false,false,4},STAND},
		{Key{19,false,false,false,5},STAND},
		{Key{19,false,false,false,6},STAND},
		{Key{19,false,false,false,7},STAND},
		{Key{19,false,false,false,8},STAND},
		{Key{19,false,false,false,9},STAND},
		{Key{19,false,false,false,10},STAND},
		{Key{19,false,false,false,11},STAND},
		//  Value 18
		{Key{18,false,false,false,2},STAND},
		{Key{18,false,false,false,3},STAND},
		{Key{18,false,false,false,4},STAND},
		{Key{18,false,false,false,5},STAND},
		{Key{18,false,false,false,6},STAND},
		{Key{18,false,false,false,7},STAND},
		{Key{18,false,false,false,8},STAND},
		{Key{18,false,false,false,9},STAND},
		{Key{18,false,false,false,10},STAND},
		{Key{18,false,false,false,11},STAND},
		//  Value 17
		{Key{17,false,false,false,2},STAND},
		{Key{17,false,false,false,3},STAND},
		{Key{17,false,false,false,4},STAND},
		{Key{17,false,false,false,5},STAND},
		{Key{17,false,false,false,6},STAND},
		{Key{17,false,false,false,7},STAND},
		{Key{17,false,false,false,8},STAND},
		{Key{17,false,false,false,9},STAND},
		{Key{17,false,false,false,10},STAND},
		{Key{17,false,false,false,11},STAND},
		//  Value 16
		{Key{16,false,false,false,2},STAND},
		{Key{16,false,false,false,3},STAND},
		{Key{16,false,false,false,4},STAND},
		{Key{16,false,false,false,5},STAND},
		{Key{16,false,false,false,6},STAND},
		{Key{16,false,false,false,7},HIT},
		{Key{16,false,false,false,8},HIT},
		{Key{16,false,false,false,9},HIT},
		{Key{16,false,false,false,10},HIT},
		{Key{16,false,false,false,11},HIT},
		//  Value 15
		{Key{15,false,false,false,2},STAND},
		{Key{15,false,false,false,3},STAND},
		{Key{15,false,false,false,4},STAND},
		{Key{15,false,false,false,5},STAND},
		{Key{15,false,false,false,6},STAND},
		{Key{15,false,false,false,7},HIT},
		{Key{15,false,false,false,8},HIT},
		{Key{15,false,false,false,9},HIT},
		{Key{15,false,false,false,10},HIT},
		{Key{15,false,false,false,11},HIT},
		//  Value 14
		{Key{14,false,false,false,2},STAND},
		{Key{14,false,false,false,3},STAND},
		{Key{14,false,false,false,4},STAND},
		{Key{14,false,false,false,5},STAND},
		{Key{14,false,false,false,6},STAND},
		{Key{14,false,false,false,7},HIT},
		{Key{14,false,false,false,8},HIT},
		{Key{14,false,false,false,9},HIT},
		{Key{14,false,false,false,10},HIT},
		{Key{14,false,false,false,11},HIT},
		//  Value 13
		{Key{13,false,false,false,2},STAND},
		{Key{13,false,false,false,3},STAND},
		{Key{13,false,false,false,4},STAND},
		{Key{13,false,false,false,5},STAND},
		{Key{13,false,false,false,6},STAND},
		{Key{13,false,false,false,7},HIT},
		{Key{13,false,false,false,8},HIT},
		{Key{13,false,false,false,9},HIT},
		{Key{13,false,false,false,10},HIT},
		{Key{13,false,false,false,11},HIT},
		//  Value 12
		{Key{12,false,false,false,2},HIT},
		{Key{12,false,false,false,3},HIT},
		{Key{12,false,false,false,4},STAND},
		{Key{12,false,false,false,5},STAND},
		{Key{12,false,false,false,6},STAND},
		{Key{12,false,false,false,7},HIT},
		{Key{12,false,false,false,8},HIT},
		{Key{12,false,false,false,9},HIT},
		{Key{12,false,false,false,10},HIT},
		{Key{12,false,false,false,11},HIT},
		//  Value 11
		{Key{11,false,false,false,2},DOUBLE},
		{Key{11,false,false,false,3},DOUBLE},
		{Key{11,false,false,false,4},DOUBLE},
		{Key{11,false,false,false,5},DOUBLE},
		{Key{11,false,false,false,6},DOUBLE},
		{Key{11,false,false,false,7},DOUBLE},
		{Key{11,false,false,false,8},DOUBLE},
		{Key{11,false,false,false,9},DOUBLE},
		{Key{11,false,false,false,10},DOUBLE},
		{Key{11,false,false,false,11},HIT},
		//  Value 10
		{Key{10,false,false,false,2},DOUBLE},
		{Key{10,false,false,false,3},DOUBLE},
		{Key{10,false,false,false,4},DOUBLE},
		{Key{10,false,false,false,5},DOUBLE},
		{Key{10,false,false,false,6},DOUBLE},
		{Key{10,false,false,false,7},DOUBLE},
		{Key{10,false,false,false,8},DOUBLE},
		{Key{10,false,false,false,9},DOUBLE},
		{Key{10,false,false,false,10},HIT},
		{Key{10,false,false,false,11},HIT},
		//  Value 9
		{Key{9,false,false,false,2},HIT},
		{Key{9,false,false,false,3},DOUBLE},
		{Key{9,false,false,false,4},DOUBLE},
		{Key{9,false,false,false,5},DOUBLE},
		{Key{9,false,false,false,6},DOUBLE},
		{Key{9,false,false,false,7},HIT},
		{Key{9,false,false,false,8},HIT},
		{Key{9,false,false,false,9},HIT},
		{Key{9,false,false,false,10},HIT},
		{Key{9,false,false,false,11},HIT},
		//  Value 8
		{Key{8,false,false,false,2},HIT},
		{Key{8,false,false,false,3},HIT},
		{Key{8,false,false,false,4},HIT},
		{Key{8,false,false,false,5},HIT},
		{Key{8,false,false,false,6},HIT},
		{Key{8,false,false,false,7},HIT},
		{Key{8,false,false,false,8},HIT},
		{Key{8,false,false,false,9},HIT},
		{Key{8,false,false,false,10},HIT},
		{Key{8,false,false,false,11},HIT},
		//  Value 7
		{Key{7,false,false,false,2},HIT},
		{Key{7,false,false,false,3},HIT},
		{Key{7,false,false,false,4},HIT},
		{Key{7,false,false,false,5},HIT},
		{Key{7,false,false,false,6},HIT},
		{Key{7,false,false,false,7},HIT},
		{Key{7,false,false,false,8},HIT},
		{Key{7,false,false,false,9},HIT},
		{Key{7,false,false,false,10},HIT},
		{Key{7,false,false,false,11},HIT},
		//  Value 6
		{Key{6,false,false,false,2},HIT},
		{Key{6,false,false,false,3},HIT},
		{Key{6,false,false,false,4},HIT},
		{Key{6,false,false,false,5},HIT},
		{Key{6,false,false,false,6},HIT},
		{Key{6,false,false,false,7},HIT},
		{Key{6,false,false,false,8},HIT},
		{Key{6,false,false,false,9},HIT},
		{Key{6,false,false,false,10},HIT},
		{Key{6,false,false,false,11},HIT},
		//  Value 5
		{Key{5,false,false,false,2}, HIT},
		{Key{5,false,false,false,3},HIT},
		{Key{5,false,false,false,4},HIT},
		{Key{5,false,false,false,5},HIT},
		{Key{5,false,false,false,6},HIT},
		{Key{5,false,false,false,7},HIT},
		{Key{5,false,false,false,8},HIT},
		{Key{5,false,false,false,9},HIT},
		{Key{5,false,false,false,10},HIT},
		{Key{5,false,false,false,11},HIT},

		// Define soft, non pair hands
		//{Key{  Value, isSoft, isPair, isAces, Dealer Value}, Action }
		//  Value Soft 21
		{Key{21,true,false,false,2},STAND},
		{Key{21,true,false,false,3},STAND},
		{Key{21,true,false,false,4},STAND},
		{Key{21,true,false,false,5},STAND},
		{Key{21,true,false,false,6},STAND},
		{Key{21,true,false,false,7},STAND},
		{Key{21,true,false,false,8},STAND},
		{Key{21,true,false,false,9},STAND},
		{Key{21,true,false,false,10},STAND},
		{Key{21,true,false,false,11},STAND},
		//  Value Soft  20
		{Key{20,true,false,false,2},STAND},
		{Key{20,true,false,false,3},STAND},
		{Key{20,true,false,false,4},STAND},
		{Key{20,true,false,false,5},STAND},
		{Key{20,true,false,false,6},STAND},
		{Key{20,true,false,false,7},STAND},
		{Key{20,true,false,false,8},STAND},
		{Key{20,true,false,false,9},STAND},
		{Key{20,true,false,false,10},STAND},
		{Key{20,true,false,false,11},STAND},
		//  Value Soft  19
		{Key{19,true,false,false,2},STAND},
		{Key{19,true,false,false,3},STAND},
		{Key{19,true,false,false,4},STAND},
		{Key{19,true,false,false,5},STAND},
		{Key{19,true,false,false,6},STAND},
		{Key{19,true,false,false,7},STAND},
		{Key{19,true,false,false,8},STAND},
		{Key{19,true,false,false,9},STAND},
		{Key{19,true,false,false,10},STAND},
		{Key{19,true,false,false,11},STAND},
		//  Value Soft  18
		{Key{18,true,false,false,2},STAND},
		{Key{18,true,false,false,3},DOUBLE},
		{Key{18,true,false,false,4},DOUBLE},
		{Key{18,true,false,false,5},DOUBLE},
		{Key{18,true,false,false,6},DOUBLE},
		{Key{18,true,false,false,7},STAND},
		{Key{18,true,false,false,8},STAND},
		{Key{18,true,false,false,9},HIT},
		{Key{18,true,false,false,10},HIT},
		{Key{18,true,false,false,11},HIT},
		//  Value Soft  17
		{Key{17,true,false,false,2},HIT},
		{Key{17,true,false,false,3},DOUBLE},
		{Key{17,true,false,false,4},DOUBLE},
		{Key{17,true,false,false,5},DOUBLE},
		{Key{17,true,false,false,6},DOUBLE},
		{Key{17,true,false,false,7},HIT},
		{Key{17,true,false,false,8},HIT},
		{Key{17,true,false,false,9},HIT},
		{Key{17,true,false,false,10},HIT},
		{Key{17,true,false,false,11},HIT},
		//  Value Soft  16
		{Key{16,true,false,false,2},HIT},
		{Key{16,true,false,false,3},HIT},
		{Key{16,true,false,false,4},DOUBLE},
		{Key{16,true,false,false,5},DOUBLE},
		{Key{16,true,false,false,6},DOUBLE},
		{Key{16,true,false,false,7},HIT},
		{Key{16,true,false,false,8},HIT},
		{Key{16,true,false,false,9},HIT},
		{Key{16,true,false,false,10},HIT},
		{Key{16,true,false,false,11},HIT},
		//  Value Soft  15
		{Key{15,true,false,false,2},HIT},
		{Key{15,true,false,false,3},HIT},
		{Key{15,true,false,false,4},DOUBLE},
		{Key{15,true,false,false,5},DOUBLE},
		{Key{15,true,false,false,6},DOUBLE},
		{Key{15,true,false,false,7},HIT},
		{Key{15,true,false,false,8},HIT},
		{Key{15,true,false,false,9},HIT},
		{Key{15,true,false,false,10},HIT},
		{Key{15,true,false,false,11},HIT},
		//  Value Soft  14
		{Key{14,true,false,false,2},HIT},
		{Key{14,true,false,false,3},HIT},
		{Key{14,true,false,false,4},HIT},
		{Key{14,true,false,false,5},DOUBLE},
		{Key{14,true,false,false,6},DOUBLE},
		{Key{14,true,false,false,7},HIT},
		{Key{14,true,false,false,8},HIT},
		{Key{14,true,false,false,9},HIT},
		{Key{14,true,false,false,10},HIT},
		{Key{14,true,false,false,11},HIT},
		//  Value Soft  13
		{Key{13,true,false,false,2},HIT},
		{Key{13,true,false,false,3},HIT},
		{Key{13,true,false,false,4},HIT},
		{Key{13,true,false,false,5},DOUBLE},
		{Key{13,true,false,false,6},DOUBLE},
		{Key{13,true,false,false,7},HIT},
		{Key{13,true,false,false,8},HIT},
		{Key{13,true,false,false,9},HIT},
		{Key{13,true,false,false,10},HIT},
		{Key{13,true,false,false,11},HIT},
		// Define pairs
		//{Key{  Value, isSoft, isPair, isAces, Dealer Value}, Action }
		// Pair Aces
		{Key{12,true,true,true,2},SPLIT},
		{Key{12,true,true,true,3},SPLIT},
		{Key{12,true,true,true,4},SPLIT},
		{Key{12,true,true,true,5},SPLIT},
		{Key{12,true,true,true,6},SPLIT},
		{Key{12,true,true,true,7},SPLIT},
		{Key{12,true,true,true,8},SPLIT},
		{Key{12,true,true,true,9},SPLIT},
		{Key{12,true,true,true,10},SPLIT},
		{Key{12,true,true,true,11},SPLIT},
		// Pair Tens, Jacks, Queens, Kings
		{Key{20,false,true,false,2},STAND},
		{Key{20,false,true,false,3},STAND},
		{Key{20,false,true,false,4},STAND},
		{Key{20,false,true,false,5},STAND},
		{Key{20,false,true,false,6},STAND},
		{Key{20,false,true,false,7},STAND},
		{Key{20,false,true,false,8},STAND},
		{Key{20,false,true,false,9},STAND},
		{Key{20,false,true,false,10},STAND},
		{Key{20,false,true,false,11},STAND},
		// Pair Nines
		{Key{18,false,true,false,2},SPLIT},
		{Key{18,false,true,false,3},SPLIT},
		{Key{18,false,true,false,4},SPLIT},
		{Key{18,false,true,false,5},SPLIT},
		{Key{18,false,true,false,6},SPLIT},
		{Key{18,false,true,false,7},STAND},
		{Key{18,false,true,false,8},SPLIT},
		{Key{18,false,true,false,9},SPLIT},
		{Key{18,false,true,false,10},STAND},
		{Key{18,false,true,false,11},STAND},
		// Pair Eights
		{Key{16,false,true,false,2},SPLIT},
		{Key{16,false,true,false,3},SPLIT},
		{Key{16,false,true,false,4},SPLIT},
		{Key{16,false,true,false,5},SPLIT},
		{Key{16,false,true,false,6},SPLIT},
		{Key{16,false,true,false,7},SPLIT},
		{Key{16,false,true,false,8},SPLIT},
		{Key{16,false,true,false,9},SPLIT},
		{Key{16,false,true,false,10},SPLIT},
		{Key{16,false,true,false,11},SPLIT},
		// Pair Sevens
		{Key{14,false,true,false,2},SPLIT},
		{Key{14,false,true,false,3},SPLIT},
		{Key{14,false,true,false,4},SPLIT},
		{Key{14,false,true,false,5},SPLIT},
		{Key{14,false,true,false,6},SPLIT},
		{Key{14,false,true,false,7},SPLIT},
		{Key{14,false,true,false,8},HIT},
		{Key{14,false,true,false,9},HIT},
		{Key{14,false,true,false,10},HIT},
		{Key{14,false,true,false,11},HIT},
		// Pair Sixes
		{Key{12,false,true,false,2},SPLIT},
		{Key{12,false,true,false,3},SPLIT},
		{Key{12,false,true,false,4},SPLIT},
		{Key{12,false,true,false,5},SPLIT},
		{Key{12,false,true,false,6},SPLIT},
		{Key{12,false,true,false,7},HIT},
		{Key{12,false,true,false,8},HIT},
		{Key{12,false,true,false,9},HIT},
		{Key{12,false,true,false,10},HIT},
		{Key{12,false,true,false,11},HIT},
		// Pair Fives
		{Key{10,false,true,false,2},DOUBLE},
		{Key{10,false,true,false,3},DOUBLE},
		{Key{10,false,true,false,4},DOUBLE},
		{Key{10,false,true,false,5},DOUBLE},
		{Key{10,false,true,false,6},DOUBLE},
		{Key{10,false,true,false,7},DOUBLE},
		{Key{10,false,true,false,8},DOUBLE},
		{Key{10,false,true,false,9},DOUBLE},
		{Key{10,false,true,false,10},HIT},
		{Key{10,false,true,false,11},HIT},
		// Pair Fours
		{Key{8,false,true,false,2},HIT},
		{Key{8,false,true,false,3},HIT},
		{Key{8,false,true,false,4},HIT},
		{Key{8,false,true,false,5},SPLIT},
		{Key{8,false,true,false,6},SPLIT},
		{Key{8,false,true,false,7},HIT},
		{Key{8,false,true,false,8},HIT},
		{Key{8,false,true,false,9},HIT},
		{Key{8,false,true,false,10},HIT},
		{Key{8,false,true,false,11},HIT},
		// Pair Threes
		{Key{6,false,true,false,2},SPLIT},
		{Key{6,false,true,false,3},SPLIT},
		{Key{6,false,true,false,4},SPLIT},
		{Key{6,false,true,false,5},SPLIT},
		{Key{6,false,true,false,6},SPLIT},
		{Key{6,false,true,false,7},SPLIT},
		{Key{6,false,true,false,8},HIT},
		{Key{6,false,true,false,9},HIT},
		{Key{6,false,true,false,10},HIT},
		{Key{6,false,true,false,11},HIT},
		// Pair Twos
		{Key{4,false,true,false,2},SPLIT},
		{Key{4,false,true,false,3},SPLIT},
		{Key{4,false,true,false,4},SPLIT},
		{Key{4,false,true,false,5},SPLIT},
		{Key{4,false,true,false,6},SPLIT},
		{Key{4,false,true,false,7},SPLIT},
		{Key{4,false,true,false,8},HIT},
		{Key{4,false,true,false,9},HIT},
		{Key{4,false,true,false,10},HIT},
		{Key{4,false,true,false,11},HIT}
};


