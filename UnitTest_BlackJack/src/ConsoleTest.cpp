/*
 * ConsoleTest.cpp
 *
 *  Created on: 13.02.2017
 *      Author: Stefan
 */

#include "ConsoleTest.h"

void Console_Test::Run_Write()
{
//	std::stringstream in;
//	in << "The answer is 42";
//	_console.write(in);
//	std::stringstream out;
//	out << _istream.rdbuf();
//	EXPECT_EQ(in.str(),out.str());
//	    std::string myString = out.str();
}
void Console_Test::Run_WriteString()
{
	// Redirects std::cout and std::cin to "file.txt"
	std::ifstream in("file.txt");
	_cinbuf = std::cin.rdbuf(in.rdbuf()); //save and redirect
	std::ofstream out("file.txt");
	_coutbuf = std::cout.rdbuf(out.rdbuf());//save and redirect
	std::string str = "The answer is 42.";
	_console.writeString(str);
	std::string readIn("");
	std::getline (_istream, readIn);
	EXPECT_EQ(str,readIn);
	// Restore
	std::cout.rdbuf(_coutbuf);
	std::cin.rdbuf(_cinbuf);
}
void Console_Test::Run_PrintStringSet()
{

}
void Console_Test::Run_ReadInNumber()
{

}

void Console_Test::Run_ReadInAction()
{

}
void Console_Test::Run_ReadInName()
{

}
