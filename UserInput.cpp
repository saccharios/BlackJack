/*
 * UserInput.cpp
 *
 *  Created on: 19.01.2017
 *      Author: Stefan
 */

#include "UserInput.h"
#include <iostream>
#include <string>
#include <sstream>
void UserInput::PrintStringSet (std::set<std::string> const & stringSet)
{
	std::cout << " ";
	for(auto const & str : stringSet)
	{
		std::cout << "("<< str << ") ";
	}
	std::cout << std::endl;
}
std::string UserInput::ReadInStr(std::set<std::string> const & stringSet)
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

