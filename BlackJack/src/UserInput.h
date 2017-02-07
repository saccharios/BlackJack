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
#include <sstream>

class UserInput {
public:
	UserInput (std::ostream & ostrm, std::istream & istrm) : _ostream(ostrm), _istream(istrm) {}
	static void PrintStringSet (std::set<std::string> const & stringSet);
	static std::string ReadInAction(std::set<std::string> const & stringSet);
	static std::string ReadInName(std::size_t const & i);
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
	void write( std::stringstream & strm )
	{
		_ostream << strm.str();
	}

private:
	std::ostream & _ostream;
	std::istream & _istream;

};

#endif /* USERINPUT_H_ */
