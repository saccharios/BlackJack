/*
 * Simulations_BlackJack.cpp
 *
 *  Created on: 21.03.2017
 *      Author: Stefan
 */


// TODO Use Scons (Sconsolidate) for building three different builds in one project.
#include <memory>
#include "../../BlackJack/src/SimulationGame.h"
#include "../../BlackJack/src/Card.h"
#include "../../BlackJack/src/GlobalDeclarations.h"
#include "../../BlackJack/src/HoleCards.h"
#include <fstream>
#include <sstream>
#include <iostream>

#include <ctime>

int main(int argc, char ** argv)
{
    std::clock_t start;
    double duration;

    start = std::clock();
    // TODO EV calculation for "always hit" "always stand" "dealer" "optimal" strategies.
    // TODO simple rederict std::cout buffer to a file. Is there a better solution to
    // reset the output strem of the console?
	std::ofstream out_file;
	out_file.open("simulation_output.txt");
	std::streambuf* coutbuf = std::cout.rdbuf(); //save old buf
	std::cout.rdbuf(out_file.rdbuf()); //redirect std::cout to output file




	SimulationGame game;
	game.Setup(8,1);

	int N_Simulation_Steps = 1000;
	for(int i = 0; i < N_Simulation_Steps; ++i)
	{
		game.PlayRound();
		// TODO Add statistics for first decision of player.
		// TODO Add mechanic to restart the game if player is broke but N_Simulation_Steps is not done yet.
		// Simulation does not print to the console. Maybe, it should not print the game, but only some statistics at the end to a file.
	}

	std::cout.rdbuf(coutbuf); //reset to standard output again
	out_file.close();

	std::ofstream stat_file;
	stat_file.open("statistics_output.txt");
	duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
	stat_file <<"Total elapsed time: "<< duration << " sec.\n";
	stat_file.close();
	return 0;
}



