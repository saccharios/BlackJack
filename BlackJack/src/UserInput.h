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
	void PrintStringSet (std::set<std::string> const & stringSet);
	std::string ReadInAction(std::set<std::string> const & stringSet);
	std::string ReadInName(std::size_t const & i);
	// Templated functions cannot be implemented in the .cpp file
	template<typename T>
	T ReadInNumber( T const & min, T const & max)
	{
		std::string readIn;
		T value;
		do
		{
			_ostream << "Enter a number between " << min << " and " << max <<"."<<std::endl;
			std::getline (_istream, readIn);
			std::stringstream(readIn) >> value;
		}while(value < min || value > max);
		_ostream << "You have entered " << value << "."<<std::endl;
		return value;
	}
	void write( std::stringstream & strm );
	void writeString( std::string const & str );
private:
	std::ostream & _ostream;
	std::istream & _istream;

};

#endif /* USERINPUT_H_ */
