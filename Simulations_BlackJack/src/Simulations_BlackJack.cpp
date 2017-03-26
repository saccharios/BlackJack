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

// TODO Profile the program

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


	SimulationGame::Setup setup;

	setup.N_Simulation_Steps = 100;
	setup.initialBalance = MAX_INIT_BALANCE;
	setup.N_Sets = MAX_SETS;
	setup.N_Basic_AIPlayers = 0;
	setup.N_Conservative_AIPlayers = 0;
	setup.N_Aggressive_AIPlayers= 0;
	setup.N_Optimal_AIPlayers = 1;

	SimulationGame game(setup);



	do
	{
		game.PlayRound();
	}while ( game.PlayAnotherRound() );

//		// TODO Add statistics for first decision of player.

	std::cout.rdbuf(coutbuf); //reset to standard output again
	out_file.close();


	std::ofstream stat_file;
	stat_file.open("statistics_output.txt");
	duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
	stat_file <<"Total elapsed time: "<< duration << " sec.\n";
	game.PrintStatistics(stat_file);
	stat_file.close();
	return 0;
}



