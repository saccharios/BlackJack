/*
 * ConsoleTest.cpp
 *
 *  Created on: 13.02.2017
 *      Author: Stefan
 */

#include "ConsoleTest.h"

void Console_Test::Run_Write()
{
	_out_stream.open("file_Write.txt");
	// Actual test
	std::string str = "The answer is 41.";
	std::stringstream strm;
	strm << str;
	_console.Write(strm);
	_out_stream.close();
	_in_stream.open("file.txt");
	std::string readIn("");
	std::getline (_in_stream, readIn);
	EXPECT_EQ(str,readIn);
	_in_stream.close();
}
void Console_Test::Run_WriteString()
{
	_out_stream.open("file_WriteString.txt");
	// Actual test
	std::string str = "The answer is 42.";
	_console.WriteString(str);
	_out_stream.close();
	_in_stream.open("file.txt");
	std::string readIn("");
	std::getline (_in_stream, readIn);
	EXPECT_EQ(str,readIn);
	_in_stream.close();
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
