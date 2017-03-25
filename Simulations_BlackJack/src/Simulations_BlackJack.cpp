/*
 * Simulations_BlackJack.cpp
 *
 *  Created on: 21.03.2017
 *      Author: Stefan
 */


// TODO Make always build upon click run, ctrl f11 and in console c/c++ unit run
// Use Scons (Sconsolidate) for building three different builds in one project.
#include <memory>
#include "../../BlackJack/src/Game.h"
#include "../../BlackJack/src/Card.h"
#include "../../BlackJack/src/GlobalDeclarations.h"
#include "../../BlackJack/src/HoleCards.h"
#include <fstream>
#include <sstream>
#include <iostream>
int main(int argc, char ** argv)
{

//	std::ofstream filestream;
//	filestream.open("myFile.txt", std::ofstream::out | std::ofstream::app);
//
//	std::stringstream _out_stream;
//	std::stringstream istrm;
//
//	Console console(filestream, istrm);
//	console.WriteString("abc");
//	filestream.close();
//
//
//	filestream.open("myFile.txt", std::ofstream::out | std::ofstream::app);
//	console.WriteString("def");
//	filestream.close();


	std::ofstream out_file;
	out_file.open("simulation_output.txt");
	std::streambuf* coutbuf = std::cout.rdbuf(); //save old buf
	std::cout.rdbuf(out_file.rdbuf()); //redirect std::cout to output file




	Game game;
	game.Simulation_Setup(8,1);

	int N_Simulation_Steps = 10000;
	for(int i = 0; i < N_Simulation_Steps; ++i)
	{
		game.Simulation_PlayRound();
		// TODO Add statistics for first decision of player.
		// TODO Add mechanic to restart the game if player is broke but N_Simulation_Steps is not done yet.
		// Simulation does not print to the console. Maybe, it should not print the game, but only some statistics at the end to a file.
	}
	std::cout.rdbuf(coutbuf); //reset to standard output again
	return 0;
}



