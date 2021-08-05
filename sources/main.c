#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>

#include "genAlg.h"

void Usage(char* caller){
    fprintf(stderr, "Usage: %s [OPTIONS...]\n\
Description: A genetic algorithm implementation to solve the N-Queen problem.\n\
Options:\n\
    -q [ QUEENS ]      Sets the number of queens, default is 8\n\
    -p [ POPSIZE ]     Sets the population size, default is 10\n\
    -g [ MAXGENS ]     Sets the maximum generations to compute, default is 50\n\
    -s                 Sets the selection mode, default is \"roulette\"\n\
    -m [ PROB ]        Sets the mutation probability, default is 0.2\n\
    -v                 Verbose output\n\
    -h                 Show usage\n\
Note: Population size must be greater than 1. Number of queens must be greater than or equal to 1.\n", caller);
    exit(EXIT_FAILURE);
}

void CheckCondition(bool cond, char* caller, const char *msg){
    if(cond){
        fprintf(stderr, "%s: %s", caller, msg);
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char** argv){

    /*  population size must be greater than 1, popSize > 1
        number of queens must be greater than or equal to 1, QUEENS >= 1
     */
    int queens = 8, popSize = 10, maxGens = 50;
    int selflag = 0; /* 0 = roulette; 1 = tournament*/
    bool verboseflag = 0;
    double pMut = 0.2, pCross = 1.0 - pMut;
        
    int c;

    while((c = getopt(argc, argv, "q:p:g:sm:vh")) != -1){
        switch(c){
            case 'q':
                queens = atoi(optarg);
                CheckCondition((queens < 1), argv[0], "Number of queens must be greater than or equal to 1.\n");
                break;
            case 'p':
                popSize = atoi(optarg);
                CheckCondition((popSize <= 1), argv[0], "Population size must be greater than 1.\n");
                break;
            case 'g':
                maxGens = atoi(optarg);
                CheckCondition((maxGens < 1), argv[0], "Maximum generations must be greater than or equal to 1.\n");
                break;
            case 's':
                selflag = 1;
                break;                
            case 'm':
                pMut = atof(optarg);
                pCross = 1.0 - pMut;
                CheckCondition(((pMut >= 1.0) || (pMut < 0.0)), argv[0], "Mutation probability must be less than 1 and greater than or equal to 0.\n");
                break;
            case 'v':
                verboseflag = true;
                break;
            case 'h':
                Usage(argv[0]);
                break;
            default:
                exit(EXIT_FAILURE);
        }
    }
            
    if(verboseflag){    
        printf("Queens: %d\n", queens);
        printf("Population size: %d\n", popSize);
        printf("Maximum generations before stop: %d\n", maxGens);
        printf("Selection: %s\n", (selflag) ? "Tournament" : "Roulette");
        printf("Mutation probability: %.2f\n", pMut);
        printf("Crossover probability: %.2f\n", pCross);
        printf("Verbose output: %s\n\n", (verboseflag) ? "True" : "False");
    }
    
    ga_solution *sol = malloc(sizeof(ga_solution));
    CheckCondition((sol == NULL), argv[0], "Error: could not allocate memory.\n");
    
    ga(sol, queens, popSize, maxGens, selflag, verboseflag, pMut, pCross);
    if(sol->generation == 0){
        fprintf(stderr, "No solution found after %d generations.\n", maxGens);
        fprintf(stderr, "Hint: increase the maximum generations to compute with option \"-g [maxGens]\"\n");
    }
    else{
        printf("Solution found at generation #%d\n", sol->generation);
        printf("With queens = %d\n", sol->queens);
        printf("Solution: [ ");
        for(uint i = 0; i < sol->queens; i ++)
            printf((i == (sol->queens - 1)) ? "%d ]" : "%d, ", sol->solution[i]);
        printf("\n");
        /* Draw solution on board */
        for(uint i = 1; i < sol->queens + 1; i++){
            for(uint j = 1; j < sol->queens + 1; j++){
                if(j == sol->solution[i - 1])
                    printf("[Q]");
                else
                    printf("[ ]");
            }
            printf("\n");
        }
    }
    ga_free_sol(sol);
    return EXIT_SUCCESS;
}

