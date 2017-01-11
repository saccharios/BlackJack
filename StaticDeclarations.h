/*
 * StaticDeclarations.h
 *
 *  Created on: 17.10.2016
 *      Author: Stefan
 */

#ifndef STATICDECLARATIONS_H_
#define STATICDECLARATIONS_H_


#include <set>
#include <array>
#include <iostream>
#include <string>
#include <sstream>


static constexpr float minWager = 1.0;
static constexpr std::size_t maxDecks = 8;
static constexpr std::size_t maxPlayers = 8;
static constexpr float minInitBalance = 1.0;
static constexpr float maxInitBalance = 100000.0;

const std::array<std::string,4> Suit{"h","d","c","s"};
const std::array<std::string,13> Face{"2","3","4","5","6","7","8","9","T","J","Q","K","A"};

const std::set<std::string> SplitDouble{"h","s","d","p"};
const std::set<std::string> Double{"h","s","d"};
const std::set<std::string> Standard{"h","s"};

class UserInput {
public:
	static void PrintStringSet (std::set<std::string> const & stringSet)
	{
		std::cout << " ";
		for(auto const & str : stringSet)
		{
			std::cout << "("<< str << ") ";
		}
		std::cout << std::endl;
	}
	static std::string ReadInStr(std::set<std::string> const & stringSet)
	{
	    std::string readIn;
	    PrintStringSet(stringSet);
	    std::getline (std::cin, readIn);
	    while(stringSet.find(readIn) ==stringSet.end())
	    {
	        std::cout << "Enter";
	        PrintStringSet(stringSet);
	        std::getline (std::cin, readIn);
	    }
	    return readIn;
	}

	template<typename T>
	static T ReadInNumber( T const & min, T const & max)
	{
	    std::string readIn;
	    T value;
	    do
	    {
	        std::cout << "Enter a number between " << min << " and " << max <<"."<<std::endl;
	        std::getline (std::cin, readIn);
	        std::stringstream(readIn) >> value;
	    }while(value < min || value > max);
	    std::cout << "You have entered " << value << "."<<std::endl;
	    return value;
	}
};
#endif
