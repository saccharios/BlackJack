/*
 * ConsoleTest.cpp
 *
 *  Created on: 13.02.2017
 *      Author: Stefan
 */

#include "ConsoleTest.h"
#include <set>

void Console_Test::Run_Write()
{
	// Setup test file to be read in
	std::string file_name = "file_Write.txt";
	_out_stream.open(file_name);
	std::string str = "The answer is 41.";
	// Actual tests
	std::stringstream strm;
	strm << str;
	_console.Write(strm);
	_out_stream.close();
	_in_stream.open(file_name);
	std::string readIn("");
	std::getline (_in_stream, readIn);
	EXPECT_EQ(str,readIn);
	_in_stream.close();
}
void Console_Test::Run_WriteString()
{
	// Setup test file to be read in
	std::string file_name = "file_WriteString.txt";
	_out_stream.open(file_name);
	std::string str = "The answer is 42.";
	// Actual tests
	_console.WriteString(str);
	_out_stream.close();
	_in_stream.open(file_name);
	std::string readIn("");
	std::getline (_in_stream, readIn);
	EXPECT_EQ(str,readIn);
	_in_stream.close();
}
void Console_Test::Run_PrintStringSet()
{
	std::string file_name = "file_PrintStringSet.txt";
	std::set<std::string> stringSet = {"a","b", "cde"};
	_out_stream.open(file_name);
	_console.PrintStringSet(stringSet);
	_out_stream.close();
	_in_stream.open(file_name);
	std::string readIn("");
	std::getline (_in_stream, readIn);
	std::string result = " (a) (b) (cde) ";
	EXPECT_EQ(result, readIn);
	_in_stream.close();

}
void Console_Test::Run_ReadInNumber()
{
	// Setup test file to be read in
	std::string file_name = "file_ReadInNumber";
	_out_stream.open(file_name + in);
	_out_stream << "-10" << std::endl;
	_out_stream << "0" << std::endl;
	_out_stream << "1" << std::endl;
	_out_stream << "5" << std::endl;
	_out_stream << "11" << std::endl;
	_out_stream << "10" << std::endl;
	_out_stream.close();
	_out_stream.open(file_name + out);
	_in_stream.open(file_name + in);
	double min = 1;
	double max = 10;
	// Actual tests
	// First test with -10, 0 ,1
	auto readIn = _console.ReadInNumber(min, max);
	double result = 1;
	EXPECT_EQ(result, readIn);
	// Second test with 5
	readIn = _console.ReadInNumber(min, max);
	result = 5;
	EXPECT_EQ(result, readIn);
	// Third test with 11, 10
	readIn = _console.ReadInNumber(min, max);
	result = 10;
	EXPECT_EQ(result, readIn);
	_in_stream.close();
	_out_stream.close();
}

void Console_Test::Run_ReadInAction()
{
	// Setup test file to be read in
	std::string file_name = "file_ReadInAction";
	_out_stream.open(file_name + in);
	_out_stream << "d" << std::endl;
	_out_stream << "q d" << std::endl;
	_out_stream << "3" << std::endl;
	_out_stream << "abc" << std::endl;
	_out_stream << "p 5" << std::endl;
	_out_stream << "p" << std::endl;
	_out_stream.close();
	_out_stream.open(file_name + out);
	_in_stream.open(file_name + in);
	std::set<std::string> stringSet = {"d","h", "s" ,"p"};
	// Actual tests
	// First test with "d"
	auto readIn = _console.ReadInAction(stringSet);
	std::string result = "d";
	EXPECT_EQ(result, readIn);
	// Second test with "q", "3", "abc", "p"
	readIn = _console.ReadInAction(stringSet);
	result = "p";
	EXPECT_EQ(result, readIn);
	_in_stream.close();
	_out_stream.close();
}
void Console_Test::Run_ReadInName()
{
	// Setup test file to be read in
	std::string file_name = "file_ReadInName";
	_out_stream.open(file_name + in);
	std::string gauss = "Gauss";
	std::string max = "Max Well";
	std::string einstein= "EinsteinStokesNewtonLeibnitzTuring";
	std::string tesla = "Tesla";
	std::string empty = "";
	std::string galileo = "Galileo";
	_out_stream << gauss << std::endl;
	_out_stream << max << std::endl;
	_out_stream << einstein << std::endl;
	_out_stream << " " << tesla << std::endl;
	_out_stream << empty << std::endl;
	_out_stream << galileo << std::endl;
	_out_stream.close();
	_out_stream.open(file_name + out);
	_in_stream.open(file_name + in);
	std::size_t numPlayer = 0;
	std::size_t const maxChars = 20;
	// Actual tests
	// First test with "Gauss"
	auto readIn = _console.ReadInName(++numPlayer, maxChars);
	std::string result = "Gauss";
	EXPECT_EQ(result, readIn);
	// Second test with "Max Well"
	readIn = _console.ReadInName(++numPlayer, maxChars);
	result = "Max";
	EXPECT_EQ(result, readIn);
	// Third test with "EinsteinStokesNewtonLeibnitzTuring"
	readIn = _console.ReadInName(++numPlayer, maxChars);
	result = einstein.substr( 0, maxChars );
	EXPECT_EQ(result, readIn);
	// Fourth test with " Tesla"
	readIn = _console.ReadInName(++numPlayer, maxChars);
	result = tesla;
	EXPECT_EQ(result, readIn);
	// Fifth test with "", "Galileo"
	readIn = _console.ReadInName(++numPlayer, maxChars);
	result = galileo;
	EXPECT_EQ(result, readIn);
	_in_stream.close();
	_out_stream.close();

}
