/*
 * UserInput.cpp
 *
 *  Created on: 19.01.2017
 *      Author: Stefan
 */

#include <iostream>
#include <string>
#include <sstream>
#include "UserInput.h"
#include "GlobalDeclarations.h"

void UserInput::PrintStringSet (std::set<std::string> const & stringSet)
{
	std::cout << " ";
	for(auto const & str : stringSet)
	{
		std::cout << "("<< str << ") ";
	}
	std::cout << std::endl;
}
std::string UserInput::ReadInAction(std::set<std::string> const & stringSet)
{
	std::string readIn;
	PrintStringSet(stringSet);
	std::getline (std::cin, readIn);
	while(stringSet.find(readIn) == stringSet.end())
	{
		std::cout << "Enter";
		PrintStringSet(stringSet);
		std::getline (std::cin, readIn);
	}
	return readIn;
}


std::string UserInput::ReadInName(std::size_t const & numPlayer)
{
	std::string name;
	std::string readIn;
	std::cout << "Enter name of player " << numPlayer <<": " << std::endl;
	std::getline (std::cin, readIn);
	std::stringstream(readIn) >> name;

	if( name.size() > maxChars )
	{
		std::cout << "Your name is too long, truncating after " << maxChars << " characters." << std::endl;
		name = name.substr( 0, maxChars ) ;
	}
	return name;
}
