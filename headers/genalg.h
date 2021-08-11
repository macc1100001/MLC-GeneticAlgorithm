#ifndef _MY_ALGGEN_H
#define _MY_ALGGEN_H

/* https://www.gnu.org/software/gsl/doc/html/usage.html */

#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned int uint;

/*
    ToDo:
 
    1. Modify the ga_solution struct to save all posible solutions found 
    for N-Queens(this implies modifying ga_solver function to not end on 
    the first solution found, but find all of them without saving repeated solutions.).
    
    2. Modify "crossover" function to work with N-Queens
    (current implementation only works with 8-Queens).
    
    3. Implement more selection algorithms.
    
    4. Save an image of the solution representation. A chessboard(NxN) 
    with the queens in their places. And maybe also implement it to save
    every individual from each generation, to see its evolution.
 */


/*  This is the solution returned by the ga function.
    Solution(s) found are returned in this struct format */
struct ga_solution{

    uint queens; /* number of queens to found the solution */
    uint *solution;  /* Solution(s) vector of an individual */
    uint generation; /* The generation where the solution was found */

};

typedef struct ga_solution ga_solution;


/* 
    Description:    Solver for the N-Queens problem using a genetic algorithm implementation.
    Params:
       ga_solution *sol:    A pointer to a ga_solution struct where the solution found is returned.
       
       int queens:          The number of queens the solver will use to find a solution.
       
       int popSize:         The population size of all the generations(number of individuals per generation)
       
       int maxGens:         The maximum number of generations the solver will compute generations to find a solution
       
       int selflag:         Used to indicate whether to use "Roulette" or "Tournament" selection
       
       int verboseflag:     Used to indicate if the solver should print aditional information each generation
       
       double pMut:         Mutation probability used by the genetic algorithm to change an individual's genes
       
       double pCross:       Crossing probability used by the genetic algorithm to determine whether an individual
                            should be crossedover with another one. Calculated as (1 - pMut).
   
*/
ga_solution* ga_solver(uint queens, uint popSize, uint maxGens, int selflag, bool verboseflag, double pMut, double pCross);


/* 
    Description:    Used to free resources allocated by a call to "ga" function
    Params:
        ga_solution *sol:   A pointer to a ga_solution that was returned from the "ga_solver" function.
*/
void ga_free_sol(ga_solution *sol);

#endif
