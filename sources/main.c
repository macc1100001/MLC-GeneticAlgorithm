#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <plot.h>

#include "genalg.h"


static void draw_solution(uint queens, uint *solution, const char* filename){
    plPlotter *plotter;
    plPlotterParams *plotter_params;
    
    FILE *chessboard_img = fopen(filename, "w+");
    if(chessboard_img == NULL){
        fprintf(stderr, "Couldn't create the image file");
        return;
    }
    
    plotter_params = pl_newplparams();
    pl_setplparam(plotter_params, "BITMAPSIZE", "480x480");
    plotter = pl_newpl_r("png", stdin, chessboard_img, stderr,
                             plotter_params);
    pl_openpl_r(plotter);
    pl_fspace_r(plotter, 0, 0, 480.0, 480.0);
    pl_pencolorname_r(plotter, "black");
    pl_linewidth_r(plotter, 1);
    pl_fontsize_r(plotter, 20);
    pl_erase_r(plotter);
    pl_fmove_r(plotter, 0.0, 0.0);
    
    double width_x = 480.0/queens;
    double width_y = 480.0/queens;
    double labelsize = pl_labelwidth_r(plotter, "Q");
    
    for(uint i = 1; i < queens; i++){
        pl_fline_r(plotter, 0.0, i*width_x, 480.0, i*width_x);
        pl_fline_r(plotter, i*width_y, 0.0, i*width_y, 480.0);
    }
    
    for(uint i = 1; i < 2*queens; i = i + 2){
        for(uint j = 1; j < 2*queens; j = j + 2){
            pl_fmove_r(plotter, j*width_y/2 - labelsize/2,
                       (2*queens - i)*width_x/2 - labelsize/2);
            if(solution[(i - 1)/2] == ((j - 1)/2) + 1)
                pl_label_r(plotter, "Q");
        }
    }
        
    pl_closepl_r(plotter);
    pl_deletepl_r(plotter);
    fclose(chessboard_img);
}

static void usage(char* caller){
    fprintf(stderr, "Usage: %s [OPTIONS...]\n\
Description: A genetic algorithm implementation to solve the N-Queen problem.\n\n\
Options:\n\n\
    -q [ QUEENS ]      Sets the number of queens, default is 8\n\
    -p [ POPSIZE ]     Sets the population size, default is 10\n\
    -g [ MAXGENS ]     Sets the maximum generations to compute, default is 50\n\
    -s                 Sets the selection mode, default is \"roulette\"\n\
    -m [ PROB ]        Sets the mutation probability, default is 0.2\n\
    -i                 Prints the solution to an imagefile called \"solution.png\"\n\
    -v                 Verbose output\n\
    -h                 Show usage\n\
Note: Population size must be greater than 1. Number of queens must be greater than or equal to 1.\n", caller);
    exit(EXIT_FAILURE);
}

static void check_condition(bool cond, char* caller, const char *msg){
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
    bool verboseflag = false, imageflag = false;
    double pMut = 0.2, pCross = 1.0 - pMut;
    //char* filename = "solution.png";
        
    int c;

    while((c = getopt(argc, argv, "iq:p:g:sm:vh")) != -1){
        switch(c){
            case 'q':
                queens = atoi(optarg);
                check_condition((queens < 1), argv[0],
                "Number of queens must be greater than or equal to 1.\n");
                break;
            case 'p':
                popSize = atoi(optarg);
                check_condition((popSize <= 1), argv[0],
                "Population size must be greater than 1.\n");
                break;
            case 'g':
                maxGens = atoi(optarg);
                check_condition((maxGens < 1), argv[0],
                "Maximum generations must be greater than or equal to 1.\n");
                break;
            case 's':
                selflag = 1;
                break;                
            case 'm':
                pMut = atof(optarg);
                pCross = 1.0 - pMut;
                check_condition(((pMut >= 1.0) || (pMut < 0.0)),
                argv[0], "Mutation probability must be less than 1 and greater than or equal to 0.\n");
                break;
            case 'v':
                verboseflag = true;
                break;
            case 'i':
                imageflag = true;
                break;
            case 'h':
                usage(argv[0]);
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
    }
        
    ga_solution *sol = ga_solver(queens, popSize, maxGens, selflag,
              verboseflag, pMut, pCross);
    check_condition(sol == NULL, argv[0], "Couldn't allocate memory for solution.\n");
    if(sol->generation == 0){
        fprintf(stderr, "No solution found after %d generations.\n", maxGens);
        fprintf(stderr, 
        "Hint: increase the maximum generations to compute with option \"-g [maxGens]\"\n");
    }
    else{
        printf("Solution found at generation #%d\n", sol->generation);
        printf("With queens = %d\n", sol->queens);
        printf("Solution: [ ");
        for(uint i = 0; i < sol->queens; i ++)
            printf((i == (sol->queens - 1)) ? "%d ]" : "%d, ", sol->solution[i]);
        printf("\n");
        /* Draw solution on board */
        if(imageflag)
            draw_solution(sol->queens, sol->solution, "solution.png");
            
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

