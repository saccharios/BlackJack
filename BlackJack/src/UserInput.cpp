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


void UserInput::write( std::stringstream & strm )
{
	_ostream << strm.str();
}
void UserInput::writeString( std::string const & str )
{
	_ostream << str;
}


void UserInput::PrintStringSet (std::set<std::string> const & stringSet)
{
	// Print possible user input strings defined in stringSet
	_ostream << " ";
	for(auto const & str : stringSet)
	{
		_ostream << "("<< str << ") ";
	}
	_ostream<< std::endl;
}
std::string UserInput::ReadInAction(std::set<std::string> const & stringSet)
{
	// Read in an action from user that is in stringSet
	std::string readIn("");
	auto i = 0u;
	do
	{
		if(++i > 1)
		{
			_ostream << "Enter";
		}
		PrintStringSet(stringSet);
		std::getline (_istream, readIn);
	}while(stringSet.find(readIn) == stringSet.end());
	return readIn;
}


std::string UserInput::ReadInName(std::size_t const & numPlayer)
{
	// Read in user input name for current player with number numPlayer
	std::string name("");
	std::string readIn("");
	_ostream << "Enter name of player " << numPlayer <<": " << std::endl;
	std::getline (_istream, readIn);
	std::stringstream(readIn) >> name;

	if( name.size() > maxChars )
	{
		_ostream << "Your name is too long, truncating after " << maxChars << " characters." << std::endl;
		name = name.substr( 0, maxChars ) ;
	}
	return name;
}
