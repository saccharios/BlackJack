/*
 * UserInput.h
 *
 *  Created on: 19.01.2017
 *      Author: Stefan
 */

#ifndef USERINPUT_H_
#define USERINPUT_H_
#include <set>
#include <string>
#include <iostream>

class UserInput {
public:
	static void PrintStringSet (std::set<std::string> const & stringSet);
	static std::string ReadInStr(std::set<std::string> const & stringSet);

	// Templated functions cannot be implemented in the .cpp file
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

#endif /* USERINPUT_H_ */
